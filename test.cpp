#include"SplayTree.h"
#include<iostream>
using namespace std;
int main(){
	SplayTree<int> tree;
	bool flag;
	//tree.root=NULL;
	for(int i=0;i<5;i++)
	tree.insert(i);	
	tree.preOrderTraverse(tree.root);
	tree.remove(3);
	//cout<<endl<<tree.find(5)->val;
	//cout<<"result: "<<tree.root->val<<endl;
	
	cout<<endl;
	tree.search(2);
	tree.preOrderTraverse(tree.root);
	tree.search(4);
	cout<<endl;
	tree.preOrderTraverse(tree.root);
}