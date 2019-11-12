#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;
		
//初始化数组 
void SetArray(int* data,int size)
{
	//srand(time(0));
	cout<<"随机初始化"<<size<<"个数"<<endl;
	for(int i = 0 ; i < size ; i++){
		data[i] =rand()%100+1;
	}
}

//打印函数 
void Print(int* data ,int size)
{
	for(int i = 0 ; i < size ; i++){
		cout<<data[i]<<" "; 
	}
	cout<<endl;
}

//交换函数 
void Swap(int& a ,int& b)
{
	int tmp = a;
	a = b;
	b = tmp;
}
		
//冒泡排序
void Bubble_Sort(int* data ,int size)
{
	for(int i = size-1 ; i >= 0 ; i--){
		bool flag = false;		//、是否交换标志 
		for(int j = 0 ; j < i ; j++){
			if(data[j+1] < data[j]){
				Swap(data[j],data[j+1]);	
				flag = true;//发生了交换 
			}
		}
		if(flag == false){//全程无交换 
			break;
		}
	}
}
		
//直接插入排序
void Insertion_Sort(int* data ,int size)
{
	for(int i = 1 ; i < size ; i++){
		int tmp = data[i];
		int j; 
		for(j = i ; j > 0  && data[j-1] > tmp ; j--){
			//前一个数大于后一个树，进行交换 
			data[j] = data[j-1];
		}
		//找到合适位置，进行插入 
		data[j] = tmp;
	}
}


//折半插入排序
void Binary_Insertion_Sort(int* data,int size)
{
	for(int i = 1 ; i < size ; i++){
		int low = 0,high = i-1;//在i之前找到最佳位置 
		int tmp = data[i],mid,j;
		while(low <= high){//寻找最佳位置 
			mid = (low+high)/2;
			if(data[mid] < tmp){
				//大于中间值，到右半部分寻找 
				low = mid+1;
			}else{//小于中间值，到左半部分寻找
				high = mid-1;
			}
		}
		for(j = i ; j > low ; j--){
			data[j] = data[j-1];
		}
		data[j] = tmp;
	}
 } 
		
//希尔排序 
void Shell_Sort(int* data ,int size)
{
	//部分Sedgewick增量序列 
	int Sedgewick[] = {929,505,209,109,41,19,5,1,0};
	int si = 0;
	//寻找合适初始最大间隔 
	for(si = 0 ; Sedgewick[si] >= size ; si++);
	//开始希尔排序 
	for(int D = Sedgewick[si] ; D > 0 ; D = Sedgewick[++si]){
		//里面是一个D间隔的插入排序 
		for(int i = D ; i < size ; i++){
			int j=0;
			int tmp = data[i];
			for(j = i ; j >= D && data[j-D] > tmp ; j-= D){
				data[j] = data[j-D];
			}
			data[j] = tmp;
		}
	}
}
		
//一趟归并 
void Merge(int* data,int* tmp,int left,int right,int rightend)
{
	int leftend = right-1;
	int size = rightend-left+1;
	int cnt = left;
	while(left <= leftend && right <= rightend){
		if(data[left] < data[right]){
			tmp[cnt++] = data[left++];
		}else{
			tmp[cnt++] = data[right++];
		}
	}
	while(left <= leftend){
		tmp[cnt++] = data[left++];
	}
	while(right <= rightend){
		tmp[cnt++] = data[right++];
	}
	for(int i = 0 ; i < size ; i++,rightend--){
		data[rightend] = tmp[rightend]; 
	}
}

//归并排序	
void Msort(int* data,int* tmp,int left,int rightend)
{
	if(left < rightend){
		int mid = (left+rightend)/2;
		Msort(data,tmp,left,mid);//递归归并排序左半部分 
		Msort(data,tmp,mid+1,rightend);//递归归并排序右半部分 
		Merge(data,tmp,left,mid+1,rightend);//对左右部分进行有序归并 
	}
}
		
//归并排序(递归版本)
void Merge_Sort(int* data,int size)
{
	int* tmp = new int[size];
	if(tmp != NULL){
		Msort(data,tmp,0,size-1);
	}
}
		
//一趟归并排序
void Merge_Pass(int* data,int* tmp,int size,int length)
{
	int i;
	for(i = 0 ; i <= size-2*length ; i += 2*length){
		Merge(data,tmp,i,i+length,i+2*length-1);
	}
	if(i+length < size){//归并最后两个子序列 
		Merge(data,tmp,i,i+length,size-1);
	}else{//归并最后一个子序列 
		for(int j = i ; j < size ; j++){
			tmp[j] = data[j];
		}
	}
}
//归并排序(非递归排序)
void Merge_Sort1(int* data,int size)
{
	int* tmp = new int[size];
	int length = 1;
	if(tmp != NULL){
		while(length < size){
			Merge_Pass(data,tmp,size,length);
			length*=2;
			Merge_Pass(tmp,data,size,length);
			length*=2;
		}
		delete tmp;
	}
}

int main()
{
	cout<<"请输入数组长度:"<<endl;
	int size,*data;
	cin>>size;
	data = new int[size];
	
	/*SetArray(data,size);
	cout<<"冒泡排序前："<<endl;
	Print(data,size);
	cout<<"冒泡排序后："<<endl;
	Bubble_Sort(data,size);
	Print(data,size); 
	
	SetArray(data,size); 
	cout<<"直接插入排序前："<<endl;
	Print(data,size);
	cout<<"直接插入排序后："<<endl;
	Insertion_Sort(data,size);
	Print(data,size); 
	
	SetArray(data,size); 
	cout<<"折半插入排序前："<<endl;
	Print(data,size);
	cout<<"折半插入排序后："<<endl;
	Binary_Insertion_Sort(data,size);
	Print(data,size); 
	
	SetArray(data,size); 
	cout<<"希尔排序前："<<endl;
	Print(data,size);
	cout<<"希尔排序后："<<endl;
	Shell_Sort(data,size);
	Print(data,size);*/
	
	SetArray(data,size);
	cout<<"归并排序（递归版本）前："<<endl;
	Print(data,size);
	cout<<"归并排序（递归版本）后："<<endl;
	Merge_Sort(data,size);
	Print(data,size); 
	
	SetArray(data,size);
	cout<<"归并排序（非递归版本）前："<<endl;
	Print(data,size);
	cout<<"归并排序（非递归版本）后："<<endl;
	Merge_Sort1(data,size);
	Print(data,size);
	
	return 0;
 } 	
