#include "A_Prototype.h"
#include <typeinfo>
#include <iostream>

using std::cout;	using std::endl;

void A_Prototype::Print(int d)
{
	indent(d);
	cout << "prototype" << endl;
	ident->Print(d+2);

	if(!paramList->empty()){
		indent(d+2);
		cout << "identifierList" << endl;
		for(A_TopList::iterator it = paramList->begin(); it != paramList->end(); ++it) {
			A_Top* a = dynamic_cast<A_Top*>(*it);
			a->Print(d+4);
		}
	}
}

A_Prototype::~A_Prototype() {
	delete this->ident;
	for(A_TopList::iterator it = paramList->begin(); it != paramList->end(); ++it) {
		delete *it;
	}
	delete this->paramList;
}
