#include "A_UnaryExpr.h"

Value* A_UnaryExpr::Codegen() {
	Value* val = expr->Codegen();
	if(!val)
		return NULL;
	val = Builder.CreateNot(val);
	return Builder.CreateUIToFP(val, llvm::FunctionType::getDoubleTy(getGlobalContext()), "to_double");
}
