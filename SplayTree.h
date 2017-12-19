#include<cassert>
#include<iostream>
#include <cstddef>

using namespace std;
template<typename T>
struct SplayNode{
	SplayNode<T> * parent;
	SplayNode<T> *lchild;
	SplayNode<T> *rchild;
	T val;
	SplayNode(T val=0){
		parent=NULL;
		lchild=rchild=NULL;
		this->val=val;
	}
	SplayNode(){
		parent=NULL;
		lchild=rchild=NULL;
		this->val=0;
	}
};

template<typename T>
class SplayTree{
private:		
	void Splay(SplayNode<T> *node);
	void up(SplayNode<T> *);
	SplayNode<T>* L_Rotate(SplayNode<T> *node);
	SplayNode<T>* R_Rotate(SplayNode<T> *node);
	SplayNode<T>* LL_Rotate(SplayNode<T> *node);
	SplayNode<T>* RR_Rotate(SplayNode<T> *node);
	SplayNode<T>* LR_Rotate(SplayNode<T> *node);
	SplayNode<T>* RL_Rotate(SplayNode<T> *node);
	SplayNode<T>** __search_val(SplayNode<T>*&,T,SplayNode<T>*&);
	SplayNode<T>** search_val(T,SplayNode<T>*&);
	SplayNode<T> *__remove(SplayNode<T> *,T);
	SplayNode<T> *findminnode(SplayNode<T> *);
public:
	SplayNode<T> *root=NULL;
	bool search(T);
	bool insert(T);
	bool remove(T);
	void preOrderTraverse(SplayNode<T> * &node);
};

template<typename T>
void SplayTree<T>::preOrderTraverse(SplayNode<T> * &node){
	if(node){
		cout<<node->val<<" ";
		preOrderTraverse(node->lchild);
		preOrderTraverse(node->rchild);
	}
}

template<typename T>
SplayNode<T>* SplayTree<T>::findminnode(SplayNode<T> * p){
		assert(p);
		while(1){
			if(!p->lchild)
				break;
			p=p->lchild;
		}
		return p;
} 


template<typename T>
bool SplayTree<T>::remove(T item){
	__remove(root,item);
}


template<typename T>
SplayNode<T> * SplayTree<T>::__remove(SplayNode<T> *node,T item){
	SplayNode<T>*tmp; 
	if(!node)
		cout<<"未找到元素";
	else{
		if(item<node->val)
			node->lchild=__remove(node->lchild,item);
		else if(item>node->val)
			node->rchild=__remove(node->rchild,item);
		else {
			if(node->lchild&&node->rchild){
				tmp=findminnode(node->rchild);
				node->val=tmp->val;
				node->rchild=__remove(node->rchild,node->val);
			}
			else{				
				SplayNode<T>*parent=node->parent; 
				tmp=node;
				if(!node->lchild){
					node=node->rchild;
					node->parent=parent;
				}
				else{
					node=node->lchild;
					node->parent=parent;
				}
				delete tmp;
			}
		}
	}
	return node;
}  


//这里体现了为什么查找要用parent
template<typename T>
bool SplayTree<T>::insert(T val)  
{  
    SplayNode<T> ** temp=NULL;  
    SplayNode<T> * parent=NULL;  
    //先查找，如果成功则无需插入，否则返回该结点的引用。    
    temp=search_val(val,parent);    
    if (*temp==NULL) //需要插入数据  
    {  
        SplayNode<T> *node=new SplayNode<T>(val);  
        *temp=node; 
        node->parent=parent; //设置父节点。  
        return true;  
    }  
    return false;  
}  


//查找并且伸展
template<typename T>
bool SplayTree<T>::search(T val)  
{  
    SplayNode<T> * parent=NULL;  
    SplayNode<T> **temp=NULL;  
    temp=search_val(val, parent);  
    if (*temp && *temp!=root)  
    {  
        Splay(*temp);  
        return true;  
    }  
    return false;  
}  

//search_val 返回查找到的结点 以及parent
template<typename T>
SplayNode<T>** SplayTree<T>::search_val(T val,SplayNode<T>* &parent)  
{  
    return __search_val(root,val,parent);
}

template<typename T>
SplayNode<T>** SplayTree<T>::__search_val(SplayNode<T>* &node,T val,SplayNode<T>* &parent)  
{  
    if (node==NULL)  
        return &node;  
    if (node->val>val)  
        return __search_val(node->lchild,val,parent=node);  
    else if(node->val<val)  
        return __search_val(node->rchild,val,parent=node);  
    return &node;  
} 

template<typename T>
void SplayTree<T>::up(SplayNode<T>* node){
	SplayNode<T>* parent;  
	SplayNode<T>* grandparent;
    int i,j;  
    parent=node->parent;  
    grandparent=parent->parent;  
    i=grandparent->lchild==parent ? -1:1;  
    j=parent->lchild==node ?-1:1;  
    if (i==-1 && j==-1) //AVL树中的LL型  
        RR_Rotate(node);  
    else if(i==-1 && j==1) //AVL树中的LR型  
        LR_Rotate( node);  
    else if(i==1 && j==-1) //AVL树中的RL型  
        RL_Rotate( node);  
    else                    //AVL树中的RR型  
        LL_Rotate(node);  
}



template<typename T>
void SplayTree<T>::Splay(SplayNode<T> *node){
	while (root->lchild!=node && root->rchild!=node && root!=node) //当前结点不是根，或者不是其根的左右孩子，则根据情况进行旋转操作  
        up(node);  
    if (root->lchild==node) //当前结点为根的左孩子，只需进行一次单右旋  
        root=R_Rotate(node);  
    else if(root->rchild==node) //当前结点为根的右孩子，只需进行一次单左旋  
        root=L_Rotate(node);  
}


//两次拔高

template<typename T>
SplayNode<T>* SplayTree<T>::LR_Rotate(SplayNode<T> * node) {
	 L_Rotate(node); 
     R_Rotate(node);
}


template<typename T>
SplayNode<T>* SplayTree<T>::RL_Rotate(SplayNode<T> * node) {
	 R_Rotate(node); //先右后左  
     L_Rotate(node);  
}




/*
注意这里先旋转父亲，再旋转儿子进行了优化
*/


template<typename T>
SplayNode<T>* SplayTree<T>::LL_Rotate(SplayNode<T> * node)  
{  
    L_Rotate(node->parent);  
    L_Rotate(node);  
}  

template<typename T>
SplayNode<T>* SplayTree<T>::RR_Rotate(SplayNode<T> * node)  
{  
    R_Rotate(node->parent);  
    R_Rotate(node);  
}



/*

注意和AVL旋转算法是一样的是，不同之处有两点：
①视角不同，splay旋转视角是提升的结点

②splay旋转时候要更新 父亲与儿子（由于和AVL指向区别产生  AVL直接指向 父亲的儿子）

*/


template<typename T>
SplayNode<T>* SplayTree<T>::L_Rotate(SplayNode<T> *node){
	if(node==NULL)
		return NULL;
	SplayNode<T>* parent =node->parent;
	SplayNode<T>* grandparent =parent->parent;
	parent->rchild=node->lchild;
	if(node->lchild)
		node->lchild->parent=parent;
	node->lchild=parent;
	parent->parent=node;
	node->parent=grandparent;
	if(grandparent){
		if (grandparent->lchild==parent)  
            grandparent->lchild=node;  
        else  
            grandparent->rchild=node;  	
	}
	else
		root=node;
	return node;
}


template<typename T>
SplayNode<T> * SplayTree<T>::R_Rotate(SplayNode<T> *node){

	if (node==NULL)  
        return NULL;  
    SplayNode<T>* parent,*grandparent;  
    parent=node->parent;  
    grandparent=parent->parent;  
    parent->lchild=node->rchild;  
    
    if (node->rchild)  
        node->rchild->parent=parent;  
    node->rchild=parent;  
    parent->parent=node;  
    node->parent=grandparent;  
    
    if (grandparent)  
    {  
        if (grandparent->lchild==parent)  
            grandparent->lchild=node;  
        else  
            grandparent->rchild=node;  
    }  
    else  
        root=node;  
    return node;  
}
