#include <iostream>
#include <cstring>
#include <stack>
#include <queue> 
#include <vector> 
#include <stdio.h>
using namespace std;

const int MAX = 65535;
int G[1001][1001];
int dist[1001],path[1001];
int Nv,Ne;
int start; 

struct cmp{
	bool operator()(int a,int b){
		return dist[a]>dist[b];
	}
};


void Create_Graph()
{
	//初始化距离数组为正无穷 
	for(int i = 0 ; i < Nv+1 ; i++){
		dist[i] = MAX;
	}
	//初始化路径数组为-1 
	memset(path,-1,sizeof(path[0])*(Nv+1));
	//memset(this->collected,0,sizeof(this->collected[0])*(nv+1));
	for(int i = 0 ; i < Nv+1 ; i++){
		for(int j = 0 ; j < Nv+1 ; j++){
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
		G[v1][v2] = weight;
		G[v2][v1] = weight;
	}	
}

//迪杰斯特拉算法 
bool Dijikstra(int vertex)
{
	//初始化源顶点的dist为0 
	dist[vertex] = 0;
	priority_queue<int,vector<int>,cmp> q;
	//源顶点加入最小堆 
	q.push(vertex);
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
			// i到start的最小距离大于dist[start]+G[start][i]
			if(dist[i] > dist[start] + G[start][i]){
				dist[i] = dist[start] + G[start][i];
				q.push(i);
				path[i] = start;
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
	cout<<"  "<<"最短路径长度为："<<dist[end]<<endl;
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
