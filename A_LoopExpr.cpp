#include "A_LoopExpr.h"

#include <llvm/IR/Function.h>
#include <llvm/IR/BasicBlock.h>
#include <llvm/IR/Type.h>
#include <llvm/IR/Constant.h>

#include <cassert>
#include <iostream>

using llvm::Function;	using llvm::BasicBlock;
using llvm::PHINode;	using llvm::Type;
using llvm::ConstantFP;	using llvm::APFloat;
using llvm::Constant;

Value* A_LoopExpr::Codegen() {
	Value* startVal = start->Codegen();
	if(!startVal)
		assert(0 && "startVal is not valid");


	Function* fn = Builder.GetInsertBlock()->getParent();
	BasicBlock* prehdrbb = Builder.GetInsertBlock(),
		*loopbb = BasicBlock::Create(getGlobalContext(), "loop", fn);

	Builder.CreateBr(loopbb);

	Builder.SetInsertPoint(loopbb);

	PHINode* variable = Builder.CreatePHI(Type::getDoubleTy(getGlobalContext()), 2, this->var->GetName());
	variable->addIncoming(startVal, prehdrbb);

	Value* oldVal = NamedValues[var->GetName()];
	NamedValues[var->GetName()] = variable;

	body->Codegen();

	if(!step)
		assert(0 && "step is not valid");
	Value* stepVal = step->Codegen();
	if(!stepVal)
		assert(0 && "step value is not valid");

	Value* nextVar = Builder.CreateFAdd(variable, startVal, "nextvar");

	Value* end_cond = end->Codegen();
	if(!end_cond)
		assert(0 && "end_cond is not valid");

	end_cond = Builder.CreateFCmpONE(end_cond, ConstantFP::get(getGlobalContext(), APFloat(0.)), "loopcond");

	BasicBlock *loopendbb = Builder.GetInsertBlock(),
			   *afterbb = BasicBlock::Create(getGlobalContext(), "afterloop", fn);

	Builder.CreateCondBr(end_cond, loopbb, afterbb);
	Builder.SetInsertPoint(afterbb);

	variable->addIncoming(nextVar, loopendbb);

	NamedValues[var->GetName()] = oldVal;

	return Constant::getNullValue(Type::getDoubleTy(getGlobalContext()));
}

