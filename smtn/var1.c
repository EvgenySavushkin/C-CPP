#include <stdio.h>
#include <stdlib.h>


int  Cplusplus() {
	enum vertex {Start, Stop, C, Cplus} /* тип для моделирования вершин графа */
	v=Start;
	/* текущая вершина, сначала она равна начальной вершине Start */
	int count=0, c;
	for (c=getchar(); 1 ; c=getchar() ) {
	switch(v) {
		case Start:
			if (c=='C') v=C;
			else if (c==EOF) v=Stop;
			break; /* else v=Start; // при c==other */
		case C:
			if (c=='+') v=Cplus;
			else if (c==EOF) v=Stop;
			else if (c!='C') v=Start; /* при c==other */
			break; /* else v=C; // при c==C */
		case Cplus:
			if (c=='+') { v=Start; count++;}
			else if (c=='C') v=C;
			else if (c==EOF) v=Stop;
			else v=Start; /* при c==other */
			break;
		case Stop:
			return count;
}}
};

int main ()
{
     int z = 0;
     z = Cplusplus();
     printf("vsego %d \n",z);
     return 0;
};
