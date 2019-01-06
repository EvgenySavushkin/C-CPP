#include <stdio.h>
#include <stdlib.h>


int  Cplusplus()  {
int count=0, c=getchar();
	while ( 1 ) {
	/* Start: */
		if (c==EOF) break;
		else if (c!='C') { c=getchar(); continue; }
		else c=getchar();
	/* C: */
		if (c!='+') continue;
		else c=getchar();
	/* Cplus: */
		if (c!='+') continue;
		else { c=getchar(); count++;}
	/* Cplusplus: */
	continue; /* этот оператор можно опустить */
	}
	/* Stop: */
	return count;
};

int main ()
{
     int z = 0;
     z = Cplusplus();
     printf("vsego %d \n",z);
     return 0;
};
