#include<cmath>
template<typename T>
class IndexMaxHeap
{
public:
	int capacity;
	int count;
	int * data;
	int *index;
public:
	IndexMaxHeap(int maxcount){
		data = new int[maxcount + 1];
		index = new int[maxcount + 1];
		capacity = maxcount;
		count = 0;
	}
	IndexMaxHeap(T arr[], int n){
		data = new T[n + 1];
		index = new T[n + 1];
		capacity = n;
		for (int i = 0; i < n; i++)
			data[i + 1] = arr[i];
		for (int i = 0; i < n; i++)
			index[i + 1] = i+1;
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
void IndexMaxHeap<T>::shiftup(int son)
{
	int tmp = index[son];
	int parent = son / 2;
	
	while (parent !=0 && data[tmp] > data[index[parent]])
	{
		index[son] = index[parent];
		son = parent;
		parent = parent / 2;
	}
	index[son] = tmp;
}
template<typename T>
void IndexMaxHeap<T>::shiftdown(int parent)
{
	int tmp = index[parent];
	for(int son = parent * 2; son <= count; )
	{
		if (son + 1 <= count)
			if (data[index[son + 1]] > data[index[son]])
				 son = son + 1;
		if (data[tmp] < data[index[son]])
			index[parent] = index[son];
		else
			break;
		parent = son;
		son = son * 2;
	}
	index[parent] = tmp;
}
template<typename T>
T  IndexMaxHeap<T>::pop()
{	
	T result = data[index[1]];
	index[1] = index[count];
	count--;
	shiftdown(1);
	return result;
}
template<typename T>
T IndexMaxHeap<T>::getmax()
{
	return data[index[1]];
}
template<typename T>
void IndexMaxHeap<T>::push(T item)
{
	count++;
	index[count] = count;
	data[index[count]] = item;
	shiftup(count);
}
template<typename T>
int IndexMaxHeap<T>::getcount()
{
	return count;
}