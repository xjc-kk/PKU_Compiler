#include "MyPrinter.h"

namespace Boost {

namespace Internal {


std::string MyPrinter::print(const Expr &expr) {
    oss.clear();
    expr.visit_expr(this);
    return oss.str();
}


std::string MyPrinter::print(const Stmt &stmt) {
    oss.clear();
    stmt.visit_stmt(this);
    return oss.str();
}


std::string MyPrinter::print(const Group &group) {
    oss.clear();
    group.visit_group(this);
    return oss.str();
}


void MyPrinter::visit(Ref<const IntImm> op) {
    oss << op->value();
}


void MyPrinter::visit(Ref<const UIntImm> op) {
    oss << op->value();
}


void MyPrinter::visit(Ref<const FloatImm> op) {
    oss << op->value();
}


void MyPrinter::visit(Ref<const StringImm> op) {
    oss << op->value();
}


void MyPrinter::visit(Ref<const Unary> op) {
    oss << "(";
    if (op->op_type == UnaryOpType::Neg) {
        oss << "-";
    } else if (op->op_type == UnaryOpType::Not) {
        oss << "!";
    }
    (op->a).visit_expr(this);
    oss << ")";
}


void MyPrinter::visit(Ref<const Binary> op) {
    oss << "(";
    (op->a).visit_expr(this);
    if (op->op_type == BinaryOpType::Add) {
        oss << " + ";
    } else if (op->op_type == BinaryOpType::Sub) {
        oss << " - ";
    } else if (op->op_type == BinaryOpType::Mul) {
        oss << " * ";
    } else if (op->op_type == BinaryOpType::Div) {
        oss << " / ";
    } else if (op->op_type == BinaryOpType::Mod) {
        oss << " % ";
    } else if (op->op_type == BinaryOpType::And) {
        oss << " && ";
    } else if (op->op_type == BinaryOpType::Or) {
        oss << " || ";
    }
    (op->b).visit_expr(this);
    oss << ")";
}


void MyPrinter::visit(Ref<const Compare> op) {
    (op->a).visit_expr(this);
    if (op->op_type == CompareOpType::LT) {
        oss << " < ";
    } else if (op->op_type == CompareOpType::LE) {
        oss << " <= ";
    } else if (op->op_type == CompareOpType::EQ) {
        oss << " == ";
    } else if (op->op_type == CompareOpType::GE) {
        oss << " >= ";
    } else if (op->op_type == CompareOpType::GT) {
        oss << " > ";
    } else if (op->op_type == CompareOpType::NE) {
        oss << " != ";
    }
    (op->b).visit_expr(this);
}


void MyPrinter::visit(Ref<const Select> op) {
    // no use
    oss << "select(";
    (op->cond).visit_expr(this);
    oss << ", ";
    (op->true_value).visit_expr(this);
    oss << ", ";
    (op->false_value).visit_expr(this);
    oss << ")";
}


void MyPrinter::visit(Ref<const Call> op) {
    // no use
    oss << "call_";
    if (op->call_type == CallType::Pure) {
        oss << "pure";
    } else if (op->call_type == CallType::SideEffect) {
        oss << "side_effect";
    };
    oss << "(" << op->func_name;
    for (size_t i = 0; i < op->args.size(); ++i) {
        oss << ", ";
        op->args[i].visit_expr(this);
    }
    oss << ")";
}


void MyPrinter::visit(Ref<const Cast> op) {
    // no use
    oss << "cast<" << op->new_type << ">(";
    (op->val).visit_expr(this);
    oss << ")";
}


void MyPrinter::visit(Ref<const Ramp> op) {
    //no use
    oss << "ramp(";
    (op->base).visit_expr(this);
    oss << ", " << op->stride << ", " << op->lanes << ")";
}


void MyPrinter::visit(Ref<const Var> op) {
    if (print_arg) {
        if (op->type() == Type::float_scalar(32))   oss << "float"; //check
        else oss << "int";
        oss << " (&";
        oss << op->name;
        oss << ")";
        for (size_t i = 0; i < op->shape.size(); ++i) {
            if(i == 0 && op->shape[i] == 1) break;// not an array
            oss << "[";
            oss << op->shape[i];
            oss << "]";
        }
    } 
    else {
        oss << op->name;
        for (size_t i = 0; i < op->args.size(); ++i) {
            oss << "[";
            op->args[i].visit_expr(this);
            oss << "]";
        }
    }
}


void MyPrinter::visit(Ref<const Dom> op) {
    if(get_begin){ // print op->begin
        (op->begin).visit_expr(this);
    }
    else{ // print extent
        // actually, extent is the end 
        (op->extent).visit_expr(this);
    }
}


void MyPrinter::visit(Ref<const Index> op) {
    if (print_range) { // in loop
        get_begin = true;
        oss << "(int ";
        oss << op->name;
        oss << " = ";
        (op->dom).visit_expr(this);
        oss << "; ";
        oss << op->name;
        oss << " < ";
        get_begin = false;
        (op->dom).visit_expr(this);
        oss << "; ++";
        oss << op->name;
        oss << ") ";
    }
    else    oss << op->name;
}


void MyPrinter::visit(Ref<const LoopNest> op) {
    print_range = true;
    for (auto index : op->index_list) {
        print_indent();
        oss << "for ";
        index.visit_expr(this);
        oss << "{\n";
        enter();
    }
    print_range = false;
    for (auto body : op->body_list) {
        body.visit_stmt(this);
    }
    for (auto index : op->index_list) {
        exit();
        print_indent();
        oss << "}\n";
    }
}


void MyPrinter::visit(Ref<const IfThenElse> op) {
    print_indent();
    oss << "if (";
    (op->cond).visit_expr(this);
    oss << ") {\n";
    enter();
    (op->true_case).visit_stmt(this);
    exit();

    // stop printing "else" since so far we don't need it
    /*print_indent();
    oss << "} else {\n";
    enter();
    (op->false_case).visit_stmt(this);
    exit();*/

    print_indent();
    oss << "}\n";
}


void MyPrinter::visit(Ref<const Move> op) {
    print_indent();
    /*if(op->src == NULL){
        oss << "float ";
    }*/
    (op->dst).visit_expr(this);
    // oss << " =<";
    // if (op->move_type == MoveType::HostToDevice) {
    //     oss << "host_to_device";
    // } else if (op->move_type == MoveType::MemToShared) {
    //     oss << "mem_to_shared";
    // } else if (op->move_type == MoveType::SharedToMem) {
    //     oss << "shared_to_mem";
    // } else if (op->move_type == MoveType::MemToLocal) {
    //     oss << "mem_to_local";
    // } else if (op->move_type == MoveType::LocalToMem) {
    //     oss << "local_to_mem";
    // } else if (op->move_type == MoveType::SharedToLocal) {
    //     oss << "shared_to_local";
    // } else if (op->move_type == MoveType::LocalToShared) {
    //     oss << "local_to_shared";
    // } else if (op->move_type == MoveType::SharedToShared) {
    //     oss << "shared_to_shared";
    // } else if (op->move_type == MoveType::MemToMem) {
    //     oss << "mem_to_mem";
    // } else if (op->move_type == MoveType::LocalToLocal) {
    //     oss << "local_to_local";
    // }
    // oss << "> ";
    //if(op->src != NULL){
        oss << " = ";
        (op->src).visit_expr(this);
    //}
    oss << ";\n";
}


void MyPrinter::visit(Ref<const Kernel> op) {
    print_indent();
    // if (op->kernel_type == KernelType::CPU) {
    //     oss << "<CPU>";
    // } else if (op->kernel_type == KernelType::GPU) {
    //     oss << "<GPU>";
    // }
    oss << "void";
    oss << " " << op->name << "(";
    print_arg = true;
    bool arg_num = false;// whether to add ","
    for (size_t i = 0; i < op->inputs.size(); ++i) {
        op->inputs[i].visit_expr(this);
        arg_num = true;
        if (i < op->inputs.size() - 1) {
            oss << ", ";
        }
    }
    for (size_t i = 0; i < op->outputs.size(); ++i) {
        if(arg_num)  oss << ", ";
        op->outputs[i].visit_expr(this);
    }
    print_arg = false;
    oss << ") {\n";
    enter();
    for (auto stmt : op->stmt_list) {
        stmt.visit_stmt(this);
    }
    exit();
    oss << "}\n";
}


}  // namespace Internal

}  // namespace Boost
