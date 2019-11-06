#pragma once

#include "A_Top.h"
#include "A_Prototype.h"

class A_External : public A_Top {
private:
	A_Prototype&	prototype;
public:
	A_External(A_Prototype& proto) : prototype(proto) {}
	virtual void Print(int d);
};
