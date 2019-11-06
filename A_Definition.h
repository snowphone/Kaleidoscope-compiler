#pragma once

#include "A_Top.h"

// A_Definition - This class represents a function definition itself.
class A_Definition : public A_Top {
private:
	/*
	채워넣기
	*/
public:
	A_Definition(/*채워넣기*/) : header(h), body(b) {}
	virtual void Print(int d);
};

