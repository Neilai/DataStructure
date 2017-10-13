#include<cmath>
template<typename T>

class MaxHeap
{
public:
	int capacity;
	int count;
	int * data;
public:
	MaxHeap(int maxcount){
		data = new int[maxcount+1];
		capacity = maxcount;
	}
	MaxHeap(T arr[], int n) {
		data = new T[n + 1];
		capacity = n;
		for(int i = 0; i < n; i++)
			data[i + 1] = arr[i];
		count = n;
		for (int i = count / 2; i >= 1; i--)
			shiftdown(i);
	}
	void shiftup(int);
	void shiftdown(int);
	void push(T item);
	//void show();
	T getmax();
	T pop();
	int getcount();
};
template<typename T>
void MaxHeap<T>::shiftup(int son)
{
	T tmp = data[son];
	int parent = son / 2;
	while (tmp > data[parent]&&parent!=0)
	{
		data[son] = data[parent];
		son = parent;
		parent = parent / 2;
	}
	data[son] = tmp;
}
template<typename T>
void MaxHeap<T>::shiftdown(int parent)
{
	T tmp = data[parent];
	for (int son=parent*2; son <=count; )
	{
		if (son + 1 <= count)
			if (data[son + 1] > data[son])
				son = son + 1;
		if (tmp < data[son])
			data[parent] = data[son];
		else
			break;
		parent = son;
		son = son * 2;
	}
	data[parent] = tmp;
}
template<typename T>
T  MaxHeap<T>::pop()
{
	T result = data[1];
	data[1] = data[count];
	count--;
	shiftdown(1);
	return result;
}
template<typename T>
T MaxHeap<T>::getmax()
{
	return data[1];
}
template<typename T>
void MaxHeap<T>::push(T item)
{
	count++;
	data[count] = item;
	shiftup(count);
}
template<typename T>
int MaxHeap<T>::getcount()
{
	return count;
}
