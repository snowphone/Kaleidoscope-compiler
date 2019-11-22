#include "A_NumberExpr.h"

#include <typeinfo>
#include <iostream>

#include <llvm/IR/Constants.h>
#include <llvm/IR/Type.h>

using std::cout;	using std::endl;
using llvm::Type;	using llvm::ConstantFP;

void A_NumberExpr::Print(int d) {
	indent(d);
	cout << std::fixed << "numberExpr: " << val << endl;
}

Value* A_NumberExpr::Codegen() {
	return ConstantFP::get(Type::getDoubleTy(getGlobalContext()), this->val);
}
