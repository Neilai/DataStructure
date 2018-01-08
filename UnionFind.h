class UnionFind{
private:
	int *parent;
	int num;
public:	
	UnionFind(int num){
		parent=new int[num];
		this->num=num;
		for(int i=0;i<num;i++)
			parent[i]=-1;
	}

	int find(int p){
		while(parent[p]>0)
			p=parent[p];
		return p;
	}

	bool isConnected(int p,int q){
		return find(p)==find(q);
	}
	int getNum(int p){
		int q=find(p);
		return 0-parent[q];
	}
	void merge(int p,int q){
		int root1=find(p);
		int root2=find(q);
		if(parent[root1]>parent[root2]){
			parent[root2]+=parent[root1];
			parent[root1]=root2;
		}
		else{
			parent[root1]+=parent[root2];
			parent[root2]=root1;
		}
	}

};