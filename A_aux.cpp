#include "A_aux.h"

#include "A_Identifier.h"
#include "A_Prototype.h"
#include "A_Definition.h"

#include <string>
#include <iostream>

#include <llvm/IR/Value.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/LLVMContext.h>

using std::cerr;	using std::endl;

llvm::LLVMContext& getGlobalContext() {
	static llvm::LLVMContext TheContext;
	return TheContext;
}

llvm::IRBuilder<> Builder(getGlobalContext());
map<string, Value*> NamedValues = map<string, Value*>();
Module* TheModule = NULL;

A_TopList *aroot = NULL;

extern int yyparse(void);
extern FILE* yyin;

Value* LogErrorV(const char* reason) {
	cerr << "Error: " << reason << endl;
	return NULL;
}

void StartParse(const char* path) {
	yyin = fopen(path, "r");
	yyparse();
	fclose(yyin);
}

void free_tree() {
	/* Free memory */
	for(A_TopList::iterator it = aroot->begin(); it != aroot->end(); ++it) {
		delete *it;
	}
	delete aroot;
}


void generate(A_Top* top) {
	A_Expr* expr = dynamic_cast<A_Expr*>(top);
	if(expr) {
		A_Prototype* proto = new A_Prototype(new A_Identifier(""));
		A_Definition* func = new A_Definition(proto, expr);
		func->Codegen();
	} else {
		top->Codegen();
	}

}
