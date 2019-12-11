%{
extern int lines;

#include <iostream>
#include <vector>
#include <string>

#include <llvm/IR/Type.h>

#include "A_Top.h"
#include "A_Definition.h"
#include "A_Prototype.h"
#include "A_Identifier.h"
#include "A_External.h"
#include "A_NumberExpr.h"
#include "A_VariableExpr.h"
#include "A_BinaryExpr.h"
#include "A_CallExpr.h"
#include "A_CondExpr.h"
#include "A_AssignExpr.h"
#include "A_LoopExpr.h"
#include "A_UnaryExpr.h"
#include "A_ListExpr.h"
#include "A_Lvalue.h"

using std::cerr;	using std::endl;
using std::vector;


int yylex(void);
void yyerror(char* s) {
	cerr << "SCANNER ERROR: " << lines << " - " << s << endl;
	exit(1);
}
void generate(A_Top*);
%}

%union {
	double num;
	const char* id;
	A_External* ext;
	A_Definition* def;
	A_Identifier* ident;
	A_Lvalue* lv;
	A_TopList* toplist;
	A_Top* top;
	A_Prototype* proto;
	A_Expr* expr;
	llvm::Type* tp;
}


%token COMMENT EXTERN DEF  ';' 
%left ',' 
%token <num> NUMBER 
%token <id> ID 
%type<tp> type
%type <expr> expression numberExpr variableExpr binaryExpr callExpr condExpr assignExpr notExpr listExpr
%type <expr> loopExpr
%type <toplist> topList paramList expressionList
%type <ident> identifier
%type <def> definition
%type <lv> lvalue
%type <ext> external
%type <proto> prototype
%type <top> top 

%token END 0
%right '='
%left OR
%left AND 
%left EQ NE
%left '<' LE '>' GE
%left '+' '-'
%left '*' '/' '%'
%left '!'
%right UMINUS
%token '[' ']' ':' DOUBLE  

%token IF THEN FOR IN ELSE GET_ELEMENT
%token '(' ')'

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

definition : DEF prototype expressionList	{ $$ = new A_Definition($2, $3); }
		;

prototype : identifier '(' ')' 				{ $$ = new A_Prototype($1); }
		  | identifier '(' ')' ':' type				{ $$ = new A_Prototype($1, $5); }
		| identifier '(' paramList ')' ':' type	{ $$ = new A_Prototype($1, $6, $3); }
		| identifier '(' paramList ')' { $$ = new A_Prototype($1, $3); }
		;

identifier : ID		{ $$ = new A_Identifier(std::string($1)); }
		;

lvalue : type identifier  		{ $$ = new A_Lvalue($2, $1); }
lvalue : identifier 				{ $$ = new A_Lvalue($1); }
	   ;

paramList : lvalue					{ $$ = new A_TopList(1, $1); }
			|  paramList ',' lvalue	{ $1->push_back($3); $$ = $1; }
			;


type : DOUBLE { $$ = llvm::VectorType::getDoubleTy(getGlobalContext()); }
	 | '[' type '*' NUMBER ']' { $$ = llvm::VectorType::get($2, (int)$4); }
	 ;

expression : numberExpr			{ $$ = $1; }
		|  variableExpr			{ $$ = $1; }
		|  binaryExpr			{ $$ = $1; }
		|  callExpr				{ $$ = $1; }
		|  '(' expression ')'	{ $$ = $2; }
		|  condExpr				{ $$ = $1; }
		|  assignExpr			{ $$ = $1; }
		|  loopExpr 			{ $$ = $1; }
		|  notExpr 				{ $$ = $1; }
		|  listExpr				{ $$ = $1; }
		;

notExpr : '!' expression { $$ = new A_UnaryExpr($2); }
		;

listExpr : '[' expressionList ']'	{ $$ = new A_ListExpr($2); }
		  ;

loopExpr : FOR identifier '=' expression ',' expression ',' expression IN expression { $$ = new A_LoopExpr($2, $4, $6, $8, $10); }
		 ;

assignExpr : lvalue '=' expression { $$ = new A_AssignExpr($1, $3); }
		   ;

numberExpr : NUMBER	{ $$ = new A_NumberExpr($1); }
		   | '-' NUMBER { $$ = new A_NumberExpr(-$2); }
		;

variableExpr : identifier			{ $$ = new A_VariableExpr($1); }
			;

binaryExpr : expression '+' expression	{ $$ = new A_BinaryExpr('+', $1, $3); }
		|  expression '-' expression	{ $$ = new A_BinaryExpr('-', $1, $3); }
		|  expression '*' expression	{ $$ = new A_BinaryExpr('*', $1, $3); }
		|  expression '/' expression	{ $$ = new A_BinaryExpr('/', $1, $3); }
		|  expression '%' expression	{ $$ = new A_BinaryExpr('%', $1, $3); }
		|  expression '<' expression	{ $$ = new A_BinaryExpr('<', $1, $3); }
		|  expression LE expression		{ $$ = new A_BinaryExpr(LE, $1, $3); }
		|  expression '>' expression	{ $$ = new A_BinaryExpr('>', $1, $3); }
		|  expression GE expression		{ $$ = new A_BinaryExpr(GE, $1, $3); }
		|  expression EQ expression		{ $$ = new A_BinaryExpr(EQ, $1, $3); }
		|  expression NE expression		{ $$ = new A_BinaryExpr(NE, $1, $3); }
		|  expression AND expression	{ $$ = new A_BinaryExpr(AND, $1, $3); }
		|  expression OR expression		{ $$ = new A_BinaryExpr(OR, $1, $3); }
		;

callExpr : identifier '(' ')'				{ $$ = new A_CallExpr($1); }
		| identifier '(' expressionList ')'	{ $$ = new A_CallExpr($1, $3); }
		;

condExpr: IF expression THEN	expression	{ $$ = new A_CondExpr($2, $4); }
		| IF expression THEN	expression ELSE expression	{ $$ = new A_CondExpr($2, $4, $6); }
		;

expressionList : expression						{ $$ = new A_TopList(1, $1); }
			|  expressionList ',' expression	{ $1->push_back($3); $$ = $1; }
			;

external : EXTERN prototype	{ $$ = new A_External($2); }
		;
%%

