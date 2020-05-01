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
};

void parse(FILE*, record&);

#endif
