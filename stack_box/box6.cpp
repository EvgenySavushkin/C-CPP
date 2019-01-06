#include <iostream>
using namespace std;

class body
{
	public:
	virtual double area()=0;
};

class box: public virtual body
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

class wbox: public virtual  box
{
	protected:
	double wh,ww;	
	public:
	wbox() : box()/*,ww(0.5),wh(0.5)*/{ww=wh=0.5;}
	wbox(double d) : box(d),ww(0.5),wh(0.5){}
	wbox(double d,double c) : box(d,c),ww(0.5),wh(0.5){}
	wbox(double a,double b,double c) : box(a,b,c),ww(0.5),wh(0.5){}
	wbox(double a,double b, double c, double d) : box(a,b,c),ww(d),wh(d){}
	wbox(double a,double b, double c, double d,double e):box(a,b,c),ww(d),wh(e){}
	wbox(const wbox & a){l=a.l;h=a.h;w=a.w;ww=a.ww;wh=a.wh;cout<<"wKK\n";}
	~wbox(){cout<<"Destructor wbox called\n";}
	void zna(){cout<<l<<" "<<w<<" "<<h<<" "<<ww<<" "<<wh<<"\n";}
	double area(){cout<<"area = "<<l*w+2*h*l+2*h*w-ww*wh<<"\n";return(l*w+2*h*l+2*h*w-ww*wh);}
};

class hbox: public virtual  box
{
	protected:
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

class whbox: public hbox, public wbox
{
	public:
	whbox() :hbox(),wbox() {}
	whbox(double d) : hbox(d),wbox(d),box(d){}
	whbox(double d,double c) : hbox(d,c),box(d,c),wbox(){}
	whbox(double a,double b,double c) : box(a,b,c),wbox(),hbox(a,b,c){}
	whbox(double a,double b, double c, double d) : box(a,b,c),wbox(a,b,c),hbox(a,b,c,d){}
	whbox(double a,double b, double c, double d,double e):box(a,b,c),hbox(a,b,c,d),wbox(a,b,c,e){}
	whbox(double a,double b, double c, double d,double e,double f):box(a,b,c),hbox(a,b,c,d),wbox(a,b,c,e,f){}
	whbox(const whbox & a){l=a.l;h=a.h;w=a.w;ww=a.ww;wh=a.wh;lid=a.lid;cout<<"whKK\n";}
	~whbox(){cout<<"Destructor whbox called\n";}
	void zna(){cout<<l<<" "<<w<<" "<<h<<" "<<ww<<" "<<wh<<"\n"<<"lid "<<lid.get_l()<<" "<<lid.get_w()<<" "<<lid.get_h() <<"\n";;}
	double area(){cout<<"area = "<<l*w+2*h*l+2*h*w-ww*wh+lid.area()<<"\n";return(l*w+2*h*l+2*h*w-ww*wh+lid.area());}

};

int main(void)
{
	double h,l,w,lh,ww,wh;
	cout<<"Enter box heigth\n";
	cin>>h;
	cout<<"Enter a width\n";
	cin>>w;
	cout<<"Enter box length\n";
	cin>>l;	
	cout<<"Enter box lheigth\n";
	cin>>lh;
	cout<<"Enter box qqidth\n";
	cin>>ww;	
	cout<<"Enter box wheigth\n";
	cin>>wh;
	whbox a,b(l),c(h,l),d(l,w,h),e(l,w,h,lh),f(l,w,h,lh,ww),t(l,w,h,lh,ww,wh),g(d);
	a.zna();h=a.area();
	b.zna();h=b.area();	
	c.zna();h=c.area();
	d.zna();h=d.area();
	e.zna();h=e.area();
	f.zna();h=f.area();
	t.zna();h=t.area();
	g.zna();h=g.area();
	return(0);
}
