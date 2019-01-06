#include <stdio.h>
#include <stdlib.h>
#include "spisok.c"
#include "derevo.c"
#define N 200
#define M 15

void selsor(int *,int);
void puzsor(int *,int);
void vstsor2(int *,int,int);
void vstsor(int *, int);
void schsor(int *,int);
void dersor(int*,int);
void bissor(int*, int);
void dvpoisk(int*,int ,int);
void transp(int (*)[M],int);

struct tabl{char* name; void(*fun)(int *,int);}; 
struct tabl func[] = { {"Sortirovka viborom",&selsor},
			{"Puzirkovaia sortirovka",&puzsor},
			{"sortirovks vstavkami",&vstsor},
			{"sortirovka shela",&schsor},
			{"piramidalnaya sortirovka(derevom)",&dersor},
			{"bistraia sortirovka",&bissor}
			};

main(void)
{
	int i,j,z;
	char flag = 'n';
	int a[N];

	for(j=0;j<3;j++)
	{
		if(flag=='n')
		{	
			z=0;
			printf("Enter number from 0 to %d",N);
			printf("\nsize of array =");
			z=scanf("%d",&i);
			if(z==0){printf("it's not a number\n");return(0);}
			if (i<0||i>=N)
			{	if(j<2)
				printf("you have %d attempt(s)",2-j);
				else return(0);
			}
			else
			{
				for (z=0;z<i;z++)
				{
					a[z]	= rand()%50;
				}
				flag='f';
			}
		}
	}
	for(z=0;z<i;z++){printf("%d ",a[z]);}
	printf("\n choose sorting method:\n");
	for(z=0;z<6;z++){printf("%d : %s\n",z+1,func[z].name);}
	printf("method #:");
	flag = getchar();
	flag = getchar();
	printf("%c\n",flag);
	switch(flag)
	{
	case('1'):
		printf("you choose %s",func[0].name );
		func[0].fun(a,i);
		break;
	case('2'):
		printf("you choose %s",func[1].name );
		func[1].fun(a,i);
		break;	
	case('3'):
		printf("you choose %s",func[2].name );
		func[2].fun(a,i);
		break;
	case('4'):
		printf("you choose %s",func[3].name );
		func[3].fun(a,i);
		break;
	case('5'):
		printf("you choose %s",func[4].name );
		func[4].fun(a,i);
		break;	
	case('6'):
		printf("you choose %s",func[5].name );
		func[5].fun(a,i);
		break;	
	default:
		printf("default choosing %s",func[0].name );
		func[0].fun(a,i);
		break;
	}
//	bissor(a,i);
	printf("\n");
	for(z=0;z<i;z++){printf("%d ",a[z]);}
	printf("\n");
//*************************************************
	z=1;
	while(z==1)
	{
	printf("\nenter a number h=");
	z=scanf("%d",&j);
	dvpoisk(a,i,j);
	}
	printf("\nnot a number\n");

	
//**************************************************
	int b[M][M];
	for(i=0;i<M;i++)
		for(j=0;j<M;j++)
		{
			b[i][j]	= rand()%50;
		}
	for(i=0;i<M;i++){
		printf("\n");
		for(j=0;j<M;j++)
		{
			printf("%4d ",b[i][j]);
		}}
	transp(b,M);
	printf("\n");
	for(i=0;i<M;i++){
		printf("\n");
		for(j=0;j<M;j++)
		{
			printf("%4d ",b[i][j]);
		}}
}
void transp(int a[][M],int g)
{	
	int i,j,t;
	for(i=1;i<g;i++)
		for(j=0;j<i;j++)
		{
			t=a[i][j];
			a[i][j]=a[j][i];
			a[j][i]=t;
		}

}


void dvpoisk(int*a,int i,int h)
{
	int f=0;

	while(1)
	{
	if(*(a+f+(i-f)/2)>h){i=f+(i-f)/2-1;}
	if(*(a+f+(i-f)/2)<h){f=f+(i-f)/2+1;}
	if(*(a+f+(i-f)/2)==h){printf("\n %d is %d item",h,f+1+(i-f)/2);break;}
	if(i<=f){printf("\n %d not found",h);break;}
	}
}

void bissor(int *a, int i)
{
	int j =0;
	int  z,t,k, p;
	k=i-1;
	int *b,*c;
	p = *(a+k);
	while(j<=k)	
	{
		while(*(a+j) < p) j++;
		while(*(a+k) > p) k--;
		if(j<=k)
		{
		t=*(a+j); *(a+j)=*(a+k);*(a+k)=t; 
//		for(z=0;z<i;z++){printf("%d ", *(a+z));}printf("\np=%d j=%d k=%d\n",p,j,k);
		j++;k--;
		}
	}
	b=a;
	c=a+j;
	if(k>0) {/*printf("lev\n")*/;bissor(b,k+1);}
	if(i>j) {/*printf("prav \n")*/;bissor(c, i-j);}
}

void selsor(int *a,int i)
{
	int z,j,k,t;
	for (j=0;j<i;j++)
	{
		k=j;
		for(z=j+1;z<i;z++)
		{	
			if( a[z]<a[k]) k=z;
		}
		t=a[j];
		a[j]=a[k];
		a[k]=t;
	}

}

void dersor(int *a,int i)
{
	der u;
	int j=0;
	u=(der)malloc(sizeof(tist));
	u=preobr(u,a,i);
	vmas(u,a,&j);
	udalder(u);
}

void puzsor(int *a,int i)
{
	int k,j,t;
	for(j=0;j<i-1;j++)
	{
		for(k=0;k<i-j-1;k++)
		{
			if(a[k]>a[k+1]) 
			{
				t=a[k];
				a[k]=a[k+1];
				a[k+1]=t;
			}
		}
	}
}

void vstsor(int *a,int i)
{
	int j,k,t,m;
	for(j=1;j<i;j++)
	{
		for(k=0;k<j;k++)
		{
			if(a[j]<a[k])
			{
				t=a[j];
				for(m=0;m<j-k;m++)
				{
					a[j-m]=a[j-m-1];
				}
				a[k]=t;
				break;
			}
		}
	}
}

void vstsor2(int *a,int i,int d )
{
	int j,k,t,m;
	for(j=d;j<i*d;j=j+d)
	{
		for(k=0;k<j;k=k+d)
		{
			if(a[j]<a[k])
			{
				t=a[j];
				for(m=0;m<j-k;m=m+d)
				{
					a[j-m]=a[j-m-d];
				}
				a[k]=t;
				break;
			}
		}
	}
}
void schsor(int *a,int i)
{
	list q,r;
	int w=0;
	q=(list)malloc(sizeof(node));
	q->next=NULL;
	int p1,p2,p3,s;
	p1=p2=p3=s=1;
	while(w*3<i)
	{
		if(++s%2)
		{	
			w=8*p1-6*p2+1;
			q=dob(q,w);
		}
		else
		{
			w=9*p1-9*p3+1;
			q=dob(q,w);
			p2*=2;
			p3*=2;
		}
		p1*=2;
	}
//r=q;pech2(r);r=q;printf("\n%d",len(r));
	r=q;
	s=len(r);
	for(w=s;w>0;w--)
	{
		p2=vernelem(q,w);
//		printf("D%dD\n",p2);
		if(i/p2!=1){for(p1=0;p1<p2;p1++)
		{
//			printf("V%dV\n",p1);
			vstsor2(a+p1,i/p2,p2);
//			for(p3=0;p3<i;p3++){printf("%d ",a[p3]);if(!((p3-p1)%p2)){printf("|");}}
		}}
	}
	
}

