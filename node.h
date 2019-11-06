#include <iostream>
#include <vector>
#include <stdio.h>
#include <string>
using namespace std;

class A_Top;
class A_Definition;
class A_Prototype;
class A_Identifier;
class A_Expr;
class A_NumberExpr;
class A_VariableExpr;
class A_BinaryExpr;
class A_CallExpr;
class A_External;

typedef std::vector<A_Top*>		A_TopList;

extern A_TopList *aroot;

class A_Top {
public:
	virtual ~A_Top() {}
	void indent(int d);				// 각 노드의 깊이를 지정해준다.
	virtual void Print(int d){}		// 노드를 출력한다.
};

// A_Prototype - This class represents the "prototype" for a function,
class A_Prototype : public A_Top {
private:
	/*
	채워넣기
	*/
public:
	A_Prototype(/*채워넣기*/) : ident(id), paramList(il) {}
	virtual void Print(int d);
};

// A_Definition - This class represents a function definition itself.
class A_Definition : public A_Top {
private:
	/*
	채워넣기
	*/
public:
	A_Definition(/*채워넣기*/) : header(h), body(b) {}
	virtual void Print(int d);
};

class A_Identifier : public A_Top {
private:
	std::string name;
public:
	A_Identifier(std::string& n) : name(n) {}
	virtual void Print(int d);
};
class A_Expr : public A_Top {
public:
	virtual ~A_Expr() {}
	virtual void Print(int d) {}
};

// A_NumberExpr - Expr class for numeric literals like "1.0".
class A_NumberExpr : public A_Expr {
private:
	double val;
public:
	A_NumberExpr(double v) : val(v) {}
	virtual void Print(int d);
};

// A_VariableExpr - Expr class for referencing a variable, like "a".
class A_VariableExpr : public A_Expr {
private:
	/*
	채워넣기
	*/
public:
	A_VariableExpr(/*채워넣기*/) : ident(id) {}
	virtual void Print(int d);
};

// A_BinaryExpr - Expr class for a binary operator.
class A_BinaryExpr : public A_Expr {
private:
	char		oper;
	A_Expr&	left;
	A_Expr& right;

public:
	A_BinaryExpr(char op, A_Expr& lhs, A_Expr& rhs) : oper(op), left(lhs), right(rhs) {}
	virtual void Print(int d);
};

// A_CallExpr - Expr class for function calls.
class A_CallExpr : public A_Expr {
private:
	/*
	채워넣기
	*/
	A_TopList&		arguments;
public:
	A_CallExpr(/*채워넣기*/) : funcName(f), arguments(args) {}
	virtual void Print(int d);
};

class A_External : public A_Top {
private:
	A_Prototype&	prototype;
public:
	A_External(A_Prototype& proto) : prototype(proto) {}
	virtual void Print(int d);
};
