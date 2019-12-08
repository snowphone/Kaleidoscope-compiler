#pragma once

#include "A_Expr.h"
#include "A_NumberExpr.h"

class A_CondExpr: public A_Expr {
	A_Expr *cond_expr,
		   *then_expr,
		   *else_expr;
public:
	A_CondExpr(A_Expr* cond_expr, A_Expr* then_expr, A_Expr* else_expr = new A_NumberExpr(0)) : cond_expr(cond_expr), then_expr(then_expr), else_expr(else_expr) {}

	virtual ~A_CondExpr();
	virtual Value* Codegen();
};
