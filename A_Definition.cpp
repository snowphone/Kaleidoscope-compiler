#include "A_Definition.h"

#include <typeinfo>
#include <iostream>
#include <vector>

#include <llvm/IR/Module.h>
#include <llvm/IR/Function.h>
#include <llvm/IR/BasicBlock.h>

using std::cout;	using std::endl;
using std::vector;	using llvm::Function;
using llvm::BasicBlock;

void A_Definition::Print(int d)
{
	indent(d);
	cout << "definition" << endl;

	this->header->Print(d + 2);

	for(A_TopList::iterator it = body->begin(); it != body->end(); ++it) {
		(*it)->Print(d + 2);
	}
}

A_Definition::~A_Definition() {
	delete this->header;
	delete this->body;
}

Function* A_Definition::Codegen() {
	// Check for previous 'extern' declaration
	functionProtos[header->GetName()] = header;
	Function* function = getFunction(header->GetName());

	if(!function)
		function = header->Codegen();

	if(!function) 
		return NULL;


	// Create a block
	BasicBlock* bb = BasicBlock::Create(getGlobalContext(), "entry", function);
	Builder.SetInsertPoint(bb);

	// Record the function arguments in the NamedValues map.
	map<string, Value*> backup;
	std::copy(NamedValues.begin(), NamedValues.end(), std::inserter(backup, backup.end()));

	for(Function::arg_iterator it = function->arg_begin(); it != function->arg_end(); ++it) {
		NamedValues[it->getName()] = &*it;
	}

	for(A_TopList::iterator it = body->begin(); it != body->end() - 1; ++it) {
		(*it)->Codegen();
	}

	Value* ret = body->back()->Codegen();

	// If the function is not global
	if(!header->GetName().empty()) {
		NamedValues.clear();
		std::copy(backup.begin(), backup.end(), std::inserter(NamedValues, NamedValues.end()));
	}

	if(ret) {
		Builder.CreateRet(ret);
		return function;
	} else {
		// Error
		function->eraseFromParent();
		return NULL;
	}
}
