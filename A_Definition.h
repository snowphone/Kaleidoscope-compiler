#pragma once

#include "A_Top.h"
#include "A_Prototype.h"
#include "A_Expr.h"

// A_Definition - This class represents a function definition itself.
class A_Definition : public A_Top {
private:
	A_Prototype*	header;
	A_Expr*			body;
public:
	A_Definition(A_Prototype* h, A_Expr* b) : header(h), body(b) {}
	virtual void Print(int d);
};

