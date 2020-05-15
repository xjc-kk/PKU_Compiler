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

#ifndef BOOST_IRVISITOR_H
#define BOOST_IRVISITOR_H

#include "IR.h"
#include <unordered_map>
#include <utility>
#include <cassert>
#include <algorithm>
#include <vector>
#include <set>


namespace Boost {

namespace Internal {

class IRVisitor {
 public:
    virtual void visit(Ref<const IntImm>);
    virtual void visit(Ref<const UIntImm>);
    virtual void visit(Ref<const FloatImm>);
    virtual void visit(Ref<const StringImm>);
    virtual void visit(Ref<const Unary>);
    virtual void visit(Ref<const Binary>);
    virtual void visit(Ref<const Select>);
    virtual void visit(Ref<const Compare>);
    virtual void visit(Ref<const Call>);
    virtual void visit(Ref<const Var>);
    virtual void visit(Ref<const Cast>);
    virtual void visit(Ref<const Ramp>);
    virtual void visit(Ref<const Index>);
    virtual void visit(Ref<const Dom>);
    virtual void visit(Ref<const LoopNest>);
    virtual void visit(Ref<const IfThenElse>);
    virtual void visit(Ref<const Move>);
    virtual void visit(Ref<const Kernel>);

   std::unordered_map<std::string, std::pair<int, int> > index_mp;  // index_name-->index_dom
   std::vector<std::vector<std::pair<Expr, int> > > needIf;   // <index expressions that need IF check, upper_bound> for each term
   std::unordered_map<std::string, std::vector<int> > var_dims;  // var_name-->dims
   std::vector<std::set<std::string> > termIndex;   // term private indexes
   std::vector<std::string> left_indexes; // indexes of leftVar
   bool enterR; // whether comes to righthand of "="
   int ti; // indexNo. of terms

 private:
};

}  // namespace Internal

}  // namespace Boost


#endif  // BOOST_IRVISITOR_H