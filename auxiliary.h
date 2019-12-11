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
using llvm::Function;
using llvm::ExecutionEngine;

#if __clang_major__ == 3
	#define PASS(X)  (X)
#else
	#define PASS(X) (std::unique_ptr<Module>(X))
#endif

LLVMContext& getGlobalContext();
class A_Top;
class A_Prototype;
typedef std::vector<A_Top*>		A_TopList;

extern const string anon_func;

extern IRBuilder<> Builder;
extern Module* TheModule;
extern map<string, Value*> NamedValues;
extern ExecutionEngine* engine;
extern map<string, A_Prototype*> functionProtos;

extern A_TopList *aroot;

Value* LogErrorV(const string& reason);

string to_string(long long i);
void StartParse(const char* path);
void free_tree();
void generate(A_Top* top);
void compile(A_TopList* tops);
Function* getFunction(string name);
