#include "GradGen.h"
#include "MyMutator.h"
using namespace std;
static Type data_type;
vector<Expr> get_grad(const vector<Expr>& vs, const string& x)
{
    static vector<Expr> vec;
    vec.resize(1);

    MyMutator mutator;
    mutator.set_grad(x);
    auto y = vs[0].as<Var>();
    Expr dy = Var::make(data_type, "d" + y->name, y->args, y->shape);
    for (int i=1;i<vs.size();i++)
    {
        Expr ret = vs[i].mutate_expr(&mutator);
        Expr z = Binary::make(data_type, BinaryOpType::Mul, ret, dy); 
        vec.push_back(z);
        // c = a*b
        // da = dc*b
  //   Var(type, name, args, shape)
    }
    vec[0] = mutator.get_dx();
    return vec;
}
void GradGen(const record& js, record& result)
{
    for (auto& in : js.in)
        result.in.push_back(in);
    for (auto& out : js.out)
        result.in.push_back("d" + out);
    for (auto& grad : js.grad)
        result.out.push_back("d" + grad);
    result.type = js.type;
    result.name = js.name;

    if (js.type.compare("float")==0)	data_type = Type::float_scalar(32);
    if (js.type.compare("int"  )==0)	data_type = Type::int_scalar(32);

    // for kernel
    const vector<Expr>& vs = js.vs[0]; // always be one assignment in case
  //  MyMutator mutator;
    for (auto& grad : js.grad)
    {
        result.vs.push_back(get_grad(vs, grad));
        //left value
    //   vec.push_back(Var::make(data_type, "d"+vs[0].name, vs[0].args, vs[0].shape));

    }

}
