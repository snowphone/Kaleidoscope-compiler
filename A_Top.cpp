#include "A_Top.h"

#include <typeinfo>
#include <iostream>
#include <string>

#include <llvm/IR/Value.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/LLVMContext.h>

#ifdef NEW_CLANG
llvm::LLVMContext& getGlobalContext() {
	static llvm::LLVMContext TheContext;
	return TheContext;
}
#endif

llvm::IRBuilder<> Builder(getGlobalContext());
map<string, Value*> NamedValues = map<string, Value*>();
Module* TheModule = NULL;

A_TopList *aroot = NULL;

void A_Top::indent(int d)
{
	std::cout << std::string(d, ' ');
}
