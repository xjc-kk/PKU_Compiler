#include "IRGenerator.h"

#include <unordered_map>
#include <utility>
#include <iostream>

#include "IRMutator.h"
#include "IRVisitor.h"
#include "IRPrinter.h"

IRVisitor visitor;
Type index_type;
Type dataType;

std::vector<Expr> ins;
std::vector<Expr> outs;
std::vector<Expr> left_index;
std::vector<Expr> right_index;
std::vector<Expr> all_index;
vector<Stmt> main_stmt;

void genStmt(Stmt s){
    left_index.clear();
    right_index.clear();
    all_index.clear();

    s.visit_stmt(&visitor);

    // generate indexes within stmt s

    //cout << "check indexes:\n";
    for(auto index_name : visitor.left_indexes){
        auto dom = visitor.index_mp[index_name];
        int begin = dom.first;
        int end = dom.second;
        //cout << index_name << ": [" << begin << "," << end << ")\n";

        Expr index_dom = Dom::make(index_type, begin, end-begin);
        Expr index_e = Index::make(index_type, index_name, index_dom, IndexType::Spatial);
        left_index.push_back(index_e);
        all_index.push_back(index_e);
    }

    for(int i = visitor.left_indexes.size(); i < visitor.indexes.size(); ++i){
        string index_name = visitor.indexes[i];
        auto dom = visitor.index_mp[index_name];
        int begin = dom.first;
        int end = dom.second;
        //cout << index_name << ": [" << begin << "," << end << ")\n";

        Expr index_dom = Dom::make(index_type, begin, end-begin);
        Expr index_e = Index::make(index_type, index_name, index_dom, IndexType::Reduce);
        right_index.push_back(index_e);
        all_index.push_back(index_e);
    }


    vector<long unsigned int> v;
    for(auto i : (visitor.var_dims)[visitor.leftVarName]){
        v.push_back(i);
    }

    if(!visitor.leftVarUseful){     // generate out = 0
        Expr dst = Var::make(dataType, visitor.leftVarName, left_index, v);
        Expr src = IntImm::make(dataType, 0);
        Stmt initiate = Move::make(dst, src, MoveType::MemToMem);

        Stmt move_stmt = Move::make(s.as<Move>()->dst, Binary::make(dataType, BinaryOpType::Add, s.as<Move>()->dst, s.as<Move>()->src), MoveType::MemToMem);
        
        if(visitor.needIf.empty()){
            main_stmt.push_back(LoopNest::make(left_index, {initiate, LoopNest::make(right_index, {move_stmt})}));
        }
        else{
            Stmt ifStmt = move_stmt;
            //cout << "check needIf:\n";
            for(auto itr : visitor.needIf){
                IRPrinter printer;
                //cout << printer.print(itr.first) << " : ";
                //cout << itr.second << "\n";
                Expr cond = Binary::make(index_type, BinaryOpType::And, 
                                    Compare::make(index_type, CompareOpType::LT, itr.first, IntImm::make(index_type, itr.second)),
                                    Compare::make(index_type, CompareOpType::GE, itr.first, IntImm::make(index_type, 0)));
                ifStmt = IfThenElse::make(cond, ifStmt, {});
            }
            main_stmt.push_back(LoopNest::make(left_index, {initiate, LoopNest::make(right_index, {ifStmt})}));
        }
        
    }
    else{
        if(visitor.leftVarPreSave){ // preSave outVar
            Expr dst = Var::make(dataType, "tmp", left_index, v);
            Expr src = Var::make(dataType, visitor.leftVarName, left_index, v);
            Stmt preSave = Move::make(dst, src, MoveType::MemToMem);
            main_stmt.push_back(LoopNest::make(left_index, {preSave}));
        }

        if(visitor.needIf.empty()){
            main_stmt.push_back(LoopNest::make(all_index, {s}));
        }
        else{
            Stmt ifStmt = s;
            //cout << "check needIf:\n";
            for(auto itr : visitor.needIf){
                IRPrinter printer;
                //cout << printer.print(itr.first) << " : ";
                //cout << itr.second << "\n";
                Expr cond = Binary::make(index_type, BinaryOpType::And, 
                                    Compare::make(index_type, CompareOpType::LT, itr.first, IntImm::make(index_type, itr.second)),
                                    Compare::make(index_type, CompareOpType::GE, itr.first, IntImm::make(index_type, 0)));
                ifStmt = IfThenElse::make(cond, ifStmt, {});
            }
            main_stmt.push_back(LoopNest::make(all_index, {ifStmt}));
        }
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

    for(auto s : js.vs){
        genStmt(s);
        // generate loop_nest
    }

    // generate ins & outs
    for(auto var : visitor.var_dims){
        vector<long unsigned int> v;
        for(auto i : var.second){
            v.push_back(i);
        }

        if(find(js.out.begin(), js.out.end(), var.first) != js.out.end()){
            Expr out_e = Var::make(dataType, var.first, {}, v);
            outs.push_back(out_e);
        }
        if(find(js.in.begin(), js.in.end(), var.first) != js.in.end()){
            Expr in_e = Var::make(dataType, var.first, {}, v);
            ins.push_back(in_e);
        }
    }

    // kernel
    Group kernel = Kernel::make(js.name, ins, outs, main_stmt, KernelType::CPU);

    return kernel;

}
