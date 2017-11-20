#include<cassert>
template<typename T>
class MyStack {
private:
	

	T  * data;
	int top;
	int maxsize;

public:


	MyStack(int n) {	
		top = -1;
		maxsize = n;
		data = new T[n];

	}
	
	void push(T item) {	
		top++;
		assert(top < maxsize);
		data[top] = item;	
	}
	T gettop() {
	//	assert(top >= 0);
		return data[top];
	}
	T pop(){
		assert(top>=0);
		return data[top--];
	}
	void show() {	
		for (int i = 0; i <= top; i++)
			std::cout << data[i] <<std:: ends;
	}
	bool isempty() {
		if(top==-1)
			return 1;
		else
			return 0;
	}
	
	~MyStack(){
		delete data;
	}
};