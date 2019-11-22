#include "A_Top.h"

#include <typeinfo>
#include <iostream>
#include <string>

#ifdef NEW_CLANG
llvm::LLVMContext& getGlobalContext() {
	static llvm::LLVMContext TheContext;
	return TheContext;
}
#endif

llvm::IRBuilder<> Builder(getGlobalContext());
map<string, Value*> NamedValues = map<string, Value*>();

A_TopList *aroot = NULL;

void A_Top::indent(int d)
{
	std::cout << std::string(d, ' ');
}
