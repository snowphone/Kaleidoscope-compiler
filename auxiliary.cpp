#include "auxiliary.h"

#include "A_Identifier.h"
#include "A_Prototype.h"
#include "A_Definition.h"
#include "A_CallExpr.h"
#include "A_External.h"

#include <string>
#include <iostream>

#include <llvm/IR/Value.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Verifier.h>

using std::cerr;	using std::endl;
using std::string;
using llvm::verifyFunction;

llvm::LLVMContext& getGlobalContext() {
	static llvm::LLVMContext TheContext;
	return TheContext;
}

llvm::IRBuilder<> Builder(getGlobalContext());
map<string, Value*> NamedValues = map<string, Value*>();
Module* TheModule = NULL;
ExecutionEngine* engine = NULL;
A_TopList *aroot = NULL;

extern int yyparse(void);
extern FILE* yyin;

Value* LogErrorV(const string& reason) {
	cerr << "Error: " << reason << endl;
	return NULL;
}

void StartParse(const char* path) {
	yyin = fopen(path, "r");
	if(!yyin) {
		fprintf(stderr, "Failed to open %s\n", path);
		exit(1);
	}
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

void compile(A_TopList* tops) {
	const string anon_func = "__ANON_EXPR";
	Function* f, *cf;
	for(A_TopList::iterator it = tops->begin(); it != tops->end(); ++it) {
		if(A_Expr* e = dynamic_cast<A_Expr*>(*it)) {
			A_Prototype* proto = new A_Prototype(new A_Identifier(anon_func));
			A_Definition* func = new A_Definition(proto, new A_TopList(1, e));
			cf = f = func->Codegen();
		} else {
			f = static_cast<Function*>((*it)->Codegen());
		}
		verifyFunction(*f);
	}
	TheModule->print(llvm::errs(), NULL);
	double (*fp)() = (double (*)())engine->getFunctionAddress(anon_func);
	cerr << string(15, '-') << endl
		<< "Evaluated to " << fp() << endl
		<< string(15, '-') << endl;
}

