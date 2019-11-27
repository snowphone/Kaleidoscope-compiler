#include "A_BinaryExpr.h"
#include <typeinfo>
#include <iostream>

using std::cout;
using std::endl;

void A_BinaryExpr::Print(int d)
{
	indent(d);
	cout << "binaryExpr: " << oper << endl;
	left->Print(d+2);	
	right->Print(d+2);

}

A_BinaryExpr::~A_BinaryExpr() {
	delete this->left;
	delete this->right;
}

llvm::Value* A_BinaryExpr::Codegen() {
	Value *lhs = left->Codegen(),
		  *rhs = right->Codegen();

	if(!lhs || !rhs)
		return NULL;

	switch(oper) {
		case '+':
			return Builder.CreateFAdd(lhs, rhs, "add");
		case '-':
			return Builder.CreateFSub(lhs, rhs, "subtract");
		case '*':
			return Builder.CreateFMul(lhs, rhs, "multiply");
		case '/':
			return Builder.CreateFDiv(lhs, rhs, "divide");
		default:
			return LogErrorV("Invalid binary operator");
	}
}
