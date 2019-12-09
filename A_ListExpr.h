#pragma once

#include "A_Expr.h"

#include "A_aux.h"

#include <llvm/IR/Constants.h>

using llvm::ConstantDataArray;

class A_ListExpr: public A_Expr {
	A_TopList* elements;
public:
	static Value* get_element(A_ListExpr* list, A_Expr* i);
	//static A_ListExpr* add(A_ListExpr* list, Value* item);
	//static A_ListExpr* remove(A_ListExpr* list, Value* item);
	//static Value* head(A_ListExpr* list);
	//static A_ListExpr* front(A_ListExpr* list);
	//static A_ListExpr* concat(A_ListExpr* lhs, A_ListExpr* rhs);

	A_ListExpr(A_TopList* elements): elements(elements) {}
	llvm::Constant* Codegen();
};
