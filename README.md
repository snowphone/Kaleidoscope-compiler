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
* ~~Assignment~~
* ~~sequential expression~~

## 메뉴얼

### 산술 연산자
~~~
1. + .2;	# 덧셈
3.14 - 0;	# 뺄셈
3.14 * 10;	# 곱셈
-1 / 10;	# 나눗셈
7 % 5.2;	# 나머지
~~~

### 비교 연산자
~~~
x < y;
x <= y;
x > y;
x >= y;
x == y;
x != y;
~~~

### 함수
함수는 다음과 같은 형식을 지닌다.
~~~
def function_identifier(arg1, arg2)
	body;
~~~
`def` 키워드를 사용하여 함수의 시작을 알리고, identifier와 argument list가 그 뒤를 잇는다.
마지막으로 body에 등장한 expression이 함수의 반환값이 되며, 함수의 끝에는 `;`이 위치한다.

### Expression
Expression은 수, 변수, 이항 연산, 함수 호출, 조건문, 대입문 및 반복문을 의미한다.
expression은 `,`을 통하여 연속하여 작성할 수 있으며 이를 이용하며 일반적인 다른 언어의 statements를 모방할 수 있다.
~~~c
int x = 3;
int y = 4;
x + y;
~~~
위와 같은 C언어로 된 여러 줄의 statement와 expression 조합이 있을 경우 Kaleidoscope로는 다음과 같이 표현할 수 있다.
~~~
x = 3,
y = 4,
x + y;
~~~

### 대입문
Vanilla kaleidoscope가 함수 parameter만을 이용하여 변수를 선언할 수 있었던 것과 달리 본 컴파일러는 함수 body 내부에서의 변수 선언을 허용한다. `<identifier> = <value>`의 형식을 따르며, 함수형 언어처럼 한 번만 대입이 가능하다. 대입문 또한 expression의 일부로 취급되어 대입문의 평가 결과는 rvalue이다. 따라서 `x=y=z`와 같은 다중 대입 또한 가능하다.

### 조건문
~~~
def conditional_example(x, y)
	if x < y then
		x
	else if x == y then
		0
	else
		y;
~~~
조건문은 expression으로 표현되기 때문에 삼항연산자의 역할을 수행할 수 있다.
~~~
def min_plus_three(lhs, rhs)
	min_val = if lhs < rhs then lhs else rhs,
	min_val + 3;
~~~

### 반복문
'for <초기식>, <반복 조건>, 변화값 in' 의 문법으로 구성되었다.
~~~
extern print(i);
def loop_example(n)
	# initiazation, loop_condition, step
	for _i = 0, i < n, 1 in
		print(_i);
~~~