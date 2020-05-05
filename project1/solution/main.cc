#include <iostream>
#include <cstdio>
#include <fstream>
#include <string>
#include <cstring>
#include "parse.h"
#include "IRPrinter.h"
int main() 
{
//	char filehead[100] = "#include \"../run.h\"\n\n";

	char iname[100], oname[100];

	record js;
//	int i=10;
	for (int i=1;i<=10;i++)
	{
		sprintf(iname, "./cases/case%d.json", i);
		sprintf(oname, "./kernels/kernel_case%d.cc", i);
		FILE* fin  = fopen(iname, "r");
		if (fin == nullptr) continue;
	//	FILE* fout = fopen(oname, "w");
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
			std::cout <<  printer.print(js.vs[i])<<std::endl;
			for (auto var : js.var_list[i])
			{
				IRPrinter p;
				std::cout << p.print(var) <<'<';
				for (auto j : var.as<Var>()->shape)
					std::cout << j << ' ';
				std::cout<<'>'<<std::endl;
			}
		}
		std::cout << "end!\n\n";

	//	part2
		Group kernel = IRGenerator(js);

		std::cout << "Generator done!\n\n";

	/*	part3
	 	MyPrinter printer;
		std::string code = printer.print(kernel);

		std::cout << code;
		fputs(code, fout);

		std::cout << "Success!\n";
		*/

		IRPrinter printer;
		std::string code = printer.print(kernel);

		std::cout << code;

		std::cout << "Success!\n\n";
	}
	return 0;
}

