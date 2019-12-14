#pragma once

#include "A_Expr.h"
#include "A_Identifier.h"

class A_LoopExpr: public A_Expr {
	A_Identifier* var;
	A_Expr* start, *end, *step, *body;
public:
	A_LoopExpr(A_Identifier* var, A_Expr* start, A_Expr* end, A_Expr* step, A_Expr* body): var(var), start(start), end(end), step(step), body(body) {}
	virtual Value* Codegen();
};
