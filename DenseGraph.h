#include<vector>
#include<queue>
#include<cassert>
#include<iostream>
using namespace std;
class Edge {
public:
	Edge(int a, int b, int c) :from(a), to(b), weight(c) {
	}
	int from;
	int to;
	double weight;
};
class DenseGraph {
private:
	int v, e;
	bool directed;
	double **g;
public:
	DenseGraph(int n, bool directed=1) {
		assert(n >= 0);
		this->v = n;
		this->e = 0;
		this->directed = directed;
		g = new double * [n];
		for (int i = 0; i < n; i++) {
			g[i] = new double[n];
		}
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				g[i][j] = -1;
	}
	
	Edge getedge(int from, int to) {
		return Edge(from, to, g[from][to]);
	}
	void addedge(int from, int  to, double weight) {
		assert(from >= 0 && from < v);
		assert(to >= 0 && to < v);
		g[from][to] = weight;
		if (directed)
			g[to][from] = weight;
		e++;
	}
	
	void show() {
		for (int i = 0; i < v; i++) {
			cout << "vertex " << i << " :" << ends;
			for (int j = 0; j < v; j++) {
				if (g[i][j]>=0)
					cout << j;
			}
			cout << endl;
		}
	}

	void __DFS(int pos,int visited[]){
		adjIterator iter(*this,pos);
		visited[pos]=1;
		cout<<"visit vertex "<<pos<<endl;		
		for(Edge e=iter.begin();!iter.end();e=iter.next()){
			if(!visited[e.to])
				__DFS(e.to,visited);
		}
	}
	
	void DFS(int pos){
        int visited[v];
        for(int i=0;i<v;i++)
         	visited[i]=0;       
        __DFS(pos,visited);
	}

	void __BFS(int pos,int *visited){
		queue<int> q;
		q.push(pos);
		visited[pos]=1;
		while(!q.empty()){
			int cur=q.front();	
			q.pop();
			cout<<"visit vertex "<<cur<<endl;
			adjIterator iter(*this,cur);
			for(Edge e=iter.begin();!iter.end();e=iter.next()){				
				if(!visited[e.to]){
					visited[e.to]=1;
					q.push(e.to);
				}
			}
		}
	}

	void BFS(int pos){
		int visited[v];
		for(int i=0;i<v;i++)
			visited[i]=0;
		__BFS(pos,visited);
	}


	class adjIterator {
	private:
		DenseGraph &G;
		int v;
		int index;
	public:
		adjIterator(DenseGraph &graph, int v) :G(graph) {
			this->v = v;
			this->index = 0;
		}
		Edge begin() {
			index = 0;

			while (G.g[v][index]<0) {
				index++;
			}
			if (index < G.v)
				return Edge(v,index,G.g[v][index]);
			else
				return Edge(-1, -1,-1);
		}

		Edge next(){
			index++;
			while (G.g[v][index]<0) {
				index++;
			}
			if (index < G.v)
				return Edge(v, index, G.g[v][index]);
			else
				return Edge(-1, -1, -1);
		}
		bool end() {
			return index >= G.v;
		}
	};
};
