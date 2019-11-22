#include "A_Identifier.h"

#include <typeinfo>
#include <iostream>

#include <llvm/IR/Value.h>

using std::cout;	using std::endl;
using llvm::Value;

void A_Identifier::Print(int d)
{
	indent(d);
	cout << "identifier: " << name << endl;
}

string A_Identifier::GetName() {
	return this->name;
}

Value* A_Identifier::Codegen() {
	Value* v = NamedValues[this->GetName()];
	return v ? v : NULL;
}
