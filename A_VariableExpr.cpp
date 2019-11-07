#include "A_VariableExpr.h"
#include <typeinfo>
#include <iostream>

using std::cout;	using std::endl;


void A_VariableExpr::Print(int d)
{
	indent(d);
	cout << "variableExpr" << endl;
	id->Print(d+2);
}

A_VariableExpr::~A_VariableExpr() {
	delete this->id;
}
