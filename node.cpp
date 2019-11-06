#include <typeinfo>
#include "node.h"

A_TopList *aroot = NULL;

void A_Top::indent(int d)
{
	int i;
	for(i=0 ; i<d ; i++){
		cout<<" ";
	}
}

void A_Prototype::Print(int d)
{
	int i, Size = paramList.size();
	indent(d);
	cout<<"prototype"<<endl;
	ident.Print(d+2);

	if(Size > 0){
		indent(d+2);
		cout<<"identifierList"<<endl;
		for(i=0 ; i<Size ; i++){
			A_Top& a = /*채워넣기*/;
			a.Print(d+4);
		}
	}
}

void A_Definition::Print(int d)
{
	indent(d);
	cout<<"definition"<<endl;
	/*
	 * 채워넣기
	 */
}

void A_Identifier::Print(int d)
{
	indent(d);
	cout<<"identifier: "<<name<<endl;
}

void A_NumberExpr::Print(int d)
{
	indent(d);
	cout<<"numberExpr: "<<val<<endl;
}

void A_VariableExpr::Print(int d)
{
	indent(d);
	cout<<"variableExpr"<<endl;
	ident.Print(d+2);
}

void A_BinaryExpr::Print(int d)
{
	indent(d);
	cout<<"binaryExpr: "<<oper<<endl;
	left.Print(d+2);	
	right.Print(d+2);

}

void A_CallExpr::Print(int d)
{
	int Size = arguments.size();
	int i;

	indent(d);
	cout<<"callExpr"<<endl;
	/*채워넣기*/
	
	indent(d+2);
	cout<<"expressionList"<<endl;
	for(i=0 ; i<Size ; i++){
		A_Expr& e = *((A_Expr*)arguments.at(i));
		e.Print(d+4);
	}
}

void A_External::Print(int d)
{
	indent(d);
	cout<<"external"<<endl;
}
