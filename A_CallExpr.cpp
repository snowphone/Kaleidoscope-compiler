#include "A_CallExpr.h"

#include <typeinfo>
#include <iostream>
#include <string>

#include "A_ListExpr.h"

#include <llvm/IR/Module.h>
#include <llvm/IR/Function.h>

using std::cout;		using std::endl;
using llvm::Function;

void A_CallExpr::Print(int d) {
	indent(d);
	cout << "callExpr" << endl;

	funcName->Print(d + 2);
	
	indent(d+2);
	cout << "expressionList" << endl;
	for(A_TopList::iterator it = arguments->begin(); it != arguments->end(); ++it) {
		A_Expr* e = dynamic_cast<A_Expr*>(*it);
		e->Print(d+2 + 2);
	}
}

A_CallExpr::~A_CallExpr() {
	delete this->funcName;
	for(A_TopList::iterator it = arguments->begin(); it != arguments->end(); ++it) {
		delete *it;
	}
	delete this->arguments;
}

Value* A_CallExpr::Codegen() {
	using llvm::Function;

	if(funcName->GetName() == "get_element")
		return A_ListExpr::get_element((A_ListExpr*) arguments->front(), (A_Expr*) arguments->back());

	Function* callee = getFunction(funcName->GetName());
	if(!callee) {
		return LogErrorV("Calling undefined function named '" + funcName->GetName() + "'!");
	}

	if(callee->arg_size() != arguments->size()) {
		return LogErrorV("A_CallExpr::Codegen: Expected # of arguements " + to_string(callee->arg_size()) + ", actual: " + to_string(arguments->size()));
	}

	std::vector<Value*> argv;
	for(A_TopList::iterator it = arguments->begin(); it != arguments->end(); ++it) {
		Value* v = (*it)->Codegen();
		if(v)
			argv.push_back(v);
		else
			return NULL;
	}

	return Builder.CreateCall(callee, argv, funcName->GetName());
}
