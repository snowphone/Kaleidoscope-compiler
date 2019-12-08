#include "A_AssignExpr.h"

Value* A_AssignExpr::Codegen() {
	Value* val = rval->Codegen();
	if(!val)
		return NULL;

	if(NamedValues[lval->GetName()])
		return LogErrorV("variable name '" + lval->GetName() + "' can't be assigned twice.");
	NamedValues[lval->GetName()] = val;

	//Builder.CreateStore(val, var);

	return val;
}
