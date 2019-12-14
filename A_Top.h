#pragma once

#include <vector>
#include <algorithm>
#include <string>
#include <map>

#include "auxiliary.h"	// A_TopList, Module, IRBuilder, and auxilary functions here

class A_Top {
public:
	virtual ~A_Top() {}
	void indent(int d);				// Set each node's depth.
	virtual void Print(int d) = 0;	// Print each node.
	virtual Value* Codegen() = 0;
};

