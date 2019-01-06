//#include <stdio.h>
//#include <stdlib.h>

typedef struct Node * link;
typedef  struct Node {int element;link next;} node;
typedef link list;

//void polc(void);
//void pech1(list);
int vernelem(list,int);
void udal(list);
void pech2(list);
//void pech3(list);
int len(list);
list ins(int,list,char);
list dob(list, int);

/*main () 
{
	list t;
	int r,i;
	t=(list)malloc(sizeof(node));
	t->next=NULL;
	for(i=0;i<5;i++)
	{
		printf("vved ");
		scanf("%d",&r);
		dob(t,r);
		printf("\n");
		pech2(t);	
	}
	udal(t);
	return(0);
}*/
int vernelem(list e,int i)
{
	link q;
	q=e;
	int w;
	for(w=0;w<i;w++)
	{
		q=q->next;
	}
	return(q->element);	
}



list dob(list r,int i)
{
	list e;
	link q;
	q=(link)malloc(sizeof(node));
	q->element=i;
	(*q).next=NULL;
	e=r;
	while(e->next!=NULL)
	{
		e=e->next;
	}
	e->next=q;
	return(r);
}
/*void polc()
{
	char c = 'w';
	list r;
	link q;
	link l;
	r=(link)malloc(sizeof(node));
	printf("%d %d",r->next,r);
	q=r;
	printf("%d %d",q->next,q);
	while(c!='q')
	{
	printf("c=");
	c=getchar();
	q->element = c;
	printf("elem=%c\n",(*q).element);
	l=(link)malloc(sizeof(node));
	printf("l=%d\n", l);
	q->next=l;
	if(c=='q')q->next=NULL;
	q=q->next;
	printf("q=%d\n",q);
	printf("l=%d\n", l);
	}
	free(l);
	free(q);
	pech1(r);
	pech2(r);
	int u = len(r);
	printf("\n%d",u);
	r=ins(2,r,'z');
	pech3(r);
	udal(r);
}

void pech1(list e)
{
	char c='e';
	while(c!='q')
	{
		c=e->element;
		e=e->next;
		printf("%c",c);
	}
}*/
void pech2(list e)
{	
	e=e->next;
	while((*e).next!=NULL)
	{
		printf("%d ",e->element);
		e=e->next;
	}
	printf("%d ",e->element);

}

int len(list e)
{
	int i = 0;
	 while((*e).next!=NULL)
	 {
		 i++;
		 e=e->next;
	 }
	 return(i);
}

/*list ins(int i,list e,char c)
{
	list r;
	link l;
	int t;
	r=e;
	pech2(e);
	l = (list)malloc(sizeof(node));
	(*l).element = c;
	   printf("\n%d%c",l,l->element);printf("|%d|%c",r,r->element);
	for(t=1;t<i;t++){r=r->next;printf("|%d+%c",r,r->element);} 
	l->next=r->next;
	r->next=l;
	pech2(e);
	return(e);
}

void pech3(list e)
{
	if (e->next==NULL) printf("%c",e->element);
	else {printf("%c%d",e->element,e->next);e=e->next;pech3(e);}
}*/
void udal(list e)
{
	link q;
	while(e!=NULL)
	{
		q=e;
		e=e->next;
		free(q);
	}
}
