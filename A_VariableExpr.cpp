#include <typeinfo>
#include "A_VariableExpr.h"

void A_VariableExpr::Print(int d)
{
	indent(d);
	cout<<"variableExpr"<<endl;
	ident.Print(d+2);
}

