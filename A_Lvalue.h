#pragma once

#include "A_Identifier.h"

#include <llvm/IR/Type.h>

using llvm::Type;

class A_Lvalue: public A_Identifier {
	Type* type;
public:
	A_Lvalue(const string& id, Type* type = Type::getDoubleTy(getGlobalContext())) : A_Identifier(id), type(type) {}
	A_Lvalue(A_Identifier* id, Type* type = Type::getDoubleTy(getGlobalContext())) : A_Identifier(*id), type(type) {}
	Type* getType() { return type; }
};
