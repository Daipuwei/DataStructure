#include <iostream>
#include <cstring>
#include <stack>
#include <queue>
using namespace std;

const int MAX = 65535;

class Graph{
	private:
		int** G;					// 邻接矩阵
		int** dist;					// 距离数组 
		int** path;					// 路径数组 
		int Nv;						// 顶点数
	public:
		//构造函数
		Graph(int nv, int ne){
			this->Nv = nv;
			G = new int*[nv+1];
			dist = new int*[nv+1];
			path = new int*[nv+1]; 
			for(int i = 0 ; i < nv+1 ; i++){
				G[i] = new int[nv+1];
				dist[i] = new int[nv+1];
				path[i] = new int[nv+1];
				memset(path[i],-1,sizeof(path[0][0])*(nv+1));
				for(int j = 0 ; j < nv+1 ; j++){
					this->G[i][j] = this->dist[i][j] = MAX;
				} 
				this->G[i][i] = this->dist[i][i] = 0; 
			}
			cout<<"请输入边与权重:"<<endl;
			for(int i = 0 ; i < ne ; i++){
				int v1,v2,weight;
				cin>>v1>>v2>>weight;
				this->G[v1][v2] = this->G[v2][v1] = weight;
				this->dist[v1][v2] = this->dist[v2][v1] = weight;
			}	
		}
		
		//Floyd算法(多源最短路径算法) 
		bool Floyd(){
			for(int k = 1 ; k < this->Nv+1 ; k++){	//k代表中间顶点 
				for(int i = 1  ; i < this->Nv+1 ; i++){//i代表起始顶点 
					for(int j = 1 ; j < this->Nv+1 ; j++){//j代表终点 
						if(this->dist[i][k] + this->dist[k][j] < this->dist[i][j]){
							this->dist[i][j] = this->dist[i][k] + this->dist[k][j];
							if(i == j && this->dist[i][j] < 0){//发现了负值圈 
								return false;
							}
							this->path[i][j] = k;
						}					
					}
				}
			}
			return true; 
		}
		
		// 分治法寻找start到end最短路径的中间结点 
		void Find(queue<int> &q ,int start,int end){
			int mid = this->path[start][end];
			if(mid == -1){
				return;
			}
			Find(q,start,mid);
			q.push(mid);
			Find(q,mid,end);
		}

		//打印start顶点到end顶点的路径 
		void Print_Path(int start,int end){
			queue<int> queue;
			queue.push(start);
			this->Find(queue,start,end); 
			queue.push(end);
			cout<<queue.front();
			queue.pop();
			while(!queue.empty()){
				cout<<"->"<<queue.front();
				queue.pop();
			}
			cout<<endl;
		}
		
		void Print_Floyd(){
			int i,j,k;
			for(int i = 1 ; i < this->Nv+1 ; i++){
				for(int j = 1 ; j < this->Nv+1 ; j++){
					cout<<this->path[i][j]<<" ";
				}
				cout<<endl;
			} 
			cout<<"	length		path"<<endl; 
			for(i = 1 ; i < this->Nv+1 ; i++){
				for(j = i+1 ; j < this->Nv+1 ; j++){
					cout<<i<<"->"<<j<<"	";
					cout<<this->dist[i][j]<<"		"; 	
					this->Print_Path(i,j);
				}
				cout<<endl;
			}
		}
};

int main()
{
	cout<<"请输入顶点数与边长数:"<<endl;
	int nv,ne;
	cin>>nv>>ne; 
	Graph graph(nv,ne);
	if(graph.Floyd()){
		cout<<"各个顶点的最短路径为："<<endl; 
		graph.Print_Floyd();
	}
	
	return 0;
 }  
