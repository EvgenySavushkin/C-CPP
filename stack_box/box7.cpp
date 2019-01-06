#include <iostream>
using namespace std;

class body
{
	public:
	virtual double area()const=0;
};

class box: public virtual body
{
	protected:
	double  l,w,h;
	public:
	box(){w=h=1;l=2;}
	box(double d){if(d<=0) throw " length must be positive";l=h=w=d;}
	box(double d,double c){if(d<=0||c<=0) throw " length must be positive";w=h=d;l=c;}
	box(double a,double b, double c){if(a<=0||b<=0||c<=0) throw " length must be positive";l=a;w=b;h=c;}
	box(const box & a){l=a.l;w=a.w;h=a.h;cout<<"KK\n";}
	~box(){cout<<"Destructor called\n";}
	double get_l()const{return l;};double get_w()const{return w;};double get_h()const{return h;};
	void set_l(double a){l=a;};void set_h(double a){h=a;};void set_w(double a){w=a;};
	double area()const{return(l*w+2*h*l+2*h*w);}
       	virtual  void zna()const{cout<<l<<" "<<w<<" "<<h<<"\n";}
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
	wbox(double d) try : box(d),ww(0.5),wh(0.5){if(d<=0.5) throw " window is too big";}catch(const char *er){cout<<"wbox"<<er<<"\n";}
	wbox(double d,double c) try : box(d,c),ww(0.5),wh(0.5){if(d<=0.5||c<=0.5) throw " window is too big";}catch(const char *er){cout<<"wbox"<<er<<"\n";}
	wbox(double a,double b,double c) try : box(a,b,c),ww(0.5),wh(0.5){if(a<=0.5||c<=0.5) throw " window is too big";}catch(const char *er){cout<<"wbox"<<er<<"\n";}
	wbox(double a,double b, double c, double d) try : box(a,b,c),ww(d),wh(d){if(a<=d||c<=d) throw " window is too big";}catch(const char *er){cout<<"wbox"<<er<<"\n";}
	wbox(double a,double b, double c, double d,double e)try:box(a,b,c),ww(d),wh(e){if(a<=d||c<=e) throw " window is too big";}catch(const char *er){cout<<"wbox"<<er<<"\n";}
	wbox(const wbox & a){l=a.l;h=a.h;w=a.w;ww=a.ww;wh=a.wh;cout<<"wKK\n";}
	~wbox(){cout<<"Destructor wbox called\n";}
	void zna()const{cout<<l<<" "<<w<<" "<<h<<" "<<ww<<" "<<wh<<"\n";}
	double area()const{cout<<"area = "<<l*w+2*h*l+2*h*w-ww*wh<<"\n";return(l*w+2*h*l+2*h*w-ww*wh);}
};

class hbox: public virtual  box
{
	protected:
	box lid;	
	public:
	hbox() try: box(), lid(2,1,1) /*,ww(0.5),wh(0.5)*/{}catch(const char *er){cout<<"hbox"<<er<<"\n";}
	hbox(double d) try: box(d),lid(d,d,1){}catch(const char *er){cout<<"hbox"<<er<<"\n";}
	hbox(double d,double c)try : box(d,c),lid(c,d,d){}catch(const char *er){cout<<"hbox"<<er<<"\n";}
	hbox(double a,double b,double c)try : box(a,b,c),lid(a,b,1){}catch(const char *er){cout<<"hbox"<<er<<"\n";}
	hbox(double a,double b, double c, double d) try: box(a,b,c),lid(a,c,d){}catch(const char *er){cout<<"hbox"<<er<<"\n";}
	hbox(const hbox & a){l=a.l;h=a.h;w=a.w;lid=a.lid;cout<<"hKK\n";}
	~hbox(){cout<<"Destructor hbox called\n";}
	void zna()const{cout<<l<<" "<<w<<" "<<h<<" "<<lid.get_l()<<" "<<lid.get_w()<<" "<<lid.get_h() <<"\n";}
	double area()const{cout<<"area = "<<l*w+2*h*l+2*h*w+lid.area()<<"\n";return(l*w+2*h*l+2*h*w+lid.area());}
};

class whbox: public hbox, public wbox
{
	public:
	whbox() try:hbox(),wbox() {}catch(const char *er){cout<<"whbox"<<er<<"\n";}
	whbox(double d) try: hbox(d),wbox(d),box(d){}catch(const char *er){cout<<"whbox"<<er<<"\n";}
	whbox(double d,double c) try: hbox(d,c),box(d,c),wbox(){}catch(const char *er){cout<<"whbox"<<er<<"\n";}
	whbox(double a,double b,double c) try: box(a,b,c),wbox(),hbox(a,b,c){}catch(const char *er){cout<<"whbox"<<er<<"\n";}
	whbox(double a,double b, double c, double d) try: box(a,b,c),wbox(a,b,c),hbox(a,b,c,d){}catch(const char *er){cout<<"whbox"<<er<<"\n";}
	whbox(double a,double b, double c, double d,double e)try:box(a,b,c),hbox(a,b,c,d),wbox(a,b,c,e){}catch(const char *er){cout<<"whbox"<<er<<"\n";}
	whbox(double a,double b, double c, double d,double e,double f)try:box(a,b,c),hbox(a,b,c,d),wbox(a,b,c,e,f){}catch(const char *er){cout<<"whbox"<<er<<"\n";}
	whbox(const whbox & a){l=a.l;h=a.h;w=a.w;ww=a.ww;wh=a.wh;lid=a.lid;cout<<"whKK\n";}
	~whbox(){cout<<"Destructor whbox called\n";}
	void zna() const {cout<<l<<" "<<w<<" "<<h<<" "<<ww<<" "<<wh<<"\n"<<"lid "<<lid.get_l()<<" "<<lid.get_w()<<" "<<lid.get_h() <<"\n";;}
	double area()const{cout<<"area = "<<l*w+2*h*l+2*h*w-ww*wh+lid.area()<<"\n";return(l*w+2*h*l+2*h*w-ww*wh+lid.area());}

};

int main(void)
{
/*	double h,l,w,lh,ww,wh;
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
	try {whbox a,b(l),c(h,l),d(l,w,h),e(l,w,h,lh),f(l,w,h,lh,ww),t(l,w,h,lh,ww,wh),g(d);
	a.zna();h=a.area();
	b.zna();h=b.area();	
	c.zna();h=c.area();
	d.zna();h=d.area();
	e.zna();h=e.area();
	f.zna();h=f.area();
	t.zna();h=t.area();
	g.zna();h=g.area();} catch(const char *er){cout<<"main"<<er<<"\n";}
*/
	try{ const whbox a;
		a.area(); a.zna();
	}
	catch (const char *er){cout <<"main"<<er<<"\n";}

	return(0);
}
