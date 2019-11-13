#include "A_NumberExpr.h"
#include <typeinfo>
#include <iostream>

using std::cout;	using std::endl;

void A_NumberExpr::Print(int d)
{
	indent(d);
	cout << std::fixed << "numberExpr: " << val << endl;
}

