#pragma once

#include "A_Top.h"
using namespace std;

class A_Expr : public A_Top {
public:
	virtual ~A_Expr() {}
	virtual void Print(int d) {}
};
