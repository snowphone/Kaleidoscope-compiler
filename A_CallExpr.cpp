#include "A_CallExpr.h"
#include <typeinfo>
#include <iostream>
#include <string>

using std::cout;	using std::endl;

void A_CallExpr::Print(int d)
{
	int size = arguments.size();

	indent(d);
	cout << "callExpr" << endl;

	indent(d+2);
	cout << "funcName" << '\t' << this->funcName << endl;
	
	indent(d+2);
	cout << "expressionList" << endl;
	for(int i = 0; i < size; i++) {
		A_Expr& e = *(dynamic_cast<A_Expr*>(arguments.at(i)));
		e.Print(d+4);
	}
}
