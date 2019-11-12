#include <iostream>
#include <cstring>
#include <queue>
#include <stack>
using namespace std;

class Graph{
	private:
		int** G;	 			//邻接矩阵 
		int* isvisited;			//访问数组 
		int Nv;					//顶点数
		int Ne;					//边数 
	public:
		//构造函数 
		Graph(int nv , int ne){
			this->Nv = nv;
			this->Ne = ne;
			this->G = new int*[nv+1];
			this->isvisited = new int[nv+1];
			memset(isvisited,0,sizeof(isvisited[0])*(nv+1));
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
		
		//重置函数
		void reset(){
			memset(this->isvisited,0,sizeof(this->isvisited[0])*(this->Nv+1));
		}
		
		//广度优先遍历BFS 
		void BFS(int vertex){
			queue<int> queue;
			queue.push(vertex);			//初始结点入队 
			this->isvisited[vertex] = 1;
			int now;
			while(!queue.empty()){		//队不空一直循环 
				now = queue.front();	//对头元素出栈 	
				queue.pop();
				cout<<now<<" ";				//打印当前结点
				int i = 1;
				while(i <= this->Nv){		//与当前结点相邻且未被访问的结点入队 
					if(this->G[now][i] == 1 && isvisited[i] == 0){
						queue.push(i);
						this->isvisited[i] = 1;	//访问数组相应的置1 
					}
					i++;
				}
			}
		}
		
		//递归深度优先遍历DFS 
		void DFS1(int vertex){
			cout<<vertex<<" ";					//打印第一个结点 
			this->isvisited[vertex] = 1;		//相应位的访问数组置1 
			for(int i = 1 ; i <= this->Nv ; i++){
				//依次递归遍历当前结点的未被访问的邻接点 
				if(this->G[vertex][i] == 1 && this->isvisited[i] == 0){
					this->isvisited[i] = 0;
					this->DFS1(i);
					this->isvisited[i] = 0; 
				}
			}
			this->isvisited[vertex] = 0;
		}
		
		//非递归深度优先遍历DFS
		void DFS2(int vertex){
			stack<int> stack;
			stack.push(vertex);				//当前结点入栈 
			this->isvisited[vertex] = 1;	//相应位的访问数组置1 
			int now;
			while(!stack.empty()){			//栈不空则一直循环 
				now = stack.top();			//当前结点出栈 
				stack.pop();
				cout<<now<<" ";				//打印当前结点
				//把当前结点的未被访问的邻接点依次入栈并把相应访问数组置1 
				for(int i = 1 ; i <= this->Nv ; i++){
					if(this->G[now][i] != 0 && this->isvisited[i] == 0){
						stack.push(i);
						this->isvisited[i] = 1;
					}
				} 
			}
		} 
};

int main()
{
	cout<<"请输入结点总数与边数:"<<endl; 
	int nv,ne;
	cin>>nv>>ne;
	Graph graph(nv,ne);
	cout<<"请输入第一个访问的结点："<<endl;
	int now;
	cin>>now;
		
	cout<<"广度优先遍历（BFS）序列为："<<endl; 
	graph.BFS(now);
	cout<<endl;
	
	graph.reset();
	cout<<"递归深度优先遍历（DFS）序列为："<<endl; 
	graph.DFS1(now);
	cout<<endl;
	
	graph.reset();
	cout<<"非递归深度优先遍历（DFS）序列为："<<endl; 
	graph.DFS2(now);
	cout<<endl;	
	
	return 0;
}
