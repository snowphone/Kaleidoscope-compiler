# Kaleidoscope-compiler
A compiler for the Kaleidoscope language. Written in C++ with lex/yacc and generate LLVM IR.

## Status
* Identifier: lower case alphanumeric string only.
* Literal:  numeric
* Operator: addition, subtraction, multiplication

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

### 논리 연산자
Kaleidoscope는 논리곱(`&&`), 논리합(`||`), 그리고 부정(`!`) 기호를 제공한다.
논리곱과 논리합 연산은 short-circuit에 의거하여 평가된다.

### 타입
Kaleidoscope는 원래 double이라는 하나의 타입만을 가지고 있는 언어였지만, 현 버전은 double과 배열 타입을 지원한다.
타입 선언은 `<identifier> : <type>`으로 표현된다.
다중 타입 지원에 따라 Kaleidoscope는 정적 타이핑 언어가 되었다.

### 배열
Kaleidoscope에서는 배열 타입을 새로 지원하며, row-major과 0-indexed라는 특징을 가진다.
배열 타입은 `[<원소 타입> * <원소 개수>]`의 형식이다.
예를 들어 (3 X 4) 형태의 double 배열을 선언하기 위해서는 `[[double * 3] * 4]`와 같이 타입을 지정하여야 한다.
배열 타입의 변수를 초기화 하는 것은 다음의 예를 참조한다.
~~~
matrix: [[double * 2] * 3] = [[1, 2], [3, 4], 5, 6]];
~~~

### 대입문
Vanilla kaleidoscope가 함수 parameter만을 이용하여 변수를 선언할 수 있었던 것과 달리 본 컴파일러는 함수 body 내부에서의 변수 선언을 허용한다. 
지원하는 타입의 수가 늘어남에 따라 정적 타이핑 언어로 언어의 특성이 변경되었다.
타입 정보를 명시하기 위하여 `<identifier>: <type> = <value>`의 형식을 따르며, 함수형 언어처럼 한 번만 대입이 가능하다. 
대입문 또한 expression의 일부로 취급되어 대입문의 평가 결과는 대입된 값이다. 따라서 `x: double = y: double = 3.14`와 같은 다중 대입 또한 가능하다.

### 함수
함수는 다음과 같은 형식을 지닌다.
~~~
def function_identifier(arg1: <type>, arg2: <type>) : <return type>
	body;
~~~
`def` 키워드를 사용하여 함수의 시작을 알리고, identifier와 argument list가 그 뒤를 잇는다.
Argument list를 구성하는 각 argument는 `<identifier>: <type>` 의 형식을 갖추어야 한다.
Argument list 다음에는 `:`과 반환 타입이 명시된다.
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

### 조건문
~~~
def conditional_example(x:double, y:double):double
	if x < y then
		x
	else if x == y then
		0
	else
		y;
~~~
조건문은 expression으로 표현되기 때문에 삼항연산자의 역할을 수행할 수 있다.
~~~
def min_plus_three(lhs:double, rhs:double)
	min_val:double = if lhs < rhs then lhs else rhs,
	min_val + 3;
~~~

### 반복문
'for <초기식>, <반복 조건>, 변화값 in' 의 문법으로 구성되었다.
~~~
extern print(i:double);
def loop_example(n:double)
	# initiazation, loop_condition, step
	for _i = 0, i < n, 1 in
		print(_i);
~~~
