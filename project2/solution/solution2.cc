#include <iostream>
#include <cstdio>
#include <fstream>
#include <string>
#include <cstring>
//#include "parse.h"
#include "IRGenerator.h"
#include "MyPrinter.h"
int main() 
{
	char iname[100], oname[100];

	record js;

	for (int i=3;i<=9;i++)
	{
		sprintf(iname, "./cases/case%d.json", i);
		sprintf(oname, "./kernels/grad_case%d.cc", i);
		FILE* fin  = fopen(iname, "r");
		if (fin == nullptr) continue;
		// FILE* fout = fopen(oname, "w");
		std::cout<<"process :" << iname<<std::endl;

	//	fputs(filehead, fout);
		
		// part1
		parse(fin, js);
	/*	
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
		}
		std::cout << "end!\n\n";
*/
	//	part2
		Group kernel = IRGenerator(js);

//		std::cout << "Generator done!\n\n";

	// 	part3
	 	MyPrinter myprinter;
		std::string mycode = myprinter.print(kernel);

		std::cout << mycode;
/*		std::ofstream ofile(oname, std::ios::out);
		std::string head = "#include \"../run2.h\"\n\n";
		ofile << head;
    	ofile << mycode;
    	ofile.close();
*/		// fputs(mycode, fout);

//		std::cout << "Success!\n";
	}
	return 0;
}


