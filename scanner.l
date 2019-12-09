/* Author:	Junoh Moon 
 * ID: 		B611062
 */
/* Rules */
id			[a-zA-Z_][a-zA-Z0-9_]*
number		("."?[0-9]+|[0-9]+"."[0-9]*)
comment		"#".*
%{
int lines = 1;
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
#include "A_CondExpr.h"
#include "A_AssignExpr.h"
#include "A_LoopExpr.h"
#include "A_UnaryExpr.h"

#include "parser.h"

extern "C" int yywrap(void) { return 1; }
%}
%%
\n				++lines;
"if"			return IF;
"then"			return THEN;
"else"			return ELSE;
def 			return DEF;
extern 			return EXTERN;
for				return FOR;
in 				return IN;
{id}			{ yylval.id = yytext; return ID; }
{number}		{ yylval.num = atof(yytext); return NUMBER;}
{comment}		/* Comment */
"+"				return '+';
"-"				return '-';
"*"				return '*';
"/"				return '/';
"%"				return '%';
"<"				return '<';
">"				return '>';
"="				return '=';
"<="			return LE;
">="			return GE;
"=="			return EQ;
"!="			return NE;
"("				return '(';
")"				return ')';
","				return ',';
";"				return ';';
"&&"			return AND;
"||"			return OR;
"!"				return '!';
[ \r\t]			/* White space */
<<EOF>>			return END;
%%
#ifdef ENABLE_SCANNER_MAIN
int main(int argc, char* argv[]) {
	int type;
	while((type = yylex()) != END) {
		switch(type) {
			case ID:
				printf("%d\t%s\n", ID, yytext);
				break;
			case NUMBER:
				printf("%d\t%s\n", NUMBER, yytext);
				break;
			case COMMENT:
				printf("comment\t%d\n", lines);
				break;
			default:
				printf("%d\n", type);
				break;
		}
	}
}
#endif
