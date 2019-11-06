#pragma once

#include "A_Top.h"

// A_Prototype - This class represents the "prototype" for a function,
class A_Prototype : public A_Top {
private:
	/*
	채워넣기
	*/
public:
	A_Prototype(/*채워넣기*/) : ident(id), paramList(il) {}
	virtual void Print(int d);
};
