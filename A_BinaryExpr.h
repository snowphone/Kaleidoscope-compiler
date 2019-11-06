#pragma once

#include "A_Expr.h"
using namespace std;

typedef std::vector<A_Top*>		A_TopList;

extern A_TopList *aroot;

// A_BinaryExpr - Expr class for a binary operator.
class A_BinaryExpr : public A_Expr {
private:
	char		oper;
	A_Expr&	left;
	A_Expr& right;

public:
	A_BinaryExpr(char op, A_Expr& lhs, A_Expr& rhs) : oper(op), left(lhs), right(rhs) {}
	virtual void Print(int d);
};
