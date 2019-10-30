/* Author:	Junoh Moon 
 * ID: 		B611062
 */
/* Rules */
identifier	[a-z][a-z0-9]*
number		"."?[0-9]+|[0-9]+"."[0-9]*
keyword		"def"|"extern"
operator	[-+*]
punctuation "("|")"|","|";"
comment		"#".*
%{
int lines = 1;

enum TOKEN_TYPES {
	def = 256,
	ext,
	comment,
	number,
	identifier,
	plus = '+',
	minus = '-',
	mul = '*',
	lparan = '(',
	rparan = ')',
	colon = ',',
	semicolon = ';',
};
%}
%%
\n				++lines;
def 			return def;
extern 			return ext;
{identifier}	return identifier;
{number}		return number;
{comment}		return comment;
"+"				return plus;
"-"				return minus;
"*"				return mul;
"("				return lparan;
")"				return rparan;
","				return colon;
";"				return semicolon;
[ \r\t]			/* White space */
<<EOF>>			return EOF;
%%
int main(int argc, char* argv[]) {
	int type;
	while((type = yylex()) != EOF) {
		switch(type) {
			case identifier:
				printf("%d\t%s\n", identifier, yytext);
				break;
			case number:
				printf("%d\t%s\n", number, yytext);
				break;
			case comment:
				printf("comment\t%d\n", lines);
				break;
			default:
				printf("%d\n", type);
				break;
		}
	}
}
