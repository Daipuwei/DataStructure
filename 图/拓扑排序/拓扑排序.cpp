#include <iostream>
#include <cstring> 
#include <queue> 
using namespace std;

class Graph{
	private:
		int** G;					//邻接矩阵
		int* Indegree;				//入度
		int Nv;						//定点数
		vector<int> TopOrder;		//拓扑排序 
	public:
		//构造函数
		Graph(int nv , int ne){
			this->Nv = nv;
			this->G = new int*[nv+1];
			this->Indegree = new int[nv+1];
			memset(this->Indegree,0,sizeof(this->Indegree[0])*(nv+1));
			for(int i = 0 ; i < nv+1 ; i++){
				this->G[i] = new int[nv+1];
				memset(this->G[i],0,sizeof(this->G[0][0])*(nv+1));
			}
			cout<<"请输入边："<<endl;
			//生成有向图 
			for(int i = 0 ; i < ne ; i++){
				//v1是起始顶点，v2是终止边 
				int v1,v2;
				cin>>v1>>v2;
				this->G[v1][v2] = 1;
				this->Indegree[v2]++;	 //终止边入度加1 
			}
		}
		
		//拓扑排序
		bool TopSort(){
			queue<int> queue;
			//入度为0的顶点加入队列里 
			for(int i = 1 ; i < this->Nv+1 ; i++){
				if(this->Indegree[i] == 0){
					queue.push(i);
				}	
			}
			while(!queue.empty()){//队列不空一直循环 
				int vertex = queue.front();
				queue.pop();	//顶点出队
				this->TopOrder.push_back(vertex);//顶点加入拓扑序 
				for(int i = 1 ; i < this->Nv+1 ; i++){
					if(this->G[vertex][i] != 0){
						//把与vertex相关的边消去,即对应顶点入度减1
						this->Indegree[i]--;
						//顶点入度为0则入队 
						if(this->Indegree[i] == 0){
							queue.push(i);
						}
					}
				} 
			}
			//判断拓扑序中是否有Nv个顶点 ,因为上面循环结束
			//也有可能是存在环而结束的 
			if(this->TopOrder.size() != this->Nv){//没有nv个顶点 
				return false;//说明有向无环图 
			}else{
				return true;//说明不是有向无环图 
			}
		}
		
		//打印拓扑序
		void Print_TopOrder(){
			for(int i = 0 ; i < this->TopOrder.size() ; i++){
				cout<<this->TopOrder[i]<<" ";
			}
		} 
};

int main()
{
	cout<<"请输入定点数与边数:"<<endl;
	int nv,ne;
	cin>>nv>>ne; 
	Graph graph(nv,ne);
	if(graph.TopSort()){
		cout<<"该图的拓扑序排序为："<<endl; 
		graph.Print_TopOrder();
	}
	
	return 0;
 } 
