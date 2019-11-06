#include <typeinfo>
#include "A_Identifier.h"

void A_Identifier::Print(int d)
{
	indent(d);
	cout<<"identifier: "<<name<<endl;
}
