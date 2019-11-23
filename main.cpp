#include <cstdio>
#include <iostream>
#include <vector>
#include <string>

#include "A_Top.h"
#include "A_Definition.h"
#include "A_Prototype.h"
#include "A_Identifier.h"
#include "A_External.h"
#include "A_NumberExpr.h"
#include "A_VariableExpr.h"
#include "A_BinaryExpr.h"
#include "A_CallExpr.h"

#include <llvm/IR/Module.h>
#include <llvm/Support/raw_ostream.h>

using std::cerr;	using std::endl;
using std::vector;	using std::cout;

extern int yyparse(void);
void StartParse(const char* path);
void free_tree();

extern FILE* yyin;

int main(int argc, const char* argv[]) {

	if(argc != 2) {
		cerr << "Usage: " << argv[0] << " <filename>\n" << endl;
		exit(1);
	}

	TheModule = new llvm::Module(argv[1], getGlobalContext());
	StartParse(argv[1]);
	TheModule->print(llvm::errs(), NULL);


	free_tree();
	return 0;
} 

void free_tree() {
	/* Free memory */
	for(A_TopList::iterator it = aroot->begin(); it != aroot->end(); ++it) {
		delete *it;
	}
	delete aroot;
}

void StartParse(const char* path) {
	yyin = fopen(path, "r");

	yyparse();
	
	fclose(yyin);
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
