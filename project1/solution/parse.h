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
	string name;
	string type;
	vector<Stmt> vs;
	vector<vector<Expr>> var_list; // vector of var, 会有重复
};

void parse(FILE*, record&);
#endif
