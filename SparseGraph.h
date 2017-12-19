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

	double Prim(int s,vector<Edge> &tree){		
		double mindis,len=0;
		int minindex;
		int *visited=new int[v];
		double *dist=new double[v];
		int *source=new int[v];
		for(int i=0;i<v;i++){
			visited[i]=0;
			dist[i]=0x3f3f3f3f;
			source[i]=0;
		}
		dist[s]=0;		
		for(int i=0;i<v;i++){	
			mindis=0x3f3f3f3f;
			minindex=0;
			//寻找最小边
			for(int j=0;j<v;j++)
				if(!visited[j]&&mindis>=dist[j]){
					mindis=dist[j];
					minindex=j;
				}		
			visited[minindex]=1;
			
			if(!(minindex==0&&source[minindex]==0))
				tree.push_back(Edge(source[minindex],minindex,-1,mindis));
			len+=mindis;
			//取这个顶点后进行松弛
			adjIterator iter(*this,minindex);
			for(Edge e=iter.begin();!iter.end();e=iter.next())
				if(!visited[e.to]&&dist[e.to]>e.weight){
					dist[e.to]=e.weight;	
					source[e.to]=e.from;
				}
		}
		return len;

	}	



	void Dijkstra(int s,int *path,double *dist){		
		int mindis,minindex;
		int *visited=new int[v];
		for(int i=0;i<v;i++){
			visited[i]=0;
			path[i]=s;
			dist[i]=0x3f3f3f3f;
		}		
		path[s]=-1;dist[s]=0;
		for(int i=0;i<v;i++){	
			mindis=0x3f3f3f3f;
			minindex=0;
			//寻找最小边
			for(int j=0;j<v;j++)
				if(!visited[j]&&mindis>=dist[j]){
					mindis=dist[j];
					minindex=j;
				}
			visited[minindex]=1;
			//取这个顶点后进行松弛
			adjIterator iter(*this,minindex);
			for(Edge e=iter.begin();!iter.end();e=iter.next())
				if(!visited[e.to]&&dist[e.to]>dist[e.from]+e.weight){
					dist[e.to]=dist[e.from]+e.weight;
					path[e.to]=e.from;
				}	
		}

	}

	void BellmanFord(int s,int *path,double *dis){
		for(int i=0; i<v;i++){
			dis[i]=0x3f3f3f3f;
			path[i]=s;
		}
		dis[s]=0;
		path[s]=-1;
		//动态规划，最后要得到经过v-1个点到终点的结果
		for(int i=0;i<v-1;i++){
			for(int j=0;j<v;j++){
				//每一次对所有边进行一次松弛，将图向外扩展一层（一个顶点）
				adjIterator iter(*this,j);
				for(Edge e=iter.begin();!iter.end();e=iter.next()){
					if(dis[e.to]>dis[e.from]+e.weight){
						dis[e.to]=dis[e.from]+e.weight;
						path[e.to]=e.from;
					}
				}
			}
		}
	}

	void SPFA(int s,int *path,double *dis){		
		//初始化很重要，所有距离最大 ，都不在队列
		int *inqueue=new int[v];
		for(int i=0;i<v;i++){
			inqueue[i]=0;
			dis[i]=0x3f3f3f3f;
		}
		path[0]=-1;
		dis[s]=0;
		//把源放入队列
		queue<int> q;
		q.push(s);
		inqueue[s]=1;
		while(!q.empty()){
			int u=q.front();
			q.pop();
			inqueue[u]=0;
			//pop出来的点进行松弛，松弛的点放入队列（如果不在的话）
			adjIterator iter(*this,u);
			for(Edge e=iter.begin();!iter.end();e=iter.next()){
				if(dis[e.to]>dis[e.from]+e.weight){
					dis[e.to]=dis[e.from]+e.weight;
					path[e.to]=e.from;
					if(!inqueue[e.to]){
						q.push(e.to);
						inqueue[e.to]=1;
					}
				}
			}
		}
	}
	

	void Floyd(int** D,int** P){        //D:D[i][j]表示从i到j的最短距离；P:P[i][j]表示从i到j的最短路径上的结点      
	    for(int i=0;i<v;i++)
	        for(int j=0;j<v;j++){    
	            D[i][j]=0x3f3f3f3f;    
	            P[i][j]=i;    
	        }  
	    for(int i=0;i<v;i++){    
	        adjIterator iter(*this,i);
	    	for(Edge e=iter.begin();!iter.end();e=iter.next())
	    		D[e.from][e.to]=e.weight;
	    }   
	    for(int i=0;i<v;i++){    
	        D[i][i]=0;    
	        P[i][i]=0;    
	    }  //注意对角线初始化0  
	    for(int k=0;k<v;k++)    
	        for(int i=0;i<v;i++)    
	            for(int j=0;j<v;j++)    
	                if(D[i][j]>D[i][k]+D[k][j]){    
	                    D[i][j]=D[i][k]+D[k][j];    
	                    P[i][j]=P[k][j];    
	                }  //比较所有i经过点k然后再到j的距离  
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