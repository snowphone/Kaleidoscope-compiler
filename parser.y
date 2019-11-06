%{
extern int lines;
#include <stdio.h>

int yylex(void);
void yyerror(char* s) {
	fprintf(stderr, "FAIL!\nERROR: %d - %s\n", lines, s);
}
%}
%token DEF EXTERN COMMENT NUMBER ID '(' ')' ',' ';'
%token END 0
%left '+' '-'
%left '*'
%start program
%%

program : topList END
		;

topList : top ';'
		| topList top ';'
		;

top	: definition
	| external
	| expression
	;

definition : DEF prototype expression
		;

prototype : identifier '(' ')'
		| identifier '(' identifierList ')'
		;

identifier : ID
		;

identifierList : identifier
			|  identifier ',' identifierList
			;

expression : numberExpr
		|  variableExpr
		|  binaryExpr
		|  callExpr
		|  '(' expression ')'
		;

numberExpr : NUMBER
		;

variableExpr : identifier
			;

binaryExpr : expression '+' expression
		|  expression '-' expression
		|  expression '*' expression
		;

callExpr : identifier '(' ')'
		| identifier '(' expressionList ')'
		;

expressionList : expression
			|  expressionList ',' expression
			;

external : EXTERN prototype
		;
%%

int main(void) {
	int result = yyparse();
	if(result == 0) {
		puts("PASS!");
	} 
}

