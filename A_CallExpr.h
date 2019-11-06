#pragma once

#include "A_Expr.h"
using namespace std;

// A_CallExpr - Expr class for function calls.
class A_CallExpr : public A_Expr {
private:
	/*
	채워넣기
	*/
	A_TopList&		arguments;
public:
	A_CallExpr(/*채워넣기*/) : funcName(f), arguments(args) {}
	virtual void Print(int d);
};
