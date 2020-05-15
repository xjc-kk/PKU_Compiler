#include "IRGenerator.h"

#include <unordered_map>
#include <utility>
#include <iostream>

#include "IRMutator.h"
#include "IRVisitor.h"
#include "IRPrinter.h"

IRVisitor visitor;
IRMutator mutator;
Type index_type;
Type dataType;

std::vector<Expr> ins;
std::vector<Expr> outs;
std::vector<Expr> left_index;
vector<Stmt> main_stmt;
int stmtNum;

void genStmt(vector<Expr> s){
    left_index.clear();

    visitor.index_mp.clear();
    visitor.needIf.clear();
    visitor.termIndex.clear();
    visitor.left_indexes.clear();
    visitor.needIf.resize(s.size());
    visitor.termIndex.resize(s.size());

    vector<Stmt> termStmts;

    // visit dst var
    visitor.enterR = false;
    s[0].visit_expr(&visitor);

    // generate claim of tmp and set tmp to 0
    mutator.stmtNum = stmtNum;
    Expr tmp = mutator.mutate(s[0]);
    main_stmt.push_back(Move::make(tmp, tmp, MoveType::MemToMem));
    termStmts.push_back(Move::make(tmp, IntImm::make(dataType, 0), MoveType::MemToMem));

    // visit each src term
    visitor.enterR = true;
    for(int i = 1; i < s.size(); ++i){
        visitor.ti = i;
        s[i].visit_expr(&visitor);
    }

    // generate left indexes
    //cout << "check indexes:\n";
    for(auto index_name : visitor.left_indexes){
        auto dom = visitor.index_mp[index_name];
        int begin = dom.first;
        int end = dom.second;
        //cout << index_name << ": [" << begin << "," << end << ")\n";

        Expr index_dom = Dom::make(index_type, begin, end-begin);
        Expr index_e = Index::make(index_type, index_name, index_dom, IndexType::Spatial);
        left_index.push_back(index_e);
    }

    // deal with each term loop
    for(int i = 1; i < s.size(); ++i){
        vector<Expr> termIndexes;
        for(auto ind: visitor.termIndex[i]){
            auto dom = visitor.index_mp[ind];
            int begin = dom.first;
            int end = dom.second;
            Expr index_dom = Dom::make(index_type, begin, end);
            Expr index_e = Index::make(index_type, ind, index_dom, IndexType::Reduce);
            termIndexes.push_back(index_e);
        }
        Stmt ifStmt = Move::make(tmp, Binary::make(dataType, BinaryOpType::Add, tmp, s[i]), MoveType::MemToMem);
        for(auto itr : visitor.needIf[i]){
            Expr cond = Binary::make(index_type, BinaryOpType::And, 
                                Compare::make(index_type, CompareOpType::LT, itr.first, IntImm::make(index_type, itr.second)),
                                Compare::make(index_type, CompareOpType::GE, itr.first, IntImm::make(index_type, 0)));
            ifStmt = IfThenElse::make(cond, ifStmt, {});
        }
        if(!termIndexes.empty())
            termStmts.push_back(LoopNest::make(termIndexes, {ifStmt}));
        else
            termStmts.push_back(ifStmt);
    }

    // generate main loop part
    if(!left_index.empty()){
        main_stmt.push_back(LoopNest::make(left_index, termStmts));
        main_stmt.push_back(LoopNest::make(left_index, {Move::make(s[0], tmp, MoveType::MemToMem)}));
    }
    else{
        for(auto st: termStmts)
            main_stmt.push_back(st);
        main_stmt.push_back(Move::make(s[0], tmp, MoveType::MemToMem));
    }
 
}

Group IRGenerator(record& js) {
    index_type = Type::int_scalar(32);
    if (js.type == "float")	dataType = Type::float_scalar(32);
	if (js.type == "int")	dataType = Type::int_scalar(32);
    ins.clear();
    outs.clear();
    visitor.var_dims.clear();
    main_stmt.clear();

    stmtNum = 0;

    for(auto s : js.vs){
        stmtNum++;
        genStmt(s);
    }
    
    // for(auto var : visitor.var_dims){
    //     vector<long unsigned int> v;
    //     for(auto i : var.second){
    //         v.push_back(i);
    //     }

    //     if(find(js.out.begin(), js.out.end(), var.first) != js.out.end()){
    //         Expr out_e = Var::make(dataType, var.first, {}, v);
    //         outs.push_back(out_e);
    //     }
    //     if(find(js.in.begin(), js.in.end(), var.first) != js.in.end()){
    //         Expr in_e = Var::make(dataType, var.first, {}, v);
    //         ins.push_back(in_e);
    //     }
    // }

    // generate ins & outs
    for(auto in_name = js.in.begin(); in_name != js.in.end(); in_name++){
        auto var = visitor.var_dims.find(*in_name);
        if(var != visitor.var_dims.end()){
            vector<long unsigned int> v;
            for(auto i : var->second){
                v.push_back(i);
            }
            Expr in_e = Var::make(dataType, var->first, {}, v);
            ins.push_back(in_e);
        }
    }
    for(auto out_name = js.out.begin(); out_name != js.out.end(); out_name++){
        auto var = visitor.var_dims.find(*out_name);
        if(var != visitor.var_dims.end()){
            vector<long unsigned int> v;
            for(auto i : var->second){
                v.push_back(i);
            }
            Expr out_e = Var::make(dataType, var->first, {}, v);
            outs.push_back(out_e);
        }
    }    
    // kernel
    Group kernel = Kernel::make(js.name, ins, outs, main_stmt, KernelType::CPU);

    return kernel;

}
