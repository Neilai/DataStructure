#include<cassert>
#include<iostream>
template<typename T>
struct ListNode
{
	T item;
	ListNode<T> *next=nullptr;
	ListNode<T> *prev= nullptr;
};
template<typename T>
class List
{
public:

	List():plist(nullptr){ }
	
	List(T a[], int n) {
		for (int i = 0; i < n; i++)
			insert(i, a[i]);
	}

	void push(T item);	
	T front();
	
	void clear();
	void show();
	
	T get( int pos);
	int  getlength();
	void insert(int pos,T item);
	void remove(T item);
	void remove_pos(int pos);
	int find(T item);
	ListNode<T>* getnode(int pos);
	void swap(int  i, int j);
	void sort();
	void merge(List<T>  otherlist);
	List<T>  operator +(List<T> otherlist);
	ListNode<T>  *operator[](int pos);
private:
	ListNode<T> * plist;
};

template<typename T>
ListNode<T> *List<T>::operator[](int pos)
{
	return getnode(pos);
}

template<typename T>
T List<T>::get(int pos)
{
	T item = getnode(pos)->item;
	return item;
}

template<typename T>
void List<T>::merge(List<T>  otherlist)
{

	for (int j = 0; j < otherlist.getlength();j++)
	{
		this->push(otherlist.getnode(j)->item);
	}
	this->sort();
}
template<typename T>
List<T>  List<T>:: operator +(List<T>  otherlist)
{	
	for (int j = 0; j < otherlist.getlength();j++)
	{
		this->push(otherlist.getnode(j)->item);
	}
	this->sort();
	return *this;
}
template<typename T>
T List<T>::front()
{
	int len = getlength();
	assert(len >= 1);
	T tmp=getnode(0)->item;
	remove_pos(0);
	return tmp;
}
template<typename T>
void List<T>::push(T item)
{
	int len = getlength();
	insert(len,item);
}
template<typename T>
void List<T>::show()
{
	ListNode<T> * p = this->plist;
	while (p)
	{
		std::cout <<p->item<< std::ends;
		p = p->next;
	}
}
template<typename T>
void List<T>::clear()
{
	ListNode<T> * p=this->plist;
	while(p)
	{ 
		ListNode<T> * tmp = p->next;
		free(p);
		p = tmp;
	}
	plist = nullptr;
 }
template<typename T>
int List<T>::getlength()
{
	ListNode<T> * p = this->plist;
	if (!p)
		return 0;
	int len=0;
	while (p)
	{
      p = p->next;
	  len++;
	}
	return len;
}
template<typename T>
void List<T>::insert(int pos,T item)
{
	ListNode<T> * newnode = new ListNode<T>;
	ListNode<T> * p = this->plist;
	int len = getlength();
	newnode->item = item;
	if (pos == 0)
	{
		if (len)
		{
			newnode->next = plist;
			plist->prev = newnode;
			plist = newnode;
		}
		else
			plist = newnode;
		return;
	}
	assert(pos<=len);
	if (pos ==len)
	{
		getnode(len - 1)->next = newnode;
		newnode->prev = getnode(len - 1);
		return;
	}
	int cnt = 0;
	while (cnt != pos)
	{
		p = p->next;
		cnt++;
	}
	newnode->next = p;
	newnode->prev = p->prev;
	p->prev->next= newnode;
	p->prev = newnode;
}

template<typename T>
void List<T>::remove_pos(int pos)
{
	ListNode<T> * p = this->plist;
	int cnt = 0;
	int len = getlength();
	assert(pos < len);
	while (cnt != pos)
	{
		p = p->next;
		cnt++;
	}
	if(p->next)
		p->next->prev = p->prev;
	if (p->prev)
		p->prev->next = p->next;
	else
		plist = p->next;
	free(p);
}
template<typename T>
int List<T>::find(T item)
{
	ListNode<T> * p = this->plist;
    int	cnt = 0;
	while (p)
	{
		if (p->item == item)
			return cnt;
		p = p->next;
		cnt++;
	}
	return -1;
}
template<typename T>
void List<T>::remove(T item)
{
	int pos = find(item);
	assert(pos != -1);
	remove_pos(pos);
}
template<typename T>
ListNode<T>* List<T>::getnode(int pos)
{
	ListNode<T> * p = this->plist;
	int cnt = 0;
	int len = getlength();
	assert(pos < len);
	while (p)
	{
		if (cnt == pos)
			return p;
		cnt++;
		p = p->next;
	}
}
template<typename T>
void List<T>::swap(int i,int j)
{
	int len = getlength();
	if (i == j)
		return;
	assert(i < len);
	assert(j < len);
	ListNode<T> *tmp,*p1,*p2;
	p1 = getnode(i);
	p2 = getnode(j);
	if (j == i + 1)
	{
		if (p1->prev)
			p1->prev->next = p2;
		else
			plist = p2;
		if(p2->next)
			p2->next->prev = p1;
		
		p1->next = p2->next;
		p2->next = p1;
		p2->prev = p1->prev;
		p1->prev = p2;
		return;
	}
	if (i == j + 1)
	{
		if (p2->prev)
			p2->prev->next = p1;
		else
			plist = p1;
		if(p1->next)
			p1->next->prev = p2;
		
		p2->next = p1->next;
		p1->next = p2;
		p1->prev = p2->prev;
		p2->prev = p1;
		return;
	}

	if(p1->prev)
		p1->prev->next = p2;
	else
		plist = p2;
	if(p1->next)
		p1->next->prev = p2;
	if(p2->prev)
		p2->prev->next=p1;
	else
		plist = p1;
	if(p2->next)
		p2->next->prev = p1;
	
	tmp = p1->next;
	p1->next = p2->next;
	p2->next = tmp;
	
	tmp = p1->prev;
	p1->prev = p2->prev;
	p2->prev = tmp;
}
template<typename T>
void List<T>::sort()
{
	int len = getlength();
	if (len == 1)
		return;
	for (int i = 0; i < len; i++)
	{
		int minIndex = i;
		for (int j = i + 1; j < len; j++)
			if (getnode(j)->item < getnode(minIndex)->item)
				minIndex = j;
		swap(i, minIndex);
	}
}