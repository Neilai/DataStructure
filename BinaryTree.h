#include<cassert>
#include<iostream>
#include<Queue>
#include<stack>
using namespace std;
template <typename T>
struct treenode {
	T data=0;
	treenode<T> *lchild;
	treenode<T> *rchild;
};
template <typename T>
struct tmpnode
{
	treenode<T>*btnode;
	int isfirst;
};
template <typename T>
class BinaryTree {	
public:
	BinaryTree() {
		this->root = new treenode<T>;
	}
	treenode<T> *root;
	//根据前序中序建树
	treenode<T>* createby_pre_in(T * pre,T *in,int len);
	//根据中序后序建树
	treenode<T>* createby_post_in(T* post,T *in ,int len);
	
	//标号1为递归算法  标号2为非递归算法
	void inorder1(treenode<T> *root) {
		if (root != nullptr) {
			inorder1(root->lchild);
			cout << root->data << " ";
			inorder1(root->rchild);
		}
	};
	void inorder2(treenode<T> * root){

		stack<treenode<T> *> s;
		treenode<T>  *p=root;
		while(p!=NULL||!s.empty()){
			while(p!=NULL){
				s.push(p);
				p=p->lchild;
			}
		if(!s.empty())
			{
				p=s.top();
				cout<<p->data<<" ";
				s.pop();
				p=p->rchild;
			}
		}
		
	}
	//
	void postorder1(treenode<T> *root) {
		if (root != nullptr) {
			postorder1(root->lchild);
			postorder1(root->rchild);
			cout << root->data << " ";
		}
	};

	void postorder2(treenode<T> *root){
		stack<tmpnode<T> *> s;
		treenode<T> *p=root;
		tmpnode<T> *tmp;
		while(p!=NULL||!s.empty()){
			while(p!=NULL){
				tmpnode<T> *n=new tmpnode<T>;
				n->btnode=p;
				n->isfirst=true;
				s.push(n);
				p=p->lchild;
			}
			if(!s.empty()){
				tmp=s.top();
				if(!tmp->btnode->rchild||!tmp->isfirst){
					s.pop();
					cout<<tmp->btnode->data<<" ";
				}
				else{						
					p=tmp->btnode->rchild;	
					tmp->isfirst=false;
				}
			}
		}
	}
	void preorder2(treenode<T> * root){
		stack<treenode<T> *> s;
		treenode<T>  *p=root;
		while(p!=NULL||!s.empty()){
			while(p!=NULL){
				cout<<p->data<<" ";
				s.push(p);
				p=p->lchild;
			}
			if(!s.empty())
			{
				p=s.top();
				s.pop();
				p=p->rchild;
			}
		}

	}
	void preorder1(treenode<T> *root) {
		if (root != nullptr)
		{
			cout << root->data << " ";
			preorder1(root->lchild);
			preorder1(root->rchild);
		}
	};
	//层序遍历
	void levelorder(treenode<T> *root){
		queue<treenode<T> *> Q;
		if (!root)
			return;
		treenode<T> *tmp;
		Q.push(root);
		while (!Q.empty()) {
			tmp = Q.front();
			Q.pop();
			cout << tmp->data << ends;
			if (tmp->lchild)
				Q.push(tmp->lchild);
			if (tmp->rchild)
				Q.push(tmp->rchild);
		}

	}
	//插入
	treenode<T>*  insert(treenode<T> *bst,T item){
		if(!bst){
			bst=new treenode<T>;
			bst->data=item;
			bst->lchild=bst->rchild=NULL;
		}
		else{
			if(item<bst->data)
				bst->lchild=insert(bst->lchild,item);
			else if(item>bst->data)
				bst->rchild=insert(bst->rchild,item);
		}
		return bst;
	};
	//寻找最小最大结点
	treenode<T>* findminnode(treenode<T> * p){
		assert(p);
		while(1){
			if(!p->lchild)
				break;
			p=p->lchild;
		}
		return p;
	}
	treenode<T>* findmaxnode(treenode<T> * p){
		assert(p);
		while(1){
			if(!p->rchild)
				break;
			p=p->rchild;
		}
		return p;
	}
	//寻找结点
	treenode<T>* findnode(treenode<T> * p,T item){
		assert(p);
		if(item>p->data)
			findnode(p->rchild,item);
		else if(item<p->data)
			findnode(p->lchild,item);
		else 
			 return p;
	}
	//删除
	treenode<T>* remove(treenode<T> *bst,T item){
		treenode<T> * tmp;
		if(!bst)
			cout<<"未找到元素";
		else{
			if(item<bst->data)
				bst->lchild=remove(bst->lchild,item);
			else if(item>bst->data)
				bst->right=remove(bst->rchild,item);
			else {
				if(bst->lchild&&bst->rchild){
					tmp=findminnode(bst->rchild);
					bst->data=tmp->data;
					bst->right=remove(bst->right,bst->data);
				}
				else{
					tmp=bst;
					if(!bst->lchild)
						bst=bst->rchild;
					else
						bst=bst->lchild;
				}
			}
		}
		return bst;
	};
};



template<typename T>
treenode<T>* BinaryTree<T>::createby_pre_in(T * pre, T *in, int len) {
	if (len < 0 || pre == nullptr|| in == nullptr)
		return nullptr;
	treenode<T> *root = new treenode<T>;
	root->data = pre[0];
	root->lchild = root->rchild = nullptr;
	int i = 0;
	while (i<len&& in[i] != pre[0]){
		i++;
	}
	if(i)
		root->lchild = createby_pre_in(	pre + 1,in,i);
	if(len-i-1)
		root->rchild = createby_pre_in( pre + 1+i,in + i+1,len-i-1);
	this->root = root;
	return root;
}

template<typename T>
treenode<T>* BinaryTree<T>::createby_post_in(T * post, T *in, int len) {
	if (len < 0 || post == nullptr || in == nullptr)
		return nullptr;
	treenode<T> *root = new treenode<T>;
	root->data = post[len - 1];
	root->lchild = root->rchild = nullptr;
	int i = 0;
	while (in[i]!=post[len-1]){
		i++;
	};
	if(i)
		root->lchild = createby_post_in(post,in , i );
	if(len-i-1)
		root->rchild = createby_post_in( post+i ,in+i+1,len-i-1);
	this->root = root;
	return root;
}