#include <typeinfo>
#include "A_CallExpr.h"

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
