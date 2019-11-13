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

using std::cerr;	using std::endl;
using std::vector;	using std::cout;

extern int yyparse(void);
void StartParse(const char* path);

extern FILE* yyin;

int main(int argc, const char** argv) {

	if(argc != 2) {
		fprintf(stderr, "usage: %s <filename>\n", argv[0]);
		exit(1);
	}

	StartParse(argv[1]);

	return 0;
} 


void StartParse(const char* path) {
	yyin = fopen(path, "r");

	int result = yyparse();
	if(result == 0) {
		cout << "Parsing..." << endl
			<< 	string(15, '-') << " AST " << string(15, '-') << endl;
		for(A_TopList::iterator it = aroot->begin(); it != aroot->end(); ++it) {
			(*it)->Print(0);
		}
		cout << string(35, '-') << endl;
		/* Free memory */
		for(A_TopList::iterator it = aroot->begin(); it != aroot->end(); ++it) {
			delete *it;
		}
		delete aroot;
	}

	fclose(yyin);
}
