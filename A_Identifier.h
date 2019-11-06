#pragma once

#include "A_Top.h"

class A_Identifier : public A_Top {
private:
	std::string name;
public:
	A_Identifier(std::string& n) : name(n) {}
	virtual void Print(int d);
};
