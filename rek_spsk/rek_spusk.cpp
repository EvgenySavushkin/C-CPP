#include <iostream>
using namespace std;

char c;

void S();
void S1();
void P();
void P1();
void E();
void M1();
void T();
void M2();
void F();

void gc(){cin>>c;}

void S()
{        
	
	if(c=='a'||c=='b')
	{
		cout<<"S->P:=E, ";
		P();if(c!=':') throw c;
		gc();if(c!='=') throw c;
		gc();
		E();
	}
	else if (c=='i')
	{
		cout<<"S->if E then S S', ";
		gc();if(c!='f')throw c;
		gc(); 
		E();
		if(c!='t') throw c;
		 gc();if(c!='h')throw c;
		 gc(); if(c!='e')throw c;
		 gc();if(c!='n')throw c;
		 gc();
		S();
		//gc();
		S1();
	}
	//else throw c;

}

void S1()
{
	if(c=='e')
	{
		cout<<"S'->else S, ";
		 gc();if(c!='l')throw c;
		 gc();if(c!='s')throw c;
		 gc();if(c!='e')throw c;
		 gc();
		S();
	}
	else cout<<"S'->epsilon, ";
}

void P()
{
	if (c=='a')
	{
		cout<<"P->aP', ";
		gc();
		P1();
	}
	else if (c=='b')
	{
		cout<<"P->bP', ";
		gc();
		P1();
	}
	else throw c;
}

void P1()
{
	if(c=='(')
	{
		cout<<"P'->(E), ";
		gc();
		E();gc();//if(c!=')')throw c;gc();
	}
	else cout <<"P'->epsilon, ";
}

void E()
{
	if(c=='a'||c=='b'||c=='(')
	{
		cout<<"E->TM1, ";
		T();
		M1();
	}
	else throw c;
}

void M1()
{
	if (c=='+')
	{
		cout<<"M1->+TM1, ";
		gc();
		T();
		M1();
	}
	else cout<<"M1->epsilon, ";
}

void T()
{
	if (c=='a'||c=='b'||c=='(')
	{
		cout<<"T->FM2, ";
		F();
		M2();
	}
}

void M2()
{
	if(c=='*')
	{
		cout<<"M2->*TM2, ";
		gc();
		T();
		M2();
	}
	else cout<<"M2->epsilon, ";
}

void F()
{
	if(c=='a'||c=='b')
	{
		cout<<"F->P, ";
		P();
	}
	else if(c=='(')
	{
		cout<<"F->(E), ";
		gc();
		E();
		gc();
	}
	
}

int main()
{
	try
	{
		gc();
		S();
		if (c !='L')
			throw c;
		cout<<"SUCCESS !!!"<<endl;
		return 0;
	}
	catch (char c)
	{
		cout<<"error on lexeme "<<c<<endl;
		return 1;
	}
}
