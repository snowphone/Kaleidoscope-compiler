#include <typeinfo>
#include "A_BinaryExpr.h"

void A_BinaryExpr::Print(int d)
{
	indent(d);
	cout<<"binaryExpr: "<<oper<<endl;
	left.Print(d+2);	
	right.Print(d+2);

}

