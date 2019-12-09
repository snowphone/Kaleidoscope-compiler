#pragma once

#include "A_Expr.h"
#include "A_aux.h"

class A_UnaryExpr: public A_Expr {
	A_Expr* expr;
public:
	A_UnaryExpr(A_Expr* expr) : expr(expr) {}
	virtual Value* Codegen();
};
