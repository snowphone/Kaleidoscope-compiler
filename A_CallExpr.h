#pragma once

#include "A_Expr.h"
#include <string>
#include <vector>

using std::string;

// A_CallExpr - Expr class for function calls.
class A_CallExpr : public A_Expr {
private:
	string		funcName;
	A_TopList	arguments;
public:
	A_CallExpr(const string& f, const A_TopList& args = A_TopList()) : funcName(f), arguments(args) {}
	virtual void Print(int d);
};
