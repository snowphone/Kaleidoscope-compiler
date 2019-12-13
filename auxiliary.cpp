#include "auxiliary.h"

#include "A_Identifier.h"
#include "A_Prototype.h"
#include "A_Definition.h"
#include "A_CallExpr.h"
#include "A_External.h"

#include <string>
#include <iostream>
#include <algorithm>
#include <cstdio>

#include <llvm/IR/Value.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/ExecutionEngine/GenericValue.h>

using std::cerr;		using std::endl;
using std::string;		using llvm::GenericValue;
using llvm::ArrayRef;	using llvm::GenericValue;

llvm::LLVMContext& getGlobalContext() {
	static llvm::LLVMContext TheContext;
	return TheContext;
}

llvm::IRBuilder<> Builder(getGlobalContext());
map<string, Value*> NamedValues = map<string, Value*>();
Module* TheModule = NULL;
ExecutionEngine* engine = NULL;
A_TopList *aroot = NULL;
map<string, A_Prototype*> functionProtos = map<string, A_Prototype*>();
const string anon_func = "";

extern int yyparse(void);
extern FILE* yyin;

Value* LogErrorV(const string& reason) {
	cerr << "Error: " << reason << endl;
	return NULL;
}

string to_string(long long i) {
	char buf[128];
	sprintf(buf, "%lld", i);
	return buf;
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

static void dump() {
#ifdef __enable_jit__
	static bool isFirst = true;
	string buf;
	llvm::raw_string_ostream os(buf);
	os << *TheModule;
	os.flush();
	if(!isFirst) {
		if(buf.find("; ModuleID = ") != string::npos) {
			size_t i = buf.find_first_of('\n') + 1;
			buf.erase(buf.begin(), buf.begin() + i);
		}
		if(buf.find("source_filename ") != string::npos) {
			size_t i = buf.find_first_of('\n') + 1;
			buf.erase(buf.begin(), buf.begin() + i);
		}
		if(buf.find("target datalayout") != string::npos) {
			size_t i = buf.find_first_of('\n') + 1;
			buf.erase(buf.begin(), buf.begin() + i);
		}
	}
	isFirst = false;
	std::cerr << buf << endl;
#elif __clang_major__ == 3
	TheModule->dump();
#else
	TheModule->print(llvm::errs(), NULL);
#endif
}

Function* getFunction(string name) {
	if(Function* f = TheModule->getFunction(name))
		return f;
	map<string,A_Prototype*>::iterator it;
	if((it = functionProtos.find(name)) != functionProtos.end())
		return it->second->Codegen();
	return NULL;
}

void compile(A_TopList* tops) {
	Function* f;
	for(A_TopList::iterator it = tops->begin(); it != tops->end(); ++it) {
		if(A_Expr* e = dynamic_cast<A_Expr*>(*it)) {

			A_Prototype* proto = new A_Prototype(new A_Identifier(anon_func));
			A_Definition* func = new A_Definition(proto, new A_TopList(1, e));
			f = func->Codegen();

#ifdef __enable_jit__
			dump();

			Module* oldModule = TheModule;
			engine->addModule(PASS(TheModule));

			GenericValue val = engine->runFunction(f, ArrayRef<GenericValue>());
			const int length = 80;
			cerr << string(length, '-') << endl
				<< "Evaluated to " << std::fixed << val.DoubleVal << endl
				<< string(length, '-') << endl;

			engine->removeModule(oldModule);
			TheModule = new Module("Kaleidoscope Just-in-time Compiler", getGlobalContext());
			TheModule->setDataLayout(engine->getTargetMachine()->createDataLayout());
#endif

		} else {
			Value* v = (*it)->Codegen();
			f = static_cast<Function*>(v);
#ifdef __enable_jit__
			dump();
#endif
		}
	}
#ifndef __enable_jit__
	dump();
#endif
}
