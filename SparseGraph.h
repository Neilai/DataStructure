#include<vector>
#include<queue>
#include<cassert>
#include<iostream>
using namespace std;
class Edge {
public:
	Edge(int a, int b,int c, double d):from(a),to(b),rev(c),weight(d) {
	}
	int from;
	int to;
	int rev;
	double weight;
};
class SparseGraph {
public:
	int v, e;
	bool directed;
	vector<vector<Edge>> g;


	SparseGraph(int n, bool directed=1) {
		assert(n >= 0);
		this->v = n;
		this->e = 0;
		this->directed = directed;
		g = vector<vector<Edge>>(n, vector<Edge>());
	}
	
	int getV(){
		return v;
	}
	void addedge(int from, int  to, double weight) {
		assert(from >=0 && from < v);
		assert(to >=0 && to < v);
		Edge from_edge(from,to,g[to].size(),weight);
		g[from].push_back(from_edge);
		Edge to_edge(to, from, g[from].size() - 1, weight);
		if (directed) {
			g[to].push_back(to_edge);
		}
		e++;
	}

	Edge getedge(int from, int to) {
		assert(from >= 0 && from < v);
		assert(to >= 0 && to < v);
		for (int i = 0; i < g[from].size(); i++)
			if (g[from][i].to == to)
				return g[from][i];
	}

	bool hasedge(int from, int to) {
		assert(from >= 0 && from < v);
		assert(to >=0 && to < v);
		for (int i = 0; i < g[from].size(); i++)
			if (g[from][i].to == to)
				return true;
		return false;
	}

	void show() {
		for (int i = 0; i < v; i++) {
			cout << "vertex " << i <<" :"<< ends;
			for (int j = 0; j < g[i].size(); j++) {
				cout << g[i][j].to << ends;
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

	//迭代器

	class adjIterator {		
	private:
		SparseGraph &G;
		int v;
		int index;
	public:
		adjIterator(SparseGraph &graph, int v):G(graph) {
			this->v = v;
			this->index = 0;
		}

		Edge begin() {
			index = 0;
			if (G.g[v].size())
				return G.g[v][index];
			return Edge(-1, -1, -1, -1);
		}

		Edge next() {
			index++;
			if (index < G.g[v].size())
				return G.g[v][index];
			return Edge(-1, -1, -1, -1);
		}

		bool end() {
		   return index >= G.g[v].size();
		}	
	};
};