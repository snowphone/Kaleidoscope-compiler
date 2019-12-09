#pragma once

#include "A_Expr.h"

#include "auxiliary.h"
#include "A_Identifier.h"

class A_AssignExpr: public A_Expr {
	A_Identifier* lval;
	A_Expr* rval;
public:
	A_AssignExpr(A_Identifier* lval, A_Expr* rval) : lval(lval), rval(rval) {}
	virtual Value* Codegen();
};
