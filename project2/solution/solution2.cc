#include <iostream>
#include <cstdio>
#include <fstream>
#include <string>
#include <cstring>
//#include "parse.h"
#include "IRGenerator.h"
#include "MyPrinter.h"
#include "GradGen.h"

void check_js(const record& js);
int main() 
{
	char iname[100], oname[100];

	record js;

	for (int i=1;i<=10;i++)
	{
		sprintf(iname, "./cases/case%d.json", i);
		sprintf(oname, "./kernels/grad_case%d.cc", i);
		FILE* fin  = fopen(iname, "r");
		if (fin == nullptr) continue;
    //    if (i == 6) continue;
      //  if (i == 8) continue;
      //  if (i == 10) continue;
		// FILE* fout = fopen(oname, "w");
		std::cout<<"process :" << iname<<std::endl;
		// part1
		parse(fin, js);
        // part1.5
	    record grad_js;
        GradGen(js, grad_js);
	
        std::cout<<"CHECK: js\n";
        check_js(js);
        std::cout<<"CHECK: grad_js\n";
        check_js(grad_js);

	//	part2
		Group kernel = IRGenerator(grad_js);

//		std::cout << "Generator done!\n\n";

	// 	part3
	 	MyPrinter myprinter;
		std::string mycode = myprinter.print(kernel);

		std::cout << mycode;
		std::ofstream ofile(oname, std::ios::out);
		std::string head = "#include \"../run2.h\"\n\n";
		ofile << head;
    	ofile << mycode;
    	ofile.close();

//		std::cout << "Success!\n";
	}
	return 0;
}


void check_js(const record& js)
{
    std::cout<<"name: "+js.name<<std::endl;
    std::cout<<"type: "+js.type<<std::endl;
    std::cout<<"ins: "; for (string s: js.in) 	std::cout<<s<<' ';		std::cout<<std::endl;
    std::cout<<"outs: ";for (string s: js.out) 	std::cout<<s<<' ';		std::cout<<std::endl;
    std::cout<<"grad: ";for (string s: js.grad) std::cout<<s<<' ';		std::cout<<std::endl;
    std::cout<<js.vs.size()<<endl;

    for (int i=0;i<js.vs.size();i++)
    {
        MyPrinter printer;
        //		auto m = s.as<Move>();
        //		auto e = m->src.as<Binary>();
        //	std::cout <<  printer.print(js._vs[i])<<std::endl;
        for (auto e : js.vs[i])
        {
            MyPrinter printer;
            std::cout <<  printer.print(e)<<std::endl;
        }
        std::cout<<std::endl;
    }
    std::cout << "end!\n\n";
}

