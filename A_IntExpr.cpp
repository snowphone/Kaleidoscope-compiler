#include "A_IntExpr.h"

#include <llvm/IR/Type.h>
#include <llvm/IR/Constant.h>

using llvm::Type;	using llvm::ConstantInt;

Value* A_IntExpr::Codegen() {
	return ConstantInt::get(Type::getInt64Ty(getGlobalContext()), i);
}
