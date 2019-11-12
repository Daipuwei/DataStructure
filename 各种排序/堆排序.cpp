#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

const int MAX = 65535;

class HeapSort{
	private:
		int* data;
		int size;
	public:
		//构造函数
		HeapSort(int* data,int len){
			this->size = 0;
			this->data = new int[len+1];
			this->data[0] = MAX;
			for(int i = 0 ; i < len ; i++){
				this->data[++this->size] = data[i];
			}
			this->BuildHeap();
		}
		
		//把下标为n的子树调整为最大堆
		void Predown(int start ,int end){
			int parent ,child;
			int x = this->data[start];
			for(parent = start ; 2*parent < end ; parent = child){
				child = parent*2;
				//child+1不是最后一个元素，且右孩子大于左孩子 
				if(child+1 != this->size && this->data[child+1] > this->data[child]){
					child++; 
				}
				if(x >= this->data[child]){
					break;
				}else{
					this->data[parent] = this->data[child];
				} 
			}
			this->data[parent] = x;
		} 
		
		//建堆函数
		void BuildHeap(){
			for(int i = this->size/2 ; i >= 0 ; i--){
				this->Predown(i,this->size);
			}
		}
		
		void Swap(int* a,int* b){
			*a = *a + *b;
			*b = *a - *b;
			*a = *a - *b; 
		} 
		
		//堆排序
		void Heap_Sort(){
			for(int i = this->size ; i > 0 ; i--){
				//交换最后一个与第0个元素 
				this->Swap(&this->data[0],&this->data[i]);
				//把0到i-1个数调整为最大堆 
				this->Predown(0,i-1);
			}
		}
		
		void Print(int start , int end){
			for(int i = start ; i <= end; i++){
				cout<<this->data[i]<<" ";
			}
			cout<<endl;
		} 
};

int main()
{
	cout<<"请输入数组长度:"<<endl;
	int size,*data;
	cin>>size;
	data = new int[size]; 
	srand(time(0));
	cout<<"随机初始化"<<size<<"个数"<<endl;
	for(int i = 0 ; i < size ; i++){
		data[i] = rand()%100+1;
	}
	
	HeapSort sort(data,size);
	cout<<"堆排序前："<<endl;
	sort.Print(1,size);
	cout<<"堆排序后："<<endl;
	sort.Heap_Sort();
	sort.Print(0,size-1); 
	
	return 0;
 } 
