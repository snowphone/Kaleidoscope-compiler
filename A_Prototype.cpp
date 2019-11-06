#include <typeinfo>
#include "A_Prototype.h"

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

