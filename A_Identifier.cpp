#include "A_Identifier.h"
#include <typeinfo>
#include <iostream>

using std::cout;	using std::endl;

void A_Identifier::Print(int d)
{
	indent(d);
	cout << "identifier: " << name << endl;
}
