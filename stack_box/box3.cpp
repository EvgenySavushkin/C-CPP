#include <iostream>
using namespace std;

class body
{
	public:
	virtual double area()=0;
};

class box:public body
{
	double  l,w,h;
	public:
	box(){w=h=1;l=2;}
	box(double d){l=h=w=d;}
	box(double d,double c){w=h=d;l=c;}
	box(double a,double b, double c){l=a;w=b;h=c;}
	box(const box & a){l=a.l;w=a.w;h=a.h;cout<<"KK\n";}
	~box(){cout<<"Destructor called\n";}
	double get_l(){return l;};double get_w(){return w;};double get_h(){return h;};
	void set_l(double a){l=a;};void set_h(double a){h=a;};void set_w(double a){w=a;};
	double area(){cout<<"area = "<<l*w+2*h*l+2*h*w<<"\n";return(l*w+2*h*l+2*h*w);}
        void zna(){cout<<l<<" "<<w<<" "<<h<<"\n";}
	box & operator= (const box & a){if(this!=&a){l=a.l;w=a.w;h=a.h;return *this;}}
	box & operator++(){l=l+1;h=h+1;w=w+1;return *this;}
	box & operator--(){l=l-1;h=h-1;w=w-1;return *this;}
	box  operator++(int){box t = *this;++*this;return t;}
	box  operator--(int){box t = *this;--*this;return t;}
	friend box operator+(const box & a,const box & b){box t(a.l+b.l,a.w+b.w,a.h+b.h);return t;}
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
	box y,c,d(l,w,h);
	d.zna();
	cout<<"------------post-\n";
	c=d++;d.zna();c.zna();
	cout<<"------------pref\n";
	c=++d;d.zna();c.zna();
	cout<<"------------post\n";
	c=d--;d.zna();c.zna();
	cout<<"------------pref\n";
	c=--d;d.zna();c.zna();
	cout<<"------------sloj\n";
	y=c+d;y.zna();
	return(0);
}
