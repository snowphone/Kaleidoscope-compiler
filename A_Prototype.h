#pragma once

#include "A_Top.h"

#include "A_Identifier.h"

#include <vector>

#include <llvm/IR/Function.h>

using llvm::Function;

// A_Prototype - This class represents the "prototype" for a function,
class A_Prototype : public A_Top {
private:
	A_Identifier*	ident;
	A_TopList*		paramList;
public:
	A_Prototype(A_Identifier* id, A_TopList* il = new A_TopList()) : ident(id), paramList(il) {}
	virtual void Print(int d) ;
	virtual ~A_Prototype() ;
	string GetName();
	Function* Codegen();
};
