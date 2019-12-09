#include "A_ListExpr.h"

#include <llvm/IR/Constants.h>

#include <vector>
#include <algorithm>
#include <iterator>

using llvm::Constant;	using std::vector;
using llvm::ConstantDataArray;
using llvm::ArrayRef;
using llvm::makeArrayRef;
using llvm::Type;
using llvm::ConstantArray;
using llvm::ArrayType;
using std::transform;

static Constant* gen_constant(A_Top* elem) {
	A_Expr* expr = dynamic_cast<A_Expr*>(elem);
	if(expr)
		return (Constant*)expr->Codegen();
	else
		return (Constant*)(LogErrorV("Can not cast from A_Top to A_Expr"));
}

static bool verify_type(const vector<Constant*>& elems) {
	for(size_t i = 1; i < elems.size(); ++i) {
		if(elems.front()->getType() != elems[i]->getType())
			return false;
	}
	return true;
}

Value* A_ListExpr::get_element(A_ListExpr* list, A_Expr* i) {
	Value* v = i->Codegen();
	if(!v->getType()->isDoubleTy()){
		return LogErrorV("The type of index must be numeric");
	}
	llvm::ConstantFP* d = static_cast<llvm::ConstantFP*>(v);
	size_t idx = d->getValueAPF().convertToDouble();
	if(idx >= list->elements->size())
		return LogErrorV("Index is out of bound");
	return list->Codegen()->getAggregateElement(idx);
}

Constant* A_ListExpr::Codegen() {
	vector<Constant*> elems;
	transform(elements->begin(), elements->end(), std::back_inserter(elems), gen_constant);
	//if(!verify_type(elems))
	//	return LogErrorV("Every element in the array must have a same type");

	//Type* elem_t = elems.front()->getType();
	//ArrayType* array_t = ArrayType::get(elem_t, elems.size());

	Constant* array = llvm::ConstantVector::get(makeArrayRef(elems));

	return array;
}

