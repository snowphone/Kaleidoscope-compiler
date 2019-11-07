#include "A_External.h"
#include <typeinfo>
#include <iostream>

using std::cout;	using std::endl;

void A_External::Print(int d)
{
	indent(d);
	cout << "external" << endl;
}

A_External::~A_External() {
	delete this->prototype;
}
