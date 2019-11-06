#pragma once

#include "A_Expr.h"
using namespace std;

// A_NumberExpr - Expr class for numeric literals like "1.0".
class A_NumberExpr : public A_Expr {
private:
	double val;
public:
	A_NumberExpr(double v) : val(v) {}
	virtual void Print(int d);
};
