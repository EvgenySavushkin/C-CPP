#include <iostream>
using namespace std;

char c;
void gc(){cin>>c;};

bool scan_G()
{
	enum state {H,A,B,C,D,S,ER};
	state CS;
	CS=H;

	do
	{	gc();
		switch(CS)
		{
			case H: if(c=='0')
				{
					CS = A;
				}
				else CS = ER;
				break;
			case A: if(c=='1')
				{
					CS = B;
				}
				else if (c=='L')
				{
					CS = S;
				}
				else if(c =='0')
				{
					CS = A;
				}
				else CS = ER;
				break;
			case B: if(c=='0')
				{
					CS = C;
				}
				else if (c == 'L')
				{
					CS = S;
				}
				else CS = ER;
				break;
			case C: if(c=='0')
				{
					CS = D;
				}
				else if (c == 'L')
				{
					CS = S;
				}
				else CS = ER;
				break;
			case D: if(c=='0')
				{
					CS = C;
				}
				else if (c=='1')
				{
					CS = B;
				}
				else if (c=='L')
				{
					CS = S;
				}
				else CS = ER;
				break;

		}
		
	}
	while (CS!=S && CS!=ER);
	
	return CS ==S;
}

int main ()
{
	bool t;
	t = scan_G();
	cout<<boolalpha;
	cout<<t;
	return 0;
}
