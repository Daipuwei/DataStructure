#include <iostream>
#include <vector> 
#include <queue> 
#include <stack>
#include <cstring> 
using namespace std;

//边表类 
class EdgeList{
	private:
		int vertex;
		EdgeList* next;
	public:
		EdgeList* Create(int vertex){
			EdgeList* list = new EdgeList;
			list->vertex = vertex;
			list->next = NULL;
			return list;
		}
		
		//寻找最后一个结点
		EdgeList* getLast(EdgeList* list){
			EdgeList* cur = list;
			while(cur){
				if(cur->next == NULL){
					return cur;
				}
				cur = cur->next;
			}
		}
		
		//插入函数 
		EdgeList* Attach(EdgeList* list,int vertex){
			EdgeList* last = this->getLast(list);
			EdgeList* insert = insert->Create(vertex);
			last->next = insert;
			return list;
		}
		
		int getVertex(EdgeList* list){
			return list->vertex;
		}
		
		void Print(EdgeList* list){
			EdgeList* cur = list;
			while(cur){
				cout<<cur->vertex<<" ";
				cur = cur->next;
			}
		}
		
		EdgeList* getNext(){
			return this->next;
		}
}; 


class Graph{
	private:
		vector<EdgeList*> Edgelist;		//邻接表 
		int* isvisited;					//访问数组 
		int Nv;			//顶点数
		int Ne;			//边数 
	public:	
		//构造函数 
		Graph(int nv ,int ne){
			this->Ne = ne;
			this->Nv = nv;
			this->Edgelist.reserve(nv);
			this->isvisited = new int[nv+1];
			memset(this->isvisited,0,sizeof(this->isvisited[0])*(this->Nv+1));
			cout<<"请输入顶点："<<endl;
			//依次构造图的结点 
			for(int i = 0 ; i < this->Nv ; i++){
				int vertex;
				cin>>vertex;
				this->Edgelist[i] = new EdgeList;
				this->Edgelist[i] = this->Edgelist[i]->Create(vertex);
			}
			cout<<"请输入边："<<endl;
			//依次构造无向图的边 
			for(int i = 0 ; i < this->Ne ; i++){
				int start,end;
				cin>>start>>end;
				//找到一条边的两个顶点 
				EdgeList* s1 = this->Find(start);		
				EdgeList* s2 = this->Find(end);
				s1->Attach(s1,end);
				s2->Attach(s2,start);
			} 
		}
		
		//按指定结点查找
		EdgeList* Find(int vertex){
			for(int i = 0 ; i < this->Nv ; i++){
				if(this->Edgelist[i]->getVertex(this->Edgelist[i]) == vertex){
					return this->Edgelist[i];
				}
			} 
		}
		
		//打印邻接表函数 
		void Print(){
			for(int i = 0 ; i < this->Nv ; i++){
				EdgeList* list = this->Edgelist[i];
				list->Print(list);
				cout<<endl;
			}
		}
		
		//广度优先遍历(BFS)
		void BFS(int vertex){
			EdgeList* cur = this->Find(vertex);		//找到当前结点 	
			queue<int> queue;					//初始化队列 
			queue.push(cur->getVertex(cur));			//当前结点入队
			while(!queue.empty()){
				int index = queue.front();		//队头元素出队
				queue.pop();
				isvisited[index] = 1;				//标记为已访问 
				cout<<index<<" ";
				cur = this->Find(index);
				while(cur){		//与当前结点相邻且未被访问的结点入队 
					index = cur->getVertex(cur);
					if(isvisited[index] == 0){
						queue.push(index);
					}
					cur = cur->getNext();	
				} 
			}
		}
		
		//重置访问数组 
		void reset(){
			memset(this->isvisited,0,sizeof(this->isvisited[0])*(this->Nv+1));
		} 
		
		//递归深度优先遍历(DFS)
		void DFS1(int vertex){
			vector<int> node;
			//找到当前结点 
			EdgeList* cur = this->Find(vertex);
			while(cur){		//寻找当前结点的邻接点 
				node.push_back(cur->getVertex(cur));
				cur = cur->getNext();
			}
			//打印当前结点 
			cur = this->Find(node[0]);
			int index = cur->getVertex(cur);
			this->isvisited[index] = 1;
			cout<<index<<" ";
			//一次堆当前结点的邻接点进行DFS 
			for(int i = 1 ; i < node.size() ; i++){
				cur = this->Find(node[i]);
				index = cur->getVertex(cur);
				if(this->isvisited[index] == 0){
					this->isvisited[index] = 1;
					this->DFS1(index);
				}
			}
			this->isvisited[index] = 0;	
		}
		
		//非递归深度优先遍历(DFS)
		void DFS2(int vertex){
			stack<int> stack;
			EdgeList* cur = this->Find(vertex);		//查找当前元素 
			int index = cur->getVertex(cur);		//当前元素的顶点 
			stack.push(index);						//顶点入栈 
			this->isvisited[index] = 1;				//标记为已访问 
			while(!stack.empty()){			//栈不空一直循环 
				index = stack.top();		//栈顶的顶点出栈 
				stack.pop();
				cout<<index<<" ";			//打印当前顶点 
				cur = this->Find(index); 
				while(cur){			//把当前顶点的邻接点依次入栈 
					index = cur->getVertex(cur);
					if(this->isvisited[index] == 0){
						stack.push(index);
						this->isvisited[index] = 1;
					}
					cur = cur->getNext();
				}
			}
		} 
};

int main()
{
	cout<<"请输入顶点数与边数:"<<endl;
	int nv,ne;
	cin>>nv>>ne;
	Graph graph(nv,ne);
	cout<<"邻接表为："<<endl;
	graph.Print();

	
	cout<<"请输入结点:"<<endl;
	int vertex;
	cin>>vertex; 
	
	cout<<"广度优先遍历（BFS）序列为："<<endl;
	graph.BFS(vertex);
	cout<<endl;
	
	cout<<"递归深度优先遍历（DFS）序列为："<<endl;
	graph.reset(); 
	graph.DFS1(vertex);
	cout<<endl; 

	cout<<"非递归深度优先遍历（DFS）序列为："<<endl;
	graph.reset(); 
	graph.DFS2(vertex);
	cout<<endl; 
	
	return 0;
}
