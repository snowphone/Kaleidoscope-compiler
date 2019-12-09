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
#include "auxiliary.h"	// StartParse, free_tree, TheModule, getGlobalContext

#include <llvm/IR/Module.h>
#include <llvm/Support/raw_ostream.h>

using std::cerr;	using std::endl;
using std::vector;	using std::cout;

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

