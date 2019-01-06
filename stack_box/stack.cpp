#include <iostream>
#include "aaaa.cpp"

using namespace std;

template <class T> class stack
{
	T* body;
	int size;
	int top;
public:
	explicit stack( int sz = 10 )
	{
		size = sz;
		if (size < 0) throw "size must be positive";
		cout<<"constructor"<<endl;
		top = 0;
		body = new T[size];
	}
	stack & operator =(const stack & a){if(this!=&a){
		this->size = a.size;
		cout<<"assignment stack"<<endl;
		this->top = a.top;
		this->body = new T[size];
		for ( int i = 0; i<size; ++i) this->body[i] = a.body[i];
	
	}}
	stack(stack  & s)
	{
		size = s.size;
		cout<<"copy stack"<<endl;
		top = s.top;
		body = new T[size];
		for ( int i = 0; i<size; ++i) body[i] = s.body[i];
	}
	~stack(){delete [] body;cout<<"destructor"<<endl;}
	T pop()
	{
		if (top == 0) throw "can't apply pop";
		cout<<"pop in stack"/*<<body[top-1]*/<<endl;
		top=top-1;
		return body[top];
	}
	void push(T x)
	{
		if (top==size) throw "stack is full";
		cout<<"push in stack"<<endl;
		body[top] = x;
		top=top+1;
	}
	T top1()
	{
		cout<<"top "<<body[top-1]<<endl;
		return body[top-1];
	}

};

int main ()
{
	try{
/*	stack<int> s1(10);
	stack<double> s2(3);
	for(int i = 0; i<5;i++){s1.push(i);}
	for(int i = 0; i<5;i++){s1.pop();}
	s2.push(2.3);s2.push(3.5);s2.top1();
*/
	whbox a,b;
	stack<whbox> s4(10);s4.push(a);s4.push(b);s4.pop();
/*	stack<double> s3(s2);s3.pop();s3.pop();
	s3=s2;s3.pop();s3.pop();
*/
	}
	catch(const char *er){cout<<er<<endl;}	
/*	try{
	stack<int> s1(10);s1.pop();
	}catch(const char *er){cout<<er<<endl;}	
	try{
	stack<double> s2(1);s2.push(3.4);s2.push(4.5);
	}catch(const char *er){cout<<er<<endl;}	
	try{stack<int> s4(-5);}catch(const char *er){cout<<er<<endl;}	
*/
	}
