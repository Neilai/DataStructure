#include<queue>
#include <cstddef>
#include<cassert>
using namespace std;

template<typename T>
struct HuffmanNode{
	 
	 T   weight=-1;
	int  index=-1;
	int  lchild=-1;
	int  rchild=-1;
	int  parent=-1;
	bool operator<(HuffmanNode other) const{
		return this->weight>other.weight;	 
	 }
};

template<typename T>
class HuffmanTree{
private:

public:
	HuffmanNode<T> *tree;
	int num=0;
	
	void buildtree(T arr[],int n){
		num=2*n-1;
		
		tree=new HuffmanNode<T>[num+1];
		priority_queue<HuffmanNode<T>> q;
		
		for(int i=1;i<=n;i++){
			tree[i].index=i;
			tree[i].weight=arr[i-1];
			q.push(tree[i]);
		}

		for(int i=n+1;i<=num;i++){
			
			HuffmanNode<T> minnode1=q.top();
			q.pop();
			HuffmanNode<T> minnode2=q.top();
			q.pop();
			
			tree[i].weight=minnode2.weight+minnode1.weight;
			tree[i].index=i;
			tree[i].lchild=minnode1.index;
			tree[i].rchild=minnode2.index;
		
			minnode1.parent=tree[i].index;
			minnode2.parent=tree[i].index;
		}
	}
	void  showcode(){
		assert(num>0);
		
	}
};

