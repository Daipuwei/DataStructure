#include <iostream>
#include <string.h>
using namespace std;

class UF{
	private:
		int* array;
		//并查集中的联通分量的个数,初始化为数组大小 
		int count;
	public:
		//构造函数 
		UF(int size){
			this->count = size;
			array = new int[size];
			for(int i = 0 ; i < size ; i++){
				this->array[i] = -1;
			}
		}
		
		//查找操作，路径压缩
		int Find(int x){
			if(this->array[x] < 0){
				return x;
			}else{
				//首先查找x的父节点array[x]，然后把根节点变成array[x],之后再返回根 
				return this->array[x] = Find(this->array[x]);
			}
		}
		
		//并操作,跟结点存储集合元素个数的负数
		//通过对根结点的比较 
		void Uion(int root1, int root2){
			root1 = this->Find(root1);
			root2 = this->Find(root2);
			if(root1 == root2){
				return;
			}else if(this->array[root1] < this->array[root2]){
				//root1所代表的集合的个数大于root2所代表集合的个数
				//因为为存放的是元素个数的负数 
				this->array[root1] += this->array[root2];
				this->array[root2] = root1;
				count--;
			}else{
				this->array[root2] += this->array[root1];
				this->array[root1] = root2;
				count--;
			}
		}
		
		//判断两个集合是否属于一个集合 
		bool check(int root1,int root2){
			root1 = this->Find(root1);
			root2 = this->Find(root2);
			return root1 == root2;
		}
		
		//放回连通分量个数 
		int getCount(){
			return this->count;
		}
};

int main()
{
	int size;
	cin>>size;
	UF uf(size);
	while(1){
		char ch;
		cin>>ch;
		if(ch == 'S'){
			break;
		}else{
			int root1,root2;
			cin>>root1>>root2;
			switch(ch){
				case 'I':
					uf.Uion(root1,root2);
					break;
				case 'C':
					if(uf.check(root1,root2)){
						cout<<"yes"<<endl;
					}else{
						cout<<"no"<<endl;
					}
					break;
			}
		}
	}
	int count = uf.getCount();
	if(count > 1){
		cout<<"There are "<<count<<" components.";
	}else{
		cout<<"The network is connected."; 
	}
	
	return 0;
}
