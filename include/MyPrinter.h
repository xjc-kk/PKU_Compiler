#ifndef MYPRINTER_H
#define MYPRINTER_H

#include <string>
#include <sstream>

#include "IRVisitor.h"


namespace Boost {

namespace Internal {

class MyPrinter : public IRVisitor {
 public:
    MyPrinter() : IRVisitor() {
        indent = 0;
        print_range = false;
        print_arg = false;
    }
    std::string print(const Expr&);
    std::string print(const Stmt&);
    std::string print(const Group&);

    void print_indent() {
        for (int i = 0; i < indent; ++i)
            oss << " ";
    }

    void enter() {
        indent += 2;
    }

    void exit() {
        indent -= 2;
    }

    void visit(Ref<const IntImm>) override;
    void visit(Ref<const UIntImm>) override;
    void visit(Ref<const FloatImm>) override;
    void visit(Ref<const StringImm>) override;
    void visit(Ref<const Unary>) override;
    void visit(Ref<const Binary>) override;
    void visit(Ref<const Select>) override;
    void visit(Ref<const Compare>) override;
    void visit(Ref<const Call>) override;
    void visit(Ref<const Var>) override;
    void visit(Ref<const Cast>) override;
    void visit(Ref<const Ramp>) override;
    void visit(Ref<const Index>) override;
    void visit(Ref<const Dom>) override;
    void visit(Ref<const LoopNest>) override;
    void visit(Ref<const IfThenElse>) override;
    void visit(Ref<const Move>) override;
    void visit(Ref<const Kernel>) override;
 private:
    std::ostringstream oss;
    int indent;
    bool print_range;
    bool print_arg;
    bool print_claim;
    bool get_begin;
};

}  // namespace Internal

}  // namespace Boost


#endif  // MYPRINTER_H