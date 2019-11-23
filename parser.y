%{
extern int lines;

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
using std::vector;


int yylex(void);
void yyerror(char* s) {
	cerr << "FAIL!" << endl << "ERROR: " << lines << " - " << s << endl;
	exit(1);
}

%}

%union {
	double num;
	const char* id;
	A_External* ext;
	A_Definition* def;
	A_Identifier* ident;
	A_TopList* toplist;
	A_Top* top;
	A_Prototype* proto;
	A_Expr* expr;
}


%token COMMENT EXTERN DEF '(' ')' ',' ';'
%token <num> NUMBER 
%token <id> ID 
%type <expr> expression numberExpr variableExpr binaryExpr callExpr
%type <toplist> topList identifierList expressionList
%type <ident> identifier
%type <def> definition
%type <ext> external
%type <proto> prototype
%type <top> top 

%token END 0
%left '+' '-'
%left '*'
%right UMINUS
%start program
%%

program : topList END	{ aroot = $1; }
		;

topList : top ';'			{ $$ = new A_TopList(1, $1); }
		| topList top ';'	{ $1->push_back($2); $$ = $1; }
		;

top	: definition	{ $$ = $1; }
	| external		{ $$ = $1; }
	| expression	{ $$ = $1; }
	;

definition : DEF prototype expression	{ $$ = new A_Definition($2, $3); }
		;

prototype : identifier '(' ')'				{ $$ = new A_Prototype($1); }
		| identifier '(' identifierList ')'	{ $$ = new A_Prototype($1, $3); }
		;

identifier : ID		{ $$ = new A_Identifier(std::string($1)); }
		;

identifierList : identifier						{ $$ = new A_TopList(1, $1); }
			|  identifierList ',' identifier	{ $1->push_back($3); $$ = $1; }
			;

expression : numberExpr			{ $$ = $1; }
		|  variableExpr			{ $$ = $1; }
		|  binaryExpr			{ $$ = $1; }
		|  callExpr				{ $$ = $1; }
		|  '(' expression ')'	{ $$ = $2; }
		;

numberExpr : NUMBER	{ $$ = new A_NumberExpr($1); }
		   | '-' NUMBER { $$ = new A_NumberExpr(-$2); }
		;

variableExpr : identifier	{ $$ = new A_VariableExpr($1); }
			;

binaryExpr : expression '+' expression	{ $$ = new A_BinaryExpr('+', $1, $3); }
		|  expression '-' expression	{ $$ = new A_BinaryExpr('-', $1, $3); }
		|  expression '*' expression	{ $$ = new A_BinaryExpr('*', $1, $3); }
		;

callExpr : identifier '(' ')'				{ $$ = new A_CallExpr($1); }
		| identifier '(' expressionList ')'	{ $$ = new A_CallExpr($1, $3); }
		;

expressionList : expression						{ $$ = new A_TopList(1, $1); }
			|  expressionList ',' expression	{ $1->push_back($3); $$ = $1; }
			;

external : EXTERN prototype	{ $$ = new A_External($2); }
		;
%%

