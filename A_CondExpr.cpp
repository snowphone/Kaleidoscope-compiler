#include "A_CondExpr.h"

#include "auxiliary.h"

#include <llvm/IR/Function.h>
#include <llvm/IR/BasicBlock.h>
#include <llvm/IR/Constants.h>
#include <llvm/IR/Constant.h> 
#include <llvm/IR/Type.h>


using llvm::ConstantFP;	using llvm::APFloat;
using llvm::Function;	using llvm::BasicBlock;
using llvm::Type;		using llvm::PHINode;

A_CondExpr::~A_CondExpr() {
	delete this->cond_expr;
	delete this->then_expr;
	delete this->else_expr;
}

Value* A_CondExpr::Codegen() {
	Value* cond_ret = cond_expr->Codegen();
	if(!cond_ret)
		return NULL;

	// Same as 'if cond_ret != 0'
	cond_ret = Builder.CreateFCmpONE(cond_ret, ConstantFP::get(getGlobalContext(), APFloat(0.0)), "ifcond");

	Function* fn = Builder.GetInsertBlock()->getParent();

	BasicBlock *thenbb = BasicBlock::Create(getGlobalContext(), "then", fn),
			   *elsebb = BasicBlock::Create(getGlobalContext(), "else"),
			   *mergebb = BasicBlock::Create(getGlobalContext(), "ifcont");

	Builder.CreateCondBr(cond_ret, thenbb, elsebb);

	Builder.SetInsertPoint(thenbb);

	Value* then_ret = then_expr->Codegen();
	if(!then_ret)
		return NULL;
	Builder.CreateBr(mergebb);
	thenbb = Builder.GetInsertBlock();

	fn->getBasicBlockList().push_back(elsebb);
	Builder.SetInsertPoint(elsebb);

	Value* else_ret = else_expr->Codegen();
	if(!else_ret)
		return NULL;

	Builder.CreateBr(mergebb);
	elsebb = Builder.GetInsertBlock();

	fn->getBasicBlockList().push_back(mergebb);
	Builder.SetInsertPoint(mergebb);
	PHINode* pn = Builder.CreatePHI(Type::getDoubleTy(getGlobalContext()), 2, "iftmp");
	pn->addIncoming(then_ret, thenbb);
	pn->addIncoming(else_ret, elsebb);

	return pn;
}
