/*#include <iostream>
#include <cstring>
#include <stack>
#include <stdio.h>
using namespace std;

const int MAX = 65535;

class Graph{
	private:
		int** G;	 			//邻接矩阵 
		int* dist;				//距离数组
		int* path;				//路径数组
		int* collected;			//收录数组 
		int Nv;					//顶点数
		int Ne;					//边数 
	public:
		//构造函数 
		Graph(int nv , int ne){
			this->Nv = nv;
			this->Ne = ne;
			this->G = new int*[nv+1];
			this->dist = new int[nv+1];
			this->path = new int[nv+1];
			this->collected = new int[nv+1]; 
			for(int i = 0 ; i < this->Nv+1 ; i++){
				this->dist[i] = MAX;
			}
			memset(this->path,-1,sizeof(this->path[0])*(nv+1));
			memset(this->collected,0,sizeof(this->collected[0])*(nv+1));
			for(int i = 0 ; i < nv+1 ; i++){
				this->G[i] = new int[nv+1];
				for(int j = 0 ; j < nv+1 ; j++){
					this->G[i][j] = MAX; 
				}
			}
			cout<<"请输入边与权重："<<endl;
			for(int i = 0 ; i < ne ; i++){
				int v1,v2,weight;
				cin>>v1>>v2>>weight;
				this->G[v1][v2] = weight;
				this->G[v2][v1] = weight;
			}
		}
		
		//遍历邻接点寻找最小距离顶点
		int FindMinVertex(){
			int MinDist = MAX;	//初始化最小距离
			int v,MinV = 0;
			for(v = 1 ; v < this->Nv+1 ; v++){
				if(this->collected[v] == 0 && this->dist[v] < MinDist){
					//v没有被收录且dist[v]更小
					MinDist = dist[v];
					MinV = v; 
				}
			}
			if(MinDist < MAX){//找到最小的dist 
				return MinV;	//返回对应顶点的下标 
			}else{
				return -1;	//若这样的顶点不存在则返回-1 
			} 
		} 
		
		//有权图的Dijikstra(遍历整个数组寻找最小路径顶点)
		bool Dijikstra(int vertex){
			//根据初始结点初始化距离数组与路径数组 
			for(int i = 0 ; i < this->Nv+1 ; i++){
				//在构造函数里dist已经全部初始化为MAX
				//G存在边时为权重，没有边时为MAX 
				this->dist[i] = this->G[vertex][i];
				if(this->dist[i] < MAX){
					this->path[i] = vertex;
				}
			}
			this->dist[vertex] = 0;		//初始结点的距离为０
			this->collected[vertex] = 1;	//初始结点标记为已收录 
			while(1){
				//V是未被收录定点中dist最小者 
				int V = this->FindMinVertex(); 
				if(V == -1){//未找到这样的V则跳出循环 
					break;
				} 
				this->collected[V] = 1;//标记为已经被收录 
				//遍历图中每个顶点 
				for(int w = 1 ; w < this->Nv+1 ; w++){
					//若w是V的邻接点且未被收录 
					if(this->collected[w] == 0 && this->G[V][w] < MAX){
						if(this->G[V][w] < 0){//存在负边时 
							return false;	//结束算法 
						}
						//若收录V使得dist[w]变小 
						if(this->dist[V] + this->G[V][w] < this->dist[w]){
							//更新dist[w] 
							this->dist[w] = this->dist[V] + this->G[V][w]; 
							this->path[w] = V;//更新路径 
						} 
					} 
				} 
			}
			return true;
		}
		
		//打印迪杰斯特拉路径
		void Print_Dijikstra(int vertex){
			for(int i = 1 ; i < this->Nv+1 ; i++){
				if(i == vertex){
					continue;
				} 
				stack<int> stack;
				stack.push(i);
				cout<<vertex<<"到"<<i<<"的最短路径为：";
				int j = i;
				while(this->path[j] != -1){//路径上的元素一次入栈 
					j = this->path[j];
					stack.push(j);	
				}
				//打印路径 
				cout<<stack.top();
				stack.pop(); 
				while(!stack.empty()){
					cout<<" -> "<<stack.top();
					stack.pop();
				}
				cout<<endl<<"最短路径长度为："<<this->dist[i]<<endl;
			}
		}
};

int main() 
{
	cout<<"请输入顶点数与边数："<<endl; 
	int nv ,ne;
	cin>>nv>>ne;
	Graph graph(nv,ne);
	cout<<"请输入一个起始点："<<endl;
	int vertex;
	cin>>vertex;
	if(graph.Dijikstra(vertex)){
		graph.Print_Dijikstra(vertex); 	
	}
	
	return 0;
}*/

#include <iostream>
#include <cstring>
#include <stack>
#include <queue> 
#include <vector> 
using namespace std;

const int MAX = 65535;
int G[1001][1001];
int dist[1001] = {0};
int path[1001] = {0};
int visited[1001] = {0};
int Nv,Ne;
int start;

struct cmp{
	bool operator()(int &a,int &b){
		return dist[a]>dist[b];
	}
};

void Create_Graph()
{
	//初始化距离数组为正无穷 
	for(int i = 0 ; i < 1001 ; i++){
		dist[i] = MAX;
	}
	//初始化路径数组为-1 
	memset(path,-1,sizeof(path[0])*(1001));
	//初始化访问数组为-1 
	memset(visited,0,sizeof(visited[0])*(1001));
	//memset(this->collected,0,sizeof(this->collected[0])*(nv+1));
	for(int i = 0 ; i < 1001 ; i++){
		for(int j = 0 ; j < 1001 ; j++){
			G[i][j] = MAX;	
		}
	}
	//初始化图
	cout<<"请输入顶点数与边数："<<endl; 
	cin>>Nv>>Ne;
	cout<<"请输入边与权重："<<endl;
	for(int i = 0 ; i < Ne ; i++){
		int v1,v2,weight;
		cin>>v1>>v2>>weight;
		G[v1][v2] = G[v2][v1] = weight;
	}	
}

//迪杰斯特拉算法 
bool Dijikstra(int vertex)
{
	priority_queue<int,vector<int>,cmp> q;
	//源顶点加入最小堆 
	q.push(vertex);
	//初始化源顶点的dist为0 
	dist[vertex] = 0;
	visited[vertex] = 1; 
	//最小堆不为空，一直循环 
	while(!q.empty()){
		//从最小堆中弹出最小元素 
		int start = q.top();
		q.pop();
		for(int i = 1 ; i < Nv+1 ; i++){
			//负值圈问题 
			if(G[start][i] < 0){
				return false;
			}
			// bfs遍历领接结点 
			if (G[start][i] < MAX){
				if(visited[i] == 0){
					// i到start的最小距离大于dist[start]+G[start][i]
					if(dist[i] > dist[start] + G[start][i]){
						dist[i] = dist[start] + G[start][i];
						q.push(i);
						path[i] = start;
					}	
				}	
			}
		}
	}
	return true;
}

//打印start到end的最短路径 
void Print(int start ,int end)
{
	stack<int> stack;
	stack.push(end);
	cout<<start<<"到"<<end<<"的最短路径为：";
	int j = end;
	while(path[j] != -1){//路径上的元素一次入栈 
		j = path[j];
		stack.push(j);	
	}
	//打印路径 
	cout<<stack.top();
	stack.pop(); 
	while(!stack.empty()){
	cout<<" -> "<<stack.top();
	stack.pop();
	}
	cout<<"\n"<<"最短路径长度为："<<dist[end]<<endl;
}

void Print_Dijikstra(int vertex)
{
	for(int i = 1 ; i < Nv+1 ; i++){
		if(i == vertex){
			continue;
		} 
		Print(vertex,i); 
	}
}


int main() 
{
	Create_Graph();
	cout<<"请输入一个起始点："<<endl;
	int vertex;
	cin>>vertex;
	if(Dijikstra(vertex)){
		Print_Dijikstra(vertex); 	
	}
	
	return 0;
}
