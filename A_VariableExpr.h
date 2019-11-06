#pragma once

#include "A_Expr.h"

// A_VariableExpr - Expr class for referencing a variable, like "a".
class A_VariableExpr : public A_Expr {
private:
	/*
	채워넣기
	*/
public:
	A_VariableExpr(/*채워넣기*/) : ident(id) {}
	virtual void Print(int d);
};

