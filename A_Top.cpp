#include <typeinfo>
#include "A_Top.h"

A_TopList *aroot = NULL;

void A_Top::indent(int d)
{
	int i;
	for(i=0 ; i<d ; i++){
		cout<<" ";
	}
}
