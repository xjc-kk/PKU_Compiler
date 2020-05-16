/*
 * MIT License
 * 
 * Copyright (c) 2020 Size Zheng

 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
*/

#include "IRVisitor.h"

namespace Boost {

namespace Internal {


void IRVisitor::visit(Ref<const IntImm> op) {
    return;
}


void IRVisitor::visit(Ref<const UIntImm> op) {
    return;
}


void IRVisitor::visit(Ref<const FloatImm> op) {
    return;
}


void IRVisitor::visit(Ref<const StringImm> op) {
    return;
}


void IRVisitor::visit(Ref<const Unary> op) {
    (op->a).visit_expr(this);
    return;
}


void IRVisitor::visit(Ref<const Binary> op) {
    (op->a).visit_expr(this);
    (op->b).visit_expr(this);
    return;
}


void IRVisitor::visit(Ref<const Compare> op) {
    (op->a).visit_expr(this);
    (op->b).visit_expr(this);
    return;
}


void IRVisitor::visit(Ref<const Select> op) {
    (op->cond).visit_expr(this);
    (op->true_value).visit_expr(this);
    (op->false_value).visit_expr(this);
    return;
}


void IRVisitor::visit(Ref<const Call> op) {
    for (auto arg : op->args) {
        arg.visit_expr(this);
    }
    return;
}


void IRVisitor::visit(Ref<const Cast> op) {
    (op->val).visit_expr(this);
    return;
}


void IRVisitor::visit(Ref<const Ramp> op) {
    (op->base).visit_expr(this);
    return;
}


void IRVisitor::visit(Ref<const Var> op) {
    //std::cout << "Enter a Var Node...\n";

    std::vector<int> dims;

    if(op->shape.size() == 1 && op->shape[0] == 1 && op->args.size() == 0){ // scalar
        dims.push_back((int)op->shape[0]);
        if(var_dims.find(op->name) == var_dims.end())
            var_dims[op->name] = dims;
        return;
    }
        
    
    assert(op->shape.size() == op->args.size());


    for (size_t i = 0; i < op->shape.size(); ++i) {  
        dims.push_back((int)op->shape[i]);

        if(op->args[i].node_type() == IRNodeType::Index){    // index like i or j
            auto curArg = op->args[i].as<Index>();
            //std::cout << "Single Index: " << curArg->name << op->shape[i] << "\n";

            if(!enterR){
                left_indexes.push_back(curArg->name);
            }
            else{
                if(find(left_indexes.begin(), left_indexes.end(), curArg->name) == left_indexes.end())  // term private index
                    termIndex[ti].insert(curArg->name);
            }

            if(index_mp.find(curArg->name) != index_mp.end()){
                index_mp[curArg->name].first = std::max(index_mp[curArg->name].first, 0);
                index_mp[curArg->name].second = std::min(index_mp[curArg->name].second, (int)op->shape[i]);
            }
            else{
                index_mp[curArg->name] = std::make_pair(0, op->shape[i]);
            }
        }
        else{   // binary Expr like i+j or k+2 or 2*m+1
            needIf[ti].push_back(std::make_pair(op->args[i], op->shape[i]));
        }

    }

    if(var_dims.find(op->name) == var_dims.end())
        var_dims[op->name] = dims;

    return;
}


void IRVisitor::visit(Ref<const Dom> op) {
    (op->begin).visit_expr(this);
    (op->extent).visit_expr(this);
    return;
}


void IRVisitor::visit(Ref<const Index> op) {
    (op->dom).visit_expr(this);
    return;
}


void IRVisitor::visit(Ref<const LoopNest> op) {
    for (auto index : op->index_list) {
        index.visit_expr(this);
    }
    for (auto body : op->body_list) {
        body.visit_stmt(this);
    }
    return;
}


void IRVisitor::visit(Ref<const IfThenElse> op) {
    (op->cond).visit_expr(this);
    (op->true_case).visit_stmt(this);
    (op->false_case).visit_stmt(this);
    return;
}


void IRVisitor::visit(Ref<const Move> op) {
    (op->dst).visit_expr(this);
    (op->src).visit_expr(this);
    return;
}


void IRVisitor::visit(Ref<const Kernel> op) {
    for (auto expr : op->inputs) {
        expr.visit_expr(this);
    }
    for (auto expr : op->outputs) {
        expr.visit_expr(this);
    }
    for (auto stmt : op->stmt_list) {
        stmt.visit_stmt(this);
    }
    return;
}



}  // namespace Internal

}  // namespace Boost
