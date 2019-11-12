#include <iostream>
#include <cstring>
#include <vector>
using namespace std;

const int MAX = 65535;

//边类 
class Edge{
	private:
		int Start_Vertex;	//起始边
		int End_Vertex;		//终止边
		int Weight;			//边的权重
	public:
		//构造函数
		Edge(int start_vertex,int end_vertex , int weight){
			this->Start_Vertex = start_vertex;
			this->End_Vertex = end_vertex;
			this->Weight = weight;
		}
		
		//打印边
		void Print(){
			cout<<this->Start_Vertex<<"\t"<<this->End_Vertex<<"\t"<<this->Weight<<endl;
		}	 
};

//图类 
class Graph{
	private:
		int** G;		//邻接矩阵
		int Nv;			//顶点数
		int* dist;		//距离数组，各个顶点到最小生成树的距离 
		int* parent;	//父亲节点数组
		vector<Edge>   MST;		//最小生成树的边集合 
	public:
		//构造函数
		Graph(int nv ,int ne){
			this->Nv = nv;
			this->MST.reserve(ne);
			this->G = new int*[nv+1];
			this->dist = new int[nv+1];
			this->parent = new int[nv+1];
			for(int i = 0 ; i < nv+1 ; i++){
				this->G[i] = new int[nv+1];
				this->dist[i] = MAX;
				for(int j = 0 ; j < nv+1 ; j++){
					this->G[i][j] = MAX;
				}
			}
			cout<<"请输入边与边长："<<endl;
			for(int i = 0 ; i < ne ; i++){
				int v1,v2,weight;
				cin>>v1>>v2>>weight;
				this->G[v1][v2] = this->G[v2][v1]= weight;
			}
		}
		
		//寻找最小距离顶点函数
		int FindMinDist(){
			int MinDist = MAX;
			int MinV = 0;
			for(int i = 1 ; i < this->Nv+1 ; i++){//堆每个顶点进行遍历 
				// 若V未被收录，且dist[V]更小
				if(this->dist[i] != 0 && this->dist[i] < MinDist){
					//更新最小距离与最小顶点 
					MinDist = this->dist[i];
					MinV = i;
				}
			}
			if(MinDist < MAX){
				//最小距离小于正无穷则返回相应的顶点 
				return MinV; 
			}
			//否则返回会-1的错误标志 
			return -1;
		} 
		
		//普里姆(Prim)算法,已vertex为根节点的的最小生成树 
		int Prim(int vertex){
			int cnt = 0;							//收录顶点的个数
			int sum_weight = 0;					//最小生成树的权重和
			for(int i = 1 ; i < this->Nv+1 ; i++){
				this->parent[i] = vertex;		//暂时把父亲结点初始化为输出的初始顶点 
				this->dist[i] = this->G[vertex][i];	//i顶点到最小生成树的距离为vertex与i之间边长 
			}
			this->parent[vertex] = -1;	//把初始结点设置为最小生成树的根节点
			this->dist[vertex] = 0;		//收录初始顶点，初始结点到最小生成树的距离为0 
			cnt++;	//收录的定点数加1
			while(1){
				int cur_vertex = this->FindMinDist(); 	//寻找当前最小距离顶点
				if(cur_vertex == -1){//未能找到最小的结点
					//有两种可能，一是所有顶点已经全部被收录到最小生成树了
					//而是所有节点都不连通 
					break; 
				}
				sum_weight += this->dist[cur_vertex];
				//把this->parent[cur_vertex]与cur_vertex构成边插入到最小生成树的边集合里 
				Edge edge(this->parent[cur_vertex],cur_vertex,this->dist[cur_vertex]);
				this->MST.push_back(edge);
				cnt++;
				//置零说明已经收录到最小生成树里了，故cur_vertex顶点到最小生成树的距离为0
				this->dist[cur_vertex] = 0;
				for(int i = 1 ; i < this->Nv+1 ; i++){//对当前最小距离顶点的所有的邻接点进行遍历
					//如果邻接点i不是根结点且跟cur_vertex直接相邻 
					if(this->dist[i] != 0 && this->G[cur_vertex][i] < MAX){
						//如果cur_vertex与i之间的边小于i到最小生成树的把距离 
						if(this->G[cur_vertex][i] < this->dist[i]){
							//更新相应距离数组与父亲结点 
							this->dist[i] = this->G[cur_vertex][i];
							this->parent[i] = cur_vertex; 
						}
					}
				}
			}                            
			//上述循环结束有两种可能，一是所有顶点已经全部被收录到最小生成树了
			//而是所有节点都不连通 ，故需要判断最小生成树的结点是否与顶点数相同 
			if(cnt != this->Nv){
				sum_weight = -1;
			}
			return sum_weight; 
		}
		
		//打印最小生成树的边集合 
		void Print_Prim(){
			vector<Edge>:: iterator it;
			cout<<"Prim算法构造的最小生成树的边集合为："<<endl;
			cout<<"源点\t终点\t权重"<<endl;
			for(it = this->MST.begin() ; it != this->MST.end() ; it++){
				it->Print();
			}
		}
};

int main()
{
	int nv,ne;
	cout<<"请输入顶点数与边数:"<<endl;
	cin>>nv>>ne;
	Graph graph(nv,ne);
	cout<<"请输一个初始顶点："<<endl;
	int vertex;
	cin>>vertex;
	int min_weight = graph.Prim(vertex);
	cout<<min_weight;
	if(min_weight != -1){
		cout<<"Prim算法生成的最小生成树的权重和为："<<endl;
		cout<<min_weight<<endl;
		graph.Print_Prim();	
	}
	
	return 0;
 } 
