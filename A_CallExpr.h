#pragma once

#include "A_Expr.h"
#include "A_Identifier.h"
#include <string>
#include <vector>

using std::string;

// A_CallExpr - Expr class for function calls.
class A_CallExpr : public A_Expr {
private:
	A_Identifier*	funcName;
	A_TopList*		arguments;
public:
	A_CallExpr(A_Identifier* f, A_TopList* args = new A_TopList()) : funcName(f), arguments(args) {}
	virtual void Print(int d);
	virtual ~A_CallExpr();
};
