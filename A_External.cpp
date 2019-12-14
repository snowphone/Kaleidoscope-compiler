#include "A_External.h"

#include <typeinfo>
#include <iostream>

#include <llvm/IR/Function.h>

using std::cout;	using std::endl;
using llvm::Function;

void A_External::Print(int d)
{
	indent(d);
	cout << "external" << endl;

	this->prototype->Print(d + 2);
}

A_External::~A_External() {
	delete this->prototype;
}

Function* A_External::Codegen() {
	functionProtos[prototype->GetName()] = prototype;
	return this->prototype->Codegen();
}
