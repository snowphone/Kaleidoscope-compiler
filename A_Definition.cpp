#include "A_Definition.h"
#include <typeinfo>
#include <iostream>

using std::cout;	using std::endl;

void A_Definition::Print(int d)
{
	indent(d);
	cout << "definition" << endl;

	this->header->Print(d + 2);

	this->body->Print(d + 2);
}

A_Definition::~A_Definition() {
	delete this->header;
	delete this->body;
}
