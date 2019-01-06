#include <iostream>
using namespace std;

class box
{
	double  l,w,h;
	public:
	box(){w=h=1;l=2;}
	box(double d){l=h=w=d;}
	box(double d,double c){w=h=d;l=c;}
	box(double a,double b, double c){l=a;w=b;h=c;}
	box(const box & a){l=a.l;w=a.w;h=a.h;cout<<"KK\n";}
	~box(){cout<<"Destructor called\n";}
	double area(){cout<<"area = "<<l*w+2*h*l+2*h*w<<"\n";return(l*w+2*h*l+2*h*w);}
};

int main(void)
{
	double h,l,w;
	cout<<"Enter box heigth\n";
	cin>>h;
	cout<<"Enter a width\n";
	cin>>w;
	cout<<"Enter box length\n";
	cin>>l;	
	box a,b(l),c(w,l),d(l,w,h),e(a);
	box f=b;
	h=a.area();h=b.area();h=c.area();h=d.area();h=e.area();h=f.area();
	return(0);
}
