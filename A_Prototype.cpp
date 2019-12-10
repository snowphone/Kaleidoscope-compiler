#include "A_Prototype.h"

#include "A_Identifier.h"
#include "A_Lvalue.h"

#include <typeinfo>
#include <iostream>
#include <vector>

#include <llvm/IR/Module.h>
#include <llvm/IR/Type.h>
#include <llvm/IR/DerivedTypes.h>

using std::cout;	using std::endl;
using std::vector;	using llvm::Function;
using llvm::Type;	using llvm::FunctionType;

void A_Prototype::Print(int d) {
	indent(d);
	cout << "prototype" << endl;
	ident->Print(d+2);

	if(!paramList->empty()){
		indent(d+2);
		cout << "identifierList" << endl;
		for(A_TopList::iterator it = paramList->begin(); it != paramList->end(); ++it) {
			A_Top* a = dynamic_cast<A_Top*>(*it);
			a->Print(d+2 + 2);
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

string A_Prototype::GetName() {
	return this->ident->GetName();
}


Function* A_Prototype::Codegen() {
	// Assume Kaleidoscope only handles double type
	vector<Type*> arg_types;
	for(A_TopList::iterator it = paramList->begin(); it != paramList->end(); ++it) {
		Type* type = static_cast<A_Lvalue*>(*it)->getType();
		arg_types.push_back(type);
	}

	FunctionType* ft = FunctionType::get(this->return_type, arg_types, false);
	Function* f = Function::Create(ft, Function::ExternalLinkage, GetName(), TheModule);

	Function::arg_iterator fit = f->arg_begin();
	A_TopList::iterator ait = paramList->begin();

	for(; fit != f->arg_end(); ++fit, ++ait) {
		string name = dynamic_cast<A_Lvalue*>(*ait)->GetName();
		fit->setName(name);
	}
	return f;
}

