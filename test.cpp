#include<iostream>
#include"UnionFind.h"
using namespace std;
int main(){
	UnionFind set(10);
	set.merge(1,2);
	set.merge(2,3);
	set.merge(3,4);
	cout<<set.getNum(0);
	return 1;
}