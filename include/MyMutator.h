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

#ifndef MY_MUTATOR_H
#define MY_MUTATOR_H

#include "IR.h"
#include "IRMutator.h"

namespace Boost {

namespace Internal {

class MyMutator:public IRMutator {
private:
    std::string grad;
    Expr dx;
public:
    void set_grad(const std::string& s) { grad = s;}
    Expr get_dx() const { return dx;}

    Expr mutate(const Expr&);
    Stmt mutate(const Stmt&);
    Group mutate(const Group&);

    virtual Expr visit(Ref<const IntImm>) override;
    virtual Expr visit(Ref<const UIntImm>) override;
    virtual Expr visit(Ref<const FloatImm>) override;
    virtual Expr visit(Ref<const StringImm>) override;
    virtual Expr visit(Ref<const Unary>) override;
    virtual Expr visit(Ref<const Binary>) override;
    virtual Expr visit(Ref<const Var>) override;
  //  virtual Expr visit(Ref<const Select>) override;
//    virtual Expr visit(Ref<const Compare>) override;
//    virtual Expr visit(Ref<const Call>) override;
 //   virtual Expr visit(Ref<const Index>) override;
  //  virtual Expr visit(Ref<const Dom>) override;
  //  virtual Stmt visit(Ref<const LoopNest>) override;
 //   virtual Stmt visit(Ref<const IfThenElse>);
  //  virtual Stmt visit(Ref<const Move>) override;
   // virtual Group visit(Ref<const Kernel>);

    int stmtNum;
 private:
};

}  // namespace Internal

}  // namespace Boost


#endif  // MY_MUTATOR_H
