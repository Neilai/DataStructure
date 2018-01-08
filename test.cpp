#include<iostream>
#include"SparseGraph.h"
using namespace std;
int main(){
	SparseGraph G(5);
	G.addedge(0,1,3);
	G.addedge(0,2,3);
	G.addedge(0,3,3);
	G.addedge(1,3,3);
	G.addedge(2,4,3);
	G.addedge(2,3,3);
	G.addedge(2,3,3);
	G.DFS2(4);	
}
