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
#include <llvm/Support/TargetSelect.h>
#include <llvm/ExecutionEngine/ExecutionEngine.h>


using std::cerr;	using std::endl;
using std::vector;	using std::cout;
using std::string;
using llvm::Module;
using llvm::EngineBuilder;

int main(int argc, const char* argv[]) {

	if(argc != 2) {
		cerr << "Usage: " << argv[0] << " <filename>\n" << endl;
		exit(1);
	}

	llvm::InitializeNativeTarget();
	llvm::InitializeNativeTargetAsmPrinter(); 
	llvm::InitializeNativeTargetAsmParser();


	TheModule = new Module("Kaleidoscope Just-in-time Compiler", getGlobalContext());
	auto uniModule = std::unique_ptr<Module>(TheModule);
	string err;
	engine = EngineBuilder(std::move(uniModule))
		.setErrorStr(&err)
		.setEngineKind(llvm::EngineKind::JIT)
		.create();

	if(!engine) {
		cerr << "Could not create ExecutionEngine: " << err << endl;
		return 1;
	}

	StartParse(argv[1]);
	compile(aroot);

	free_tree();
	return 0;
} 

