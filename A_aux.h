#pragma once

#include <vector>
#include <algorithm>
#include <string>
#include <map>

#include <llvm/IR/Value.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/LLVMContext.h>


using llvm::Value;	using std::string;
using std::map;		using llvm::LLVMContext;
using llvm::Module;	using llvm::IRBuilder;


LLVMContext& getGlobalContext();
class A_Top;
typedef std::vector<A_Top*>		A_TopList;

extern IRBuilder<> Builder;
extern Module* TheModule;
extern map<string, Value*> NamedValues;

extern A_TopList *aroot;

Value* LogErrorV(const char* reason);

void generate(A_Top* top);
void StartParse(const char* path);
void free_tree();

