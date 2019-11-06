#include "A_BinaryExpr.h"
#include <typeinfo>
#include <iostream>

using std::cout;
using std::endl;

void A_BinaryExpr::Print(int d)
{
	indent(d);
	cout << "binaryExpr: " << oper << endl;
	left.Print(d+2);	
	right.Print(d+2);

}

