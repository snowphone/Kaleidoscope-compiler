#pragma once

#include "A_Top.h"

#include <string>

#include <llvm/IR/Value.h>

using std::string;	using llvm::Value;

class A_Identifier : public A_Top {
private:
	string name;
public:
	A_Identifier(const string& n) : name(n) {}
	virtual void Print(int d) ;
	string GetName();
	virtual Value* Codegen();
};
