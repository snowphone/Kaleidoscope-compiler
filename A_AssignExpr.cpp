#include "A_AssignExpr.h"

Value* A_AssignExpr::Codegen() {
	Value* val = rval->Codegen();
	if(!val)
		return NULL;

	if(NamedValues[lval->GetName()])
		return LogErrorV("variable name '" + lval->GetName() + "' can't be assigned twice.");
	if(this->lval->getType()->getTypeID() != val->getType()->getTypeID()) {
		return LogErrorV("Type error.");
	}
	NamedValues[lval->GetName()] = val;

	return val;
}
