#include <iostream>
using namespace std;

class body
{
	public:
	virtual double area()=0;
};

class box:public body
{
	protected:
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
	double area(){return(l*w+2*h*l+2*h*w);}
       	virtual  void zna(){cout<<l<<" "<<w<<" "<<h<<"\n";}
	box & operator= (const box & a){if(this!=&a){l=a.l;w=a.w;h=a.h;return *this;}}
	box & operator++(){l=l+1;h=h+1;w=w+1;return *this;}
	box & operator--(){l=l-1;h=h-1;w=w-1;return *this;}
	box  operator++(int){box t = *this;++*this;return t;}
	box  operator--(int){box t = *this;--*this;return t;}
	friend box operator+(const box & a,const box & b){box t(a.l+b.l,a.w+b.w,a.h+b.h);return t;}
};

class hbox: public box
{
	box lid;	
	public:
	hbox() : box(), lid(2,1,1) /*,ww(0.5),wh(0.5)*/{}
	hbox(double d) : box(d),lid(d,d,1){}
	hbox(double d,double c) : box(d,c),lid(c,d,d){}
	hbox(double a,double b,double c) : box(a,b,c),lid(a,b,1){}
	hbox(double a,double b, double c, double d) : box(a,b,c),lid(a,c,d){}
	hbox(const hbox & a){l=a.l;h=a.h;w=a.w;lid=a.lid;cout<<"hKK\n";}
	~hbox(){cout<<"Destructor hbox called\n";}
	void zna(){cout<<l<<" "<<w<<" "<<h<<" "<<lid.get_l()<<" "<<lid.get_w()<<" "<<lid.get_h() <<"\n";}
	double area(){cout<<"area = "<<l*w+2*h*l+2*h*w+lid.area()<<"\n";return(l*w+2*h*l+2*h*w+lid.area());}
};


int main(void)
{
	double h,l,w,lw;
	cout<<"Enter box heigth\n";
	cin>>h;
	cout<<"Enter a width\n";
	cin>>w;
	cout<<"Enter box length\n";
	cin>>l;	
	cout<<"Enter box lheigth\n";
	cin>>lw;
	hbox a,b(l),c(h,l),d(l,w,h),e(l,w,h,lw),g(d);
	a.zna();h=a.area();
	b.zna();h=b.area();	
	c.zna();h=c.area();
	d.zna();h=d.area();
	e.zna();h=e.area();
	g.zna();h=g.area();
	return(0);
}
