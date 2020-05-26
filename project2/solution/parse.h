#ifndef PARSE_H
#define PARSE_H

#include <vector>
#include <string>
#include "IR.h"
using namespace std;
using namespace Boost::Internal;
struct record {
	vector<string> in;
	vector<string> out;
    vector<string> grad;
	string name;
	string type;
//	vector<Stmt> _vs;
	vector<vector<Expr>> vs;
};

void parse(FILE*, record&);

Group IRGenerator(record& js);

#endif
