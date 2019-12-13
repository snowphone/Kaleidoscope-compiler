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

static Value* intToDouble(Value* v) {
	return Builder.CreateUIToFP(v, FunctionType::getDoubleTy(getGlobalContext()), "to_double");
}

llvm::Value* A_BinaryExpr::Codegen() {
	Value *lhs = left->Codegen(),
		  *rhs = right->Codegen();

	if(lhs->getType()->isVectorTy() || rhs->getType()->isVectorTy())
		return LogErrorV("A_BinaryExpr: List type is not supported");
	if(!lhs || !rhs)
		return NULL;

	if(lhs->getType()->getTypeID() != rhs->getType()->getTypeID()) {
		// Promote int to double
		if(lhs->getType()->isIntegerTy())
			lhs = Builder.CreateSIToFP(lhs, Type::getDoubleTy(getGlobalContext()));
		if(rhs->getType()->isIntegerTy())
			rhs = Builder.CreateSIToFP(rhs, Type::getDoubleTy(getGlobalContext()));
	}

#define CALC(OP, L, R) L->getType()->isIntegerTy() ? Builder.Create ## OP(L, R, #OP) : Builder.CreateF ## OP(L, R, #OP);
#define CALCS(OP, L, R) L->getType()->isIntegerTy() ? Builder.CreateS ## OP(L, R, #OP) : Builder.CreateF ## OP(L, R, #OP);
#define CALCIU(OP, L, R) L->getType()->isIntegerTy() ? Builder.CreateICmpU ## OP(L, R, #OP) : Builder.CreateFCmpU ## OP(L, R, #OP);
#define CALCI(OP, L, R) L->getType()->isIntegerTy() ? Builder.CreateICmp ## OP(L, R, #OP) : Builder.CreateFCmpU ## OP(L, R, #OP);

	switch(oper) {
		case '+':
			return CALC(Add, lhs, rhs);
		case '-':
			return CALC(Sub, lhs, rhs);
		case '*':
			return CALC(Mul, lhs, rhs);
		case '/':
			return CALCS(Div, lhs, rhs);
		case '%':
			return CALCS(Rem, lhs, rhs);
		case '<':
			return CALCIU(LT, lhs, rhs);
		case LE:
			return CALCIU(LT, lhs, rhs);
		case '>':
			return CALCIU(GT, lhs, rhs);
		case GE:
			return CALCIU(GE, lhs, rhs);
		case EQ:
			return CALCI(EQ, lhs, rhs);
		case NE:
			return CALCI(NE, lhs, rhs);
		case AND:
			return Builder.CreateAnd(lhs, rhs);
		case OR:
			return Builder.CreateOr(lhs, rhs);
		default:
			return LogErrorV("Invalid binary operator");
	}
}
