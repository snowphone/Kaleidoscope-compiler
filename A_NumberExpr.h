#pragma once

#include "A_Expr.h"

#include <llvm/IR/Value.h>

using llvm::Value;

// A_NumberExpr - Expr class for numeric literals like "1.0".
class A_NumberExpr : public A_Expr {
private:
	double val;
public:
	A_NumberExpr(double v) : val(v) {}
	virtual void Print(int d) ;
	virtual Value* Codegen();
};
