#pragma once

#include "A_Expr.h"

class A_IntExpr: public A_Expr {
	long long i;
public:
	A_IntExpr(long long i): i(i) {}
	virtual Value* Codegen();
};
