#include "A_BinaryExpr.h"

#include "A_External.h"
#include "A_Definition.h"
#include "A_Lvalue.h"

#include "parser.h"

#include <typeinfo>
#include <iostream>

using std::cout; using std::endl;
using llvm::FunctionType;

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
		case '%':
			return Builder.CreateFRem(lhs, rhs, "modulo");
		case '<':
			lhs = Builder.CreateFCmpULT(lhs, rhs, "less_than");
			return Builder.CreateUIToFP(lhs, FunctionType::getDoubleTy(getGlobalContext()), "to_double");
		case LE:
			lhs = Builder.CreateFCmpULE(lhs, rhs, "less_than_or_equal");
			return Builder.CreateUIToFP(lhs, FunctionType::getDoubleTy(getGlobalContext()), "to_double");
		case '>':
			lhs = Builder.CreateFCmpUGT(lhs, rhs, "greater_than");
			return Builder.CreateUIToFP(lhs, FunctionType::getDoubleTy(getGlobalContext()), "to_double");
		case GE:
			lhs = Builder.CreateFCmpUGT(lhs, rhs, "greater_than_or_equal");
			return Builder.CreateUIToFP(lhs, FunctionType::getDoubleTy(getGlobalContext()), "to_double");
		case EQ:
			lhs = Builder.CreateFCmpUEQ(lhs, rhs, "equal");
			return Builder.CreateUIToFP(lhs, FunctionType::getDoubleTy(getGlobalContext()), "to_double");
		case NE:
			lhs = Builder.CreateFCmpUNE(lhs, rhs, "not_equal");
			return Builder.CreateUIToFP(lhs, FunctionType::getDoubleTy(getGlobalContext()), "to_double");
		case AND:
			lhs = Builder.CreateAnd(lhs, rhs, "logical_and");
			return Builder.CreateUIToFP(lhs, FunctionType::getDoubleTy(getGlobalContext()), "to_double");
		case OR:
			lhs = Builder.CreateOr(lhs, rhs, "logical_or");
			return Builder.CreateUIToFP(lhs, FunctionType::getDoubleTy(getGlobalContext()), "to_double");
		default:
			return LogErrorV("Invalid binary operator");
	}
}
