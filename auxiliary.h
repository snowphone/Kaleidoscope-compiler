#pragma once

#include <vector>
#include <algorithm>
#include <string>
#include <map>

#include <llvm/IR/Value.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/ExecutionEngine/ExecutionEngine.h>


using llvm::Value;	using std::string;
using std::map;		using llvm::LLVMContext;
using llvm::Module;	using llvm::IRBuilder;
using llvm::ExecutionEngine;


LLVMContext& getGlobalContext();
class A_Top;
typedef std::vector<A_Top*>		A_TopList;

extern IRBuilder<> Builder;
extern Module* TheModule;
extern map<string, Value*> NamedValues;
extern ExecutionEngine* engine;

extern A_TopList *aroot;

Value* LogErrorV(const string& reason);

void StartParse(const char* path);
void free_tree();
void generate(A_Top* top);
void compile(A_TopList* tops);

