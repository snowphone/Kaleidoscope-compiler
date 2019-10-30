%token DEF EXT COMMENT NUMBER ID '+' '-' '*' '(' ')' ',' ';'

%start program

%%

program : topList EOF

topList : top ';'
		  topList ';'

top	: definition
	  external 
	  expression

definition : DEF prototype expression

prototype : identifier '(' ')'
		  identifier '(' identifierList ')'

identifier : ID

identifierList : identifier
			   identifierList ',' identifier

expression : numberExpr
		   variableExpr
		   binaryExpr
		   callExpr
		   '(' expression ')'

numberExpr : NUMBER

variableExpr : identifier

binaryExpr : expression '+' expression
		   expression '-' expression
		   expression '*' expression

callExpr : identifier '(' ')'
		  identifier '(' expressionList ')'

expressionList : expression
			   expressionList ',' expression

external : EXT prototype




