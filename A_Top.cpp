#include "A_Top.h"
#include <typeinfo>
#include <iostream>
#include <string>

A_TopList *aroot = NULL;

void A_Top::indent(int d)
{
	std::cout << std::string(d, ' ');
}
