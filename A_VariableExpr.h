#pragma once

#include "A_Expr.h"
#include "A_Identifier.h"
#include <string>

using std::string;

// A_VariableExpr - Expr class for referencing a variable, like "a".
class A_VariableExpr : public A_Expr {
private:
	A_Identifier* id;
public:
	A_VariableExpr(A_Identifier* id) : id(id) {}
	virtual void Print(int d);
	virtual ~A_VariableExpr();
};

