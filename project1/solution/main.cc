#include <iostream>
#include <cstdio>
#include <fstream>
#include <string>
#include <cstring>
//#include "parse.h"
#include "IRGenerator.h"
#include "IRPrinter.h"
#include "MyPrinter.h"
int main() 
{
//	char filehead[100] = "#include \"../run.h\"\n\n";

	char iname[100], oname[100];

	record js;

	for (int i=0;i<=11;i++)
	{
        if (i > 0) {
		    sprintf(iname, "./cases/case%d.json", i);
		    sprintf(oname, "./kernels/kernel_case%d.cc", i);
        }
        else {
            sprintf(iname, "./cases/example.json");
            sprintf(oname, "./kernels/kernel_example.cc");
        }
		FILE* fin  = fopen(iname, "r");
		if (fin == nullptr) continue;
		// FILE* fout = fopen(oname, "w");
		std::cout<<"process :" << iname<<std::endl;

	//	fputs(filehead, fout);
		
		// part1
		parse(fin, js);
		
		puts("check parse:");
		std::cout<<js.name<<std::endl;
		std::cout<<js.type<<std::endl;
		for (string s: js.in) 	std::cout<<s<<' ';		std::cout<<std::endl;
		for (string s: js.out) 	std::cout<<s<<' ';		std::cout<<std::endl;

		std::cout<<js.vs.size()<<endl;
	
		for (int i=0;i<js.vs.size();i++)
		{
			IRPrinter printer;
			//		auto m = s.as<Move>();
			//		auto e = m->src.as<Binary>();
			std::cout <<  printer.print(js._vs[i])<<std::endl;
			for (auto e : js.vs[i])
			{
				IRPrinter printer;
				std::cout <<  printer.print(e)<<std::endl;
			}
			std::cout<<std::endl;
			/*		
					for (auto var : js.var_list[i])
					{
					IRPrinter p;
					std::cout << p.print(var) <<'<';
					for (auto j : var.as<Var>()->shape)
					std::cout << j << ' ';
					std::cout<<'>'<<std::endl;
					}
					*/	
		}
		std::cout << "end!\n\n";
/*
	record js;
	js.in = {"B", "C"};
	js.out = {"A"};
	js.name = "test";
	js.type = "float";
	Type dataType = Type::int_scalar(32);
	vector<Expr> st;
	st.push_back(Var::make(Type::float_scalar(32), "A", {Index::make(Type::int_scalar(32), "i", Dom::make(Type::int_scalar(32), 0, 3), IndexType::Spatial)}, {3}));
	st.push_back(Var::make(Type::float_scalar(32), "B", {Index::make(Type::int_scalar(32), "j", Dom::make(Type::int_scalar(32), 0, 3), IndexType::Spatial)}, {3}));
	st.push_back(Var::make(Type::float_scalar(32), "C", {Index::make(Type::int_scalar(32), "k", Dom::make(Type::int_scalar(32), 0, 3), IndexType::Spatial)}, {3}));
	js.vs.push_back(st);
*/
	//	part2
		Group kernel = IRGenerator(js);

		std::cout << "Generator done!\n\n";

	// 	part3
	 	MyPrinter myprinter;
		std::string mycode = myprinter.print(kernel);

		std::cout << mycode;
		std::ofstream ofile(oname, std::ios::out);
		std::string head = "#include \"../run.h\"\n\n";
		ofile << head;
    	ofile << mycode;
    	ofile.close();
		// fputs(mycode, fout);

		std::cout << "Success!\n";
		

		// IRPrinter printer;
		// std::string code = printer.print(kernel);

		// std::cout << code;

		// std::cout << "Success!\n\n";
	}
	return 0;
}

