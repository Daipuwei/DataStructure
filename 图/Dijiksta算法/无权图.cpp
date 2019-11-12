#include <iostream>
#include <cstring>
#include <queue>
#include <stack>
using namespace std;

class Graph{
	private:
		int** G;	 			//邻接矩阵 
		int* dist;				//距离数组
		int* path;				//路径数组 
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
			memset(this->dist,-1,sizeof(this->dist[0])*(nv+1));
			memset(this->path,-1,sizeof(this->path[0])*(nv+1));
			for(int i = 0 ; i < nv+1 ; i++){
				G[i] = new int[nv+1];
				memset(G[i],0,sizeof(G[i][0])*(nv+1));
			}
			cout<<"请输入边："<<endl;
			for(int i = 0 ; i < ne ; i++){
				int a,b;
				cin>>a>>b;
				this->G[a][b] = 1;
				this->G[b][a] = 1;
			}
		}
		
		//无权图的Dijikstra
		void Unweighted(int vertex){
			queue<int> queue;		//初始化队列
			queue.push(vertex);		//初始结点入队
			int cur_vertex;			//当前结点 
			this->dist[vertex] = 0;		//初始结点的距离为0 
			while(!queue.empty()){
				cur_vertex = queue.front();	//队头结点出队 
				queue.pop();
				//遍历cur_vertex的每个邻接点 
				for(int i = 1  ; i < this->Nv+1 ; i++){
					if((this->G[cur_vertex][i] == 1)&& (this->dist[i] == -1)){
						this->dist[i] = this->dist[cur_vertex]+1;//当前结点的距离是cur_vertex的距离加1 
						this->path[i] = cur_vertex;	//把当前结点的上一个结点设为cur_vertex;
						queue.push(i); 
					}
				}
			}
		}
		
		//打印无权图迪杰斯特拉路径
		void Print_Unweighted(int vertex){
			for(int i = 1 ; i < this->Nv+1 ; i++){
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
				cout<<endl;
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
	graph.Unweighted(vertex);
	graph.Print_Unweighted(vertex); 
	
	return 0;
}
