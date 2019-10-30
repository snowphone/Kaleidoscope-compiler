/* Author:	Junoh Moon 
 * ID: 		B611062
 */
/* Rules */
id			[a-z][a-z0-9]*
number		"."?[0-9]+|[0-9]+"."[0-9]*
comment		"#".*
%{
int lines = 1;
#include "y.tab.h"
%}
%%
\n				++lines;
def 			return DEF;
extern 			return EXTERN;
{id}			return ID;
{number}		return NUMBER;
{comment}		/* Comment */
"+"				return '+';
"-"				return '-';
"*"				return '*';
"("				return '(';
")"				return ')';
","				return ',';
";"				return ';';
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
