#include"SparseGraph.h"
#include<iostream>
#include<vector>
using namespace std;
int main(){
	SparseGraph G(5);
	G.addedge(0,1,8);
	G.addedge(1,2,7);
	G.addedge(2,3,6);
	G.addedge(3,4,5);
	G.addedge(2,4,4);
	G.addedge(0,4,3);
	G.addedge(1,4,2);
	G.addedge(0,2,1);
	//G.show();
	int path[5];
	double dis[5];
	vector<Edge> tree;
	cout<<G.Prim(0,tree);
	cout<<endl;
	for(int i=0;i<tree.size();i++)
		cout<<tree[i].from<<" "<<tree[i].to<<" ";
	cout<<endl;
	G.show();
	// for(int i=0;i<5;i++)
	// 	cout<<path[i]<<" ";
}