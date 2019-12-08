# Kaleidoscope-compiler
A compiler for the Kaleidoscope language. Written in C++ with lex/yacc and generate LLVM IR.

## Status
* Identifier: lower case alphanumeric string only.
* Literal:  numeric
* Operator: addition, subtraction, multiplication

## TODO
* ~~Identifier: capital letters, underscore~~
* ~~Arithmetic operators:~~
  * ~~division~~   
  * ~~mod~~     
  * ~~unary minus~~
* ~~Relational operators~~
* Boolean operators
* Additional types
  * Integer
  * Array
* ~~Control structure~~
  * ~~if-then~~
  * ~~if-then-else~~
  * ~~if-else if-else~~
* ~~Loop structure~~
* Variables
  * Global 
  * Local
* Assignment
  * "="
  * compound assignments

## 메뉴얼
* 연산자
	* 산술 연산자
	~~~
	1. + .2;	# 덧셈
	3.14 - 0;	# 뺄셈
	3.14 * 10;	# 곱셈
	-1 / 10;	# 나눗셈
	7 % 5.2;		# 나머지
	~~~
	* 비교 연산자
	~~~
	x < y;
	x <= y;
	x > y;
	x >= y;
	x == y;
	x != y;
	~~~

* 조건문
~~~
def conditional_example(x, y)
	if x < y then
		x
	else if x == y then
		0
	else
		y;
~~~
* 반복문
~~~
extern print(i);

def loop_example(n)
	# initiazation, loop_condition, step
	for _i = 0, i < n, 1 in
		print(_i);
~~~
