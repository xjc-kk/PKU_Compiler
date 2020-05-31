#include "MyMutator.h"
#include <string>

namespace Boost {

namespace Internal {

Expr MyMutator::mutate(const Expr &expr) {
    return expr.mutate_expr(this);
}


Stmt MyMutator::mutate(const Stmt &stmt) {
    return stmt.mutate_stmt(this);
}


Group MyMutator::mutate(const Group &group) {
    return group.mutate_group(this);
}


Expr MyMutator::visit(Ref<const IntImm>     op) { return 0;}
Expr MyMutator::visit(Ref<const UIntImm>    op) { return 0;}
Expr MyMutator::visit(Ref<const FloatImm>   op) { return 0;}
Expr MyMutator::visit(Ref<const StringImm>  op) { return 0;}

Expr MyMutator::visit(Ref<const Unary> op) {
    Expr da = mutate(op->a);
    if (op->op_type == UnaryOpType::Neg)
        return Unary::make(op->type(), op->op_type, da);
    assert(false);
}

 const double eps = 1e-5;
bool iszero(const Expr& x)
{
    auto p = x.as<FloatImm>();
    if (p != nullptr && p->value() < eps && p->value() > -eps)
        return true;
    return false;
}
bool isone(const Expr& x)
{
    auto p = x.as<FloatImm>();
    if (p != nullptr && p->value() - 1.0 < eps && p->value() - 1.0 > -eps)
        return true;
    return false;
}
Expr MyMutator::visit(Ref<const Binary> op) {
    Expr da = mutate(op->a);
    Expr db = mutate(op->b);
    BinaryOpType type = op->op_type;
    if (type == BinaryOpType::Add || type == BinaryOpType::Sub)
    {
        if (iszero(da) && iszero(db)) return 0;
        return Binary::make(op->type(), op->op_type, da, db);
    }
    else if (type == BinaryOpType::Mul)
    {
        // a*b
        // return da*b+db*a
        if (iszero(da) && iszero(db)) return 0;
        Expr r1 = isone(da)? op->b: Binary::make(op->type(), BinaryOpType::Mul, da, op->b);
        Expr r2 = isone(db)? op->a: Binary::make(op->type(), BinaryOpType::Mul, op->a, db);
        if (iszero(da)) return r2;
        if (iszero(db)) return r1;
        return Binary::make(op->type(), BinaryOpType::Add, r1, r2);
    }
    else if (type == BinaryOpType::Div)
    {
        // x/y
        // return dx*y-x*dy/y^2
        // return dx/y simply
        return Binary::make(op->type(), BinaryOpType::Div, da, op->b);
    }
    
    assert(false);
}
Expr MyMutator::visit(Ref<const Var> op) {
    if (op->name.compare(grad) == 0)
    {
        cnt--;
        if (cnt!=0) return 0.0;
        dx = Var::make(op->type(), "d"+op->name, op->args, op->shape);
        return 1.0;
    }
    else
        return 0.0;
}

// end of file--------

/*
Expr MyMutator::visit(Ref<const Compare> op) {
    Expr new_a = mutate(op->a);
    Expr new_b = mutate(op->b);
    return Compare::make(op->type(), op->op_type, new_a, new_b);
}*/

/*
Expr MyMutator::visit(Ref<const Select> op) {
    Expr new_cond = mutate(op->cond);
    Expr new_true_value = mutate(op->true_value);
    Expr new_false_value = mutate(op->false_value);
    return Select::make(op->type(), new_cond, new_true_value, new_false_value);
}*/

/*
Expr MyMutator::visit(Ref<const Call> op) {
    std::vector<Expr> new_args;
    for (auto arg : op->args) {
        new_args.push_back(mutate(arg));
    }
    return Call::make(op->type(), new_args, op->func_name, op->call_type);
}*/

/*
Expr MyMutator::visit(Ref<const Cast> op) {
    Expr new_val = mutate(op->val);
    return Cast::make(op->type(), op->new_type, new_val);
}*/

/*
Expr MyMutator::visit(Ref<const Ramp> op) {
    Expr new_base = mutate(op->base);
    return Ramp::make(op->type(), new_base, op->stride, op->lanes);
}*/



/*
Expr MyMutator::visit(Ref<const Dom> op) {
    Expr new_begin = mutate(op->begin);
    Expr new_extent = mutate(op->extent);
    return Dom::make(op->type(), new_begin, new_extent);
}


Expr MyMutator::visit(Ref<const Index> op) {
    Expr new_dom = mutate(op->dom);
    return Index::make(op->type(), op->name, new_dom, op->index_type);
}*/

/*
Stmt MyMutator::visit(Ref<const LoopNest> op) {
    std::vector<Expr> new_index_list;
    std::vector<Stmt> new_body_list;
    for (auto index : op->index_list) {
        new_index_list.push_back(mutate(index));
    }
    for (auto body : op->body_list) {
        new_body_list.push_back(mutate(body));
    }
    return LoopNest::make(new_index_list, new_body_list);
}
*/
/*
Stmt MyMutator::visit(Ref<const IfThenElse> op) {
    Expr new_cond = mutate(op->cond);
    Stmt new_true_case = mutate(op->true_case);
    Stmt new_false_case = mutate(op->false_case);
    return IfThenElse::make(new_cond, new_true_case, new_false_case);
}
*/
/*
Stmt MyMutator::visit(Ref<const Move> op) {
    Expr new_dst = mutate(op->dst);
    Expr new_src = mutate(op->src);
    return Move::make(new_dst, new_src, op->move_type);
}*/

/*
Group MyMutator::visit(Ref<const Kernel> op) {
    std::vector<Expr> new_inputs;
    for (auto expr : op->inputs) {
        new_inputs.push_back(mutate(expr));
    }
    std::vector<Expr> new_outputs;
    for (auto expr : op->outputs) {
        new_outputs.push_back(mutate(expr));
    }
    std::vector<Stmt> new_stmt_list;
    for (auto stmt : op->stmt_list) {
        new_stmt_list.push_back(mutate(stmt));
    }
    return Kernel::make(op->name, new_inputs, new_outputs, new_stmt_list, op->kernel_type);
}*/


}  // namespace Internal

}  // namespace Boost
