#pragma once

#include "A_Top.h"
#include "A_Identifier.h"

// A_Prototype - This class represents the "prototype" for a function,
class A_Prototype : public A_Top {
private:
	A_Identifier	ident;
	A_TopList		paramList;
public:
	A_Prototype(const A_Identifier& id, const A_TopList& il = A_TopList()) : ident(id), paramList(il) {}
	virtual void Print(int d);
};
