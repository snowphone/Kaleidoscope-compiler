#pragma once

#include "A_Top.h"
#include "A_Prototype.h"
#include "A_Expr.h"

#include <llvm/IR/Function.h>

using llvm::Function;

// A_Definition - This class represents a function definition itself.
class A_Definition : public A_Top {
private:
	A_Prototype*	header;
	A_TopList*			body;
public:
	A_Definition(A_Prototype* h, A_TopList* b) : header(h), body(b) {}
	virtual void Print(int d);
	virtual ~A_Definition();
	Function* Codegen();
};

