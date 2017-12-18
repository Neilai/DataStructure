#include <cstddef>
#include<cassert>
#include<iostream>
using namespace std;
#define LH 1
#define EH 0
#define RH -1
#define EQ(a,b) ((a)==(b))
#define LT(a,b) ((a)<(b))

template<typename T>
struct AVLNode{	
	T data;
	int bf;
	AVLNode<T>* lchild;
	AVLNode<T>* rchild;
	AVLNode(){}
	AVLNode(T &e,int ibf=EH,AVLNode *lc=NULL,AVLNode * rc=NULL):data(e),bf(ibf),lchild(lc),rchild(rc){}
};

template<typename T>
class AVLTree{
private:
	void L_Rotate(AVLNode<T> *&);
	void R_Rotate(AVLNode<T> *&);
	void leftBalance(AVLNode<T> *&);
	void rightBalance(AVLNode<T> *&);
    bool __insertAVL(AVLNode<T> *&t,T e ,bool &taller);
    bool __deleteAVL(AVLNode<T>*& t, T key, bool& shorter); 
    AVLNode<T> *__searchAVL(AVLNode<T> *&node,T key);
public:
    AVLNode<T> *root=NULL;
	bool insert(T);
    bool remove(T);
	AVLNode<T> *find(T key);
    void destroyAVL(AVLNode<T> * &node);
	void preOrderTraverse(AVLNode<T> * &node);
	void inOrderTraverse(AVLNode<T> * &node);
};

template<typename T>
AVLNode<T> *AVLTree<T>::find(T key){
    return __searchAVL(root,key);
};

template<typename T>
bool AVLTree<T>::insert(T key){
    bool flag;
    if(__insertAVL(root,key,flag))
        return true;
    else
        return false;
}

template<typename T>
bool AVLTree<T>::remove(T key){
    bool flag;
    if(__deleteAVL(root,key,flag))
        return true;
    else
        return false;
}
template<typename T> 
bool AVLTree<T>::__deleteAVL(AVLNode<T>* & t, T key, bool& shorter)  
{  
    if(t == NULL)                       //不存在该元素   
    {  
        return false;                   //删除失败   
    }  
    else if(EQ(key, t->data))        //找到元素结点  
    {  
        AVLNode<T>* q = NULL;  
        if(t->lchild == NULL)            //左子树为空   
        {  
            q = t;  
            t = t->rchild;  
            delete q;  
            shorter = true;  
        }  
        else if(t->rchild == NULL)       //右子树为空   
        {  
            q = t;  
            t = t->lchild;  
            delete q;  
            shorter = true;  
        }  
        else                            //左右子树都存在,  
        {  
            q = t->lchild;  
            //在右子树寻找最大的
            while(q->rchild)  
            {  
                q = q->rchild;  
            }  
            t->data = q->data;  
            __deleteAVL(t->lchild, q->data, shorter);   //在左子树中递归删除前驱结点   
        }  
    }  
    else if(LT(key, t->data))        //左子树中继续查找   
    {  
        if(!__deleteAVL(t->lchild, key, shorter))  
        {  
            return false;  
        }  
        
        //回溯调整
        
        if(shorter)  
        {  
            switch(t->bf)  
            {  
                case LH:  
                    t->bf = EH;  
                    shorter = true;  
                    break;  
                case EH:  
                    t->bf = RH;  
                    shorter = false;  
                    break;  
                case RH:  
                    rightBalance(t);    //右平衡处理  
                    if(t->rchild->bf == EH)//注意这里，画图思考一下   
                        shorter = false;  
                    else  
                        shorter = true;  
                    break;  
            }  
        }  
    }  
    else                                //右子树中继续查找   
    {  
        if(!__deleteAVL(t->rchild, key, shorter))  
        {  
            return false;  
        }  
        if(shorter)  
        {  
            switch(t->bf)  
            {  
                case LH:  
                    leftBalance(t);     //左平衡处理   
                    if(t->lchild->bf == EH)//注意这里，画图思考一下   
                        shorter = false;  
                    else  
                        shorter = true;  
                    break;  
                case EH:  
                    t->bf = LH;  
                    shorter = false;  
                    break;  
                case RH:  
                    t->bf = EH;  
                    shorter = true;  
                    break;  
            }  
        }  
    }  
    return true;  
}  
/*
   
   自下向上调整AVL树的平衡因子


*/
template<typename T>
bool AVLTree<T>::__insertAVL(AVLNode<T> *&t,T e ,bool &taller)
{  
    
    if(t == NULL)  
    {  
        
        t = new AVLNode<T>(e);             //判断是否为空树
        taller = true;  
    }  
    else  
    {  
        if(EQ(e, t->data))       //树中已含该关键字，不插入   
        {  
            taller = false;  
            return false;  
        }  
        else if(LT(e, t->data)) //在左子树中查找插入点   
        {  
            if(!__insertAVL(t->lchild, e, taller))//左子树插入失败   
            {  
                return false;  
            }  
            
            //这一段代码用来回溯调整
            
            if(taller)                  //左子树插入成功，且左子树增高   
            {  
                switch(t->bf)  
                {  
                    case LH:            //原来t的左子树高于右子树   
                        leftBalance(t); //做左平衡处理   
                        taller = false;  
                        break;  
                    case EH:            //原来t的左子树和右子树等高   
                        t->bf = LH;      //现在左子树比右子树高   
                        taller = true;  //整棵树增高了   
                        break;  
                    case RH:            //原来t的右子树高于左子树  
                        t->bf = EH;      //现在左右子树等高   
                        taller = false;  
                        break;  
                }  
            }  
        }  
        else                            //在右子树中查找插入点   
        {  
            if(!__insertAVL(t->rchild, e, taller))//右子树插入失败   
            {  
                return false;  
            }  
            if(taller)                  //右子树插入成功，且右子树增高  
            {  
                switch(t->bf)  
                {  
                    case LH:            //原来t的左子树高于右子树   
                        t->bf = EH;  
                        taller = false;  
                        break;  
                    case EH:            //原来t的左子树和右子树等高   
                        t->bf = RH;  
                        taller = true;  
                        break;  
                    case RH:            //原来t的右子树高于左子树  
                        rightBalance(t);//做右平衡处理  
                        taller = false;  
                        break;  
                }  
            }  
        }  
    }  
    return true;                        //插入成功   
}  


template<typename T>
void AVLTree<T>::leftBalance(AVLNode<T> *&t)  
{  
    AVLNode<T>* lc = NULL;  
    AVLNode<T>* rd = NULL;  
    lc = t->lchild;  
    switch(lc->bf)  
    {  
        case LH:                    //LL旋转   
            t->bf = EH;  
            lc->bf = EH;  
            R_Rotate(t);          
            break;  
          
        case EH:                    //deleteAVL需要，insertAVL用不着   
            t->bf = LH;  
            lc->bf = RH;  
            R_Rotate(t);  
            break;  
          
        case RH:                    //LR旋转   
            rd = lc->rchild;  
            switch(rd->bf)  
            {  
                case LH:  
                    t->bf = RH;  
                    lc->bf = EH;  
                    break;    
                case EH:  
                    t->bf = EH;  
                    lc->bf = EH;  
                    break;  
                case RH:  
                    t->bf = EH;  
                    lc->bf = LH;  
                    break;  
            }  
            rd->bf = EH;  
            L_Rotate(t->lchild);//不能写L_Rotate(lc);采用的是引用参数   
            R_Rotate(t);  
            break;  
    }  
}  

template<typename T>
void AVLTree<T>::rightBalance(AVLNode<T>* &t)  
{  
    AVLNode<T>* rc = NULL;  
    AVLNode<T> *ld = NULL;  
      
    rc = t->rchild;  
    switch(rc->bf)  
    {  
        case LH:                //RL旋转   
            ld = rc->lchild;   
            switch(ld->bf)  
            {  
                case LH:  
                    t->bf = EH;  
                    rc->bf = RH;  
                    break;  
                case EH:  
                    t->bf = EH;  
                    rc->bf = EH;  
                    break;  
                case RH:  
                    t->bf = LH;  
                    rc->bf = EH;  
                    break;  
            }  
            ld->bf = EH;  
            R_Rotate(t->rchild);//不能写R_Rotate(rc);采用的是引用参数   
            L_Rotate(t);  
            break;  
              
        case EH:                //deleteAVL需要，insertAVL用不着   
            t->bf = RH;  
            rc->bf = LH;  
            L_Rotate(t);  
            break;  
                  
        case RH:                //RR旋转   
            t->bf = EH;  
            rc->bf = EH;  
            L_Rotate(t);  
            break;  
    }  
}  
template<typename T>
void AVLTree<T>::L_Rotate(AVLNode<T> *&p){
	AVLNode<T> *rc=NULL;
	rc=p->rchild;
	p->rchild=rc->lchild;
	rc->lchild=p;
	p=rc;
}

template<typename T>
void AVLTree<T>::R_Rotate(AVLNode<T>* &p)  
{   
    AVLNode<T> * lc = NULL;  
    lc  = p->lchild;     //lc指向p的左子树根结点  
    p->lchild = lc->rchild;   //lc的右子树挂接为p的左子树   
    lc->rchild = p;  
    p = lc;                 //p指向新的根结点   
}  


template<typename T> 
AVLNode<T> *AVLTree<T>::__searchAVL(AVLNode<T> *&node,T key){
  if((node == NULL)||EQ(key,node->data))  
        return node;   
    else if LT(key,node->data) /* 在左子树中继续查找 */  
        return __searchAVL(node->lchild,key);  
    else  
        return __searchAVL(node->rchild,key); /* 在右子树中继续查找 */  

}

template<typename T>
void AVLTree<T>::destroyAVL(AVLNode<T> * &node){
	if(node){
		destroyAVL(node->lchild);
		destroyAVL(node->rchild);
		delete node;
		node=NULL;
	}
}

template<typename T>
void AVLTree<T>::preOrderTraverse(AVLNode<T> * &node){
	if(node){
		cout<<node->data;
		preOrderTraverse(node->lchild);
		preOrderTraverse(node->rchild);
	}
}

template<typename T>
void AVLTree<T>::inOrderTraverse(AVLNode<T> * &node){
	if(node){
		inOrderTraverse(node->lchild);
		cout<<node->data;
		inOrderTraverse(node->rchild);
	}
}