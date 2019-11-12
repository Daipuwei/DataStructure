#include <iostream>
using namespace std;

//作为最大堆的第0个元素，以之为哨兵 
const int MaxData = 1000000;

class MaxHeap{
	private:
		int* data;			//存储数据的数组 
		int size;			//当前规模 
		int capacity;		//最大容量
	public:
		//最大堆的构造函数 
		MaxHeap(int MaxSize){
			this->data = new int[MaxSize];
			this->size = 0;
			this->capacity = MaxSize;
			this->data[0] = MaxData;
		}
		
		//把data[n]为根的子堆调整为最大堆
		void Predown(int n){
			//保存下标为n的元素
			int x = this->data[n];
			int parent,child;
			//用最后一个元素来替代第一个最大值 
			for(parent = n ; parent*2 <= this->size ; parent = child){
				//child指向当前结点的左孩子 
				child = parent*2;
				//左孩子的下标不等于最大堆容量，则说明有右孩子
				//右孩子的键值如果父节点，那么child指向右孩子，否则仍指向左孩子 
				if((child != this->size) && this->data[child] < this->data[child+1]){
					child++;//选择左右孩子中最大值 
				}
				if(x >= this->data[child]){//找到了合适的位置 
					break;
				}else{//把孩子上移
					this->data[parent] = this->data[child];
				}
			}
			this->data[parent] = x; 
		}
		
		//最大堆的建立函数 
		void Create(int* data ,int n){
			//把数据导入最大堆 
			for(int i = 0 ; i < n ; i++){
				this->data[++size] = data[i];
			}
			//从最后一个结点的父节点开始逐步之为根结点的子堆调整为最大堆 
			for(int i = this->size/2 ; i > 0 ; i--){
				this->Predown(i); 
			}
		} 
		
		//判断最大堆是否已满
		bool IsFull(){
			return this->size == this->capacity;
		} 
		
		bool IsEmpty(){
			return this->size == 0;
		}
		
		//最大堆的插入操作 
		bool Insert(int num){
			//最大堆已满则无法插入 
			if(this->IsFull()){
				return false;
			}
			//保存最后一个元素的位置
			int i = ++size; 
			//从最后一个元素的父节点开始进行过滤
			//如果父节点小于num，那么把父节点下移 
			//data[0]控制哨兵元素，它不小于最大堆中最大元素，控制循环结束 
			for(; this->data[i/2] < num ; i /= 2){
				this->data[i] = this->data[i/2];
			}
			this->data[i] = num;
			return true;
		}
		
		//最大堆的删除最大值操作
		int DeleteMax(){
			//最大堆是空时 
			if(this->IsEmpty()){
				return MaxData;
			} 
			int max = this->data[1];
			this->data[1] = this->data[size];
			//最大堆规模减一 
			this->size--;
			//然后把第一个元素为根结点进行调整为最大堆 
			this->Predown(1);
			return max; 
		}
		
		//打印最大堆
		void Print(){
			for(int i = 1 ; i <= this->size ; i++){
				cout<<this->data[i]<<" ";
			}
		} 
};

int main()
{
	cout<<"请输入最大堆的最大容量："<<endl;
	int capacity;
	cin>>capacity;
	MaxHeap maxheap(capacity); 
	cout<<"请输入初始化最大堆的元素个数:"<<endl;
	int size,*data;
	cin>>size;
	data = new int[size];
	cout<<"请初始化元素:"<<endl;
	for(int i = 0 ; i < size ; i++){
		cin>>data[i];
	}
	maxheap.Create(data,size);
	cout<<"最大堆为:"<<endl;
	maxheap.Print();
	cout<<endl;
	
	//在最大堆中插入元素
	cout<<"请输入要插入的元素："<<endl;
	int num;
	cin>>num;
	maxheap.Insert(num);
	cout<<"最大堆为:"<<endl;
	maxheap.Print(); 
	cout<<endl;
	
	cout<<"进行删除操作"<<endl;
	int x = maxheap.DeleteMax();
	cout<<"删除元素为："<<x<<endl;
	cout<<"最大堆为:"<<endl;
	maxheap.Print();
	
	return 0;
 } 
