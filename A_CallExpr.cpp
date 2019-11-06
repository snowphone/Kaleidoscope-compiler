#include "A_CallExpr.h"
#include <typeinfo>
#include <iostream>
#include <string>

using std::cout;	using std::endl;

void A_CallExpr::Print(int d)
{
	int size = arguments->size();

	indent(d);
	cout << "callExpr" << endl;

	indent(d+2);
	cout << "funcName" << endl;
	funcName->Print(d + 2);
	
	indent(d+2);
	cout << "expressionList" << endl;
	for(A_TopList::iterator it = arguments->begin(); it != arguments->end(); ++it) {
		A_Expr* e = dynamic_cast<A_Expr*>(*it);
		e->Print(d+4);
	}
}
