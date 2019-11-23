#include "A_Top.h"

#include <typeinfo>
#include <iostream>
#include <string>

using std::cout;

void A_Top::indent(int d)
{
	cout << std::string(d, ' ');
}
