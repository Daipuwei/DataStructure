#include <iostream>
#include <cstring>
#include <vector> 
using namespace std;

const int MAX = 65535; 
const int Min_Data = -32768;

//并查集 
class UF{
	private:
		int* path;		//父亲结点 
		int size;		//容量 
	public:
		//构造函数 
		UF(int size){
			this->size = size;
			this->path = new int[size+1];
			memset(this->path , -1 ,sizeof(path[0])*(size+1));
		}
		
		//查找操作,采用路径压缩 
		int Find(int x){
			if(this->path[x] < 0){
				return x;
			}else{
				//首先查找x的父节点path[x]，然后把根节点变成path[x],之后再返回根 
				return this->path[x] = this->Find(this->path[x]);
			}
		}
		
		//并操作
		void Union(int root1 ,int root2){
			root1 = this->Find(root1);
			root2 = this->Find(root2);
			//集合里存的是集合个数的相反数,大集合并小集合 
			if(this->path[root1] < this->path[root2]){//集合1比集合2大 
				this->path[root1] += this->path[root2];
				this->path[root2] = root1;
			}else{//反之集合2比集合1大 
				this->path[root2] += this->path[root1];
				this->path[root1] = root2;
			} 
		} 
		
		//检查是否产生回路
		bool CheckCircle(int root1, int root2){
			root1 = this->Find(root1);
			root2 = this->Find(root2);
			if(root1 == root2){//如果产生回路 
				return false;
			}else{//不产生回路
				this->Union(root1,root2);
				return true;
			}
		} 
};

//边类 
class Edge{
	private:
		int Start_Vertex;	//起始边
		int End_Vertex;		//终止边
		int Weight;			//边的权重
	public:
		//构造函数
		void Set(int start_vertex,int end_vertex ,int weight){
			this->Start_Vertex = start_vertex;
			this->End_Vertex = end_vertex;
			this->Weight = weight;
		}
		
		//打印边
		void Print(){
			cout<<this->Start_Vertex<<"\t"<<this->End_Vertex<<"\t"<<this->Weight<<endl;
		}
		
		int getWeight(){
			return this->Weight;
		}
		
		int getStartVertex(){
			return this->Start_Vertex;
		}
		
		int getEndVertex(){
			return this->End_Vertex;
		}
};

class MinHeap{
	private:
		vector<Edge> Edges;		//边集数组
		int capacity;		//最大容量 
		int size;			//当前规模 
	public:
		//构造函数
		MinHeap(int size){
			this->capacity = size*2; 
			this->size = 0;
			this->Edges.reserve(this->capacity);
			Edge edge;
			edge.Set(0,0,Min_Data);
			this->Edges.push_back(edge);
		}
		
		//把Edge[n]为根的子堆调整为最小堆 
		void PreDown(int n){
			Edge edge = this->Edges[n];	//保存下标为n的边
			int parent,child;
			for(parent = n ; parent*2 <= this->size ; parent = child){
				child = parent*2;
				if(child != this->size){
					int wl = this->Edges[child].getWeight();//左孩子权重 
					int wr = this->Edges[child+1].getWeight();//右孩子权重
					if(wr < wl){//右孩子权重小于左孩子权重 
						child++;//选择右孩子 
					}
				}
				//如果根节点权重小于子堆，那么找到合适位置，跳出循环 
				if(edge.getWeight() < this->Edges[child].getWeight()){
					break;
				}else{
					this->Edges[parent] = this->Edges[child];
				} 
			}
			this->Edges[parent] = edge;
		} 
		
		//构造最小堆
		void Create(vector<Edge> &set){
			for(int i = 0 ; i < set.size() ; i++){
				this->Edges[++this->size] = set[i];
			}
			//从最后一个元素的父亲开始，把自己为根的子堆调整为最小堆 
			for(int i = this->size/2 ; i >= 1 ; i--){
				this->PreDown(i);
			}
		}
		
		//删除操作 
		Edge DeleteMin(){
			if(this->IsEmpty()){
				Edge edge;
				edge.Set(0,0,Min_Data);
				return edge;
			} 
			Edge min_edge = this->Edges[1];
			this->Edges[1] = this->Edges[this->size];
			this->size--;
			this->PreDown(1);
			return min_edge;
		}
		
		//判断最小堆是否为空 
		bool IsEmpty(){
			return this->size == 0;
		}
		
		void Print(){
			cout<<"最小堆的元素有："<<this->size<<endl;
            for(int i = 1 ; i <= this->size ; i++){
                cout<<this->Edges[i].getStartVertex()<<" "<<this->Edges[i].getEndVertex()<<" "<<this->Edges[i].getWeight()<<endl;
            }
        }
};

class Graph{
	private:
		int** G;				//邻接矩阵
		int Nv;					//顶点数
		int Ne;					//边数 
		vector<Edge> MST;				//最小生成树的边集合 
		vector<Edge> Edge_Set;			//边集合 
	public:
		//构造函数
		Graph(int nv ,int ne){
			this->Nv = nv;
			this->Ne = ne;
			this->MST.reserve(this->Nv-1);
			this->Edge_Set.reserve(ne);
			this->G = new int*[nv+1];
			for(int i = 0 ; i < nv+1 ; i++){
				this->G[i] = new int[nv+1];
				for(int j = 0 ; j < nv+1 ; j++){
					this->G[i][j] = MAX;
				}
			}
			cout<<"请输入边与边长："<<endl;
			for(int i = 0 ; i < ne ; i++){
				int v1,v2,weight;
				cin>>v1>>v2>>weight;
				this->G[v1][v2] = this->G[v2][v1]= weight;
				Edge edge;
				edge.Set(v1,v2,weight);
				Edge_Set.push_back(edge); 
			}
		}
		
		//Kruskal算法
		int Kruskal(){ 
			int sum_weight = 0;
			UF uf(this->Nv);			//构造并查集
			int cnt = 0;
			//构造边集合最小堆 
			MinHeap minheap(this->Ne);
			minheap.Create(this->Edge_Set);
			int edge_cnt = 0;
			//最小生成树里未收录Nv-1条边且边集合里还有边则一直循环 
			while(edge_cnt != this->Nv-1 && !minheap.IsEmpty()){
				Edge min_edge = minheap.DeleteMin(); 
				int start= min_edge.getStartVertex();
				int end = min_edge.getEndVertex();
				if(uf.CheckCircle(start,end)){//不构成回路
					//对应的边收录到最小生成树 
					this->MST.push_back(min_edge);
					this->MST[edge_cnt++] = min_edge;
 					sum_weight += min_edge.getWeight();
				}
			}
			if(edge_cnt < this->Nv-1){
				sum_weight = -1;
			}
			return sum_weight; 
		}
		
		void Print_Kruskal(){
			cout<<"Kruskal算法构造的最小生成树的边集合为："<<endl;
			cout<<"源点\t终点\t权重"<<endl;
			for(int i = 0 ; i < this->Nv-1 ; i++){
				Edge edge = this->MST[i];
				edge.Print();
			}	
		}
};

int main()
{
	int nv,ne;
	cout<<"请输入顶点数与边数:"<<endl;
	cin>>nv>>ne;
	Graph graph(nv,ne);
	int min_weight = graph.Kruskal();
	if(min_weight != -1){
		cout<<"Kruskal算法生成的最小生成树的权重和为："<<endl;
		cout<<min_weight<<endl;
		graph.Print_Kruskal();	
	} 
	
	return 0;
 } 
