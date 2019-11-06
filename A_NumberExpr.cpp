#include <typeinfo>
#include "A_NumberExpr.h"

void A_NumberExpr::Print(int d)
{
	indent(d);
	cout<<"numberExpr: "<<val<<endl;
}

