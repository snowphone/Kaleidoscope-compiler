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

#ifdef NEW_CLANG
LLVMContext& getGlobalContext();
#else
using llvm::getGlobalContext;
#endif

class A_Top;
typedef std::vector<A_Top*>		A_TopList;

extern IRBuilder<> Builder;
extern Module* TheModule;
extern map<string, Value*> NamedValues;

extern A_TopList *aroot;

class A_Top {
public:
	virtual ~A_Top() {}
	void indent(int d);				// 각 노드의 깊이를 지정해준다.
	virtual void Print(int d) = 0;	// 노드를 출력한다.
	virtual Value* Codegen() = 0;
};

