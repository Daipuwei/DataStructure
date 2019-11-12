#include <iostream>
#include <time.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;

class MySort{
	private:
		int MAX;
		int* A;
	public:
		//构造函数 
		MySort(int N){
			this->MAX = N;
			A = new int[this->MAX];
			this->SetArray();
		}
		
		//随机初始化数组 
		void SetArray(){
			srand(time(0));
			for ( int i = 0 ; i < MAX ; i++){
				A[i] = rand() % 100 + 1; 
			}
		}
		
		//打印数组 
		void Print(){
			int count = 0;
			for ( int i = 0 ; i < MAX ; i++){
				cout<<A[i]<<" ";
				count++;
				if ( count == 10 ){
					cout<<endl;
				}
			}
		}
		
		//交换函数 
		void Swap(int* a , int* b){
			int tmp = *a;
			*a = *b;
			*b = tmp;
		}
		
		//冒泡排序 
		void Bubble_Sort(){
			int count = 0;
			for ( int i = this->MAX - 1 ; i >= 0 ; i--){
				int flag = 0;
				for ( int j = 0 ; j < i ; j++){
					if ( A[j] > A[j+1]){
						this->Swap(&A[j],&A[j+1]);
						count++;
						flag = 1;
					}
				}
				if ( flag == 0){
					break;
				}
			}	
		}
		
		//插入排序 
		void  Insertion_Sort(){
			for ( int i = 1 ; i < this->MAX ; i++){
				int tmp = A[i];
				for ( int j = i ; j > 0 && A[j-1] > tmp ; j-- ){
					A[j] = A[i-1];
				}
				A[i] = tmp;
			}
		}
		
		//希尔排序 
		void Shell_Sort(){
			int Sedgewick[] = { 929,505,209,109,41,19,5,1,0};
			int tmp;
			int i,j,k;
			for ( i = 0 ; Sedgewick[i] >= MAX ; i++);
			for ( j = Sedgewick[i] ; j > 0 ; j = Sedgewick[++i]){
				tmp = A[j];
				for ( k = 0 ; k >= j && A[i-j] > tmp ; k -= j){
					A[k] = A[k-j];
				} 
				A[k] = tmp; 
			}
		}
		
		//查找最小值的下标函数 
		int ScanForMin(int start,int end){
			int index = start;
			int min = A[start];
			for ( int i = start ; i < end ; i++){
				if ( A[i] < min){
					min = A[i];
					index = i;
				}
			}
			return index;
		}
		
		//选择排序 
		void Selection_Sort(){
			int MinPosition;
			int i;
			for ( i = 0 ; i < MAX ; i++){
				MinPosition = this->ScanForMin(i,MAX);
				this->Swap(&A[i],&A[MinPosition]);
			}
		}
		
		//一次归并函数 
		void Merge(int* TmpA,int Left,int Right,int RightEnd){
			int LeftEnd = Right -1;
			int Tmp = Left ;
			int Num = RightEnd - Left + 1;
			while ( Left <= LeftEnd && Right <= RightEnd){
				if ( A[Left] <= A[Right]){
					TmpA[Tmp++] = A[Left++];
				}else{
					TmpA[Tmp++] = A[Right++];
				}
			}
			while(Left <= LeftEnd){
				TmpA[Tmp++] = A[Left++];
			}
			while(Right <= RightEnd){
				TmpA[Tmp++] = A[Right++];
			}
			for ( int i = 0 ; i < Num; i++,RightEnd--){
				A[RightEnd] = TmpA[RightEnd];
			}
		}
		
		//递归归并函数 
		void MergeSort(int* TmpA,int Left,int RightEnd){
			int Center;
			if ( Left < RightEnd){
				Center = ( Left + RightEnd) /2;
				MergeSort(TmpA,Left,Center);
				MergeSort(TmpA,Center+1,RightEnd);
				Merge(TmpA,Left,Center+1,RightEnd);
			}
		}
		
		//递归归并排序 
		void Merge_Sort1(){
			int* TmpA;
			TmpA = new int[MAX];
			if ( TmpA != NULL){
				this->MergeSort(TmpA,0,this->MAX-1);
				delete TmpA;
			}else{
				cout<<"空间不足!"<<endl;
			}
		}
		
		//非递归一次归并
		//length为当前有序子列的长度 
		void Merge_pass(int* TmpA ,int length){
			//两两归并相邻有序子列 
			int i , j;
			for ( i = 0 ; i <= this->MAX - 2*length ; i += 2*length){
				this->Merge(TmpA,i,i+length,i+2*length-1);
			} 
			if ( i + length < this->MAX){			//归并最后剩2个子列 
				this->Merge(A,i,i+length,this->MAX-1);
			}else{//最后剩1个子列 
				for ( j = i ; j < this->MAX ; j++){
					TmpA[j] = A[j];
				}
			}
		}
		
		//非递归归并排序 
		void Merge_Sort2(){
			int* TmpA;
			TmpA = new int[this->MAX];
			int length = 1;
			if ( TmpA != NULL){
				while ( length < this->MAX){
					this->Merge_pass(TmpA,length);
					length *= 2;
					this->Merge_pass(A,length);
					length *= 2;
				}
				delete TmpA;
			}else{
				cout<<"空间不足"<<endl; 
			} 
		} 
};

int main()
{
	//初始化数组 
	int N;
	cout<<"请输入数组长度:";
	cin>>N;
	MySort sort(N);
	
	//冒泡排序
	cout<<"冒泡排序前:"<<endl;
	sort.Print();
	sort.Bubble_Sort();
	cout<<"冒泡排序后:"<<endl;
	sort.Print();
	
	//插入排序
	cout<<"插入排序前:"<<endl;
	sort.SetArray();
	sort.Print();
	sort.Insertion_Sort(); 
	cout<<"插入排序后:"<<endl;
	sort.Print();
	
	//希尔排序 
	cout<<"希尔排序前:"<<endl;
	sort.SetArray();
	sort.Print();
	sort.Shell_Sort(); 
	cout<<"希尔排序后:"<<endl;
	sort.Print();
	
	//选择排序 
	cout<<"选择排序前:"<<endl;
	sort.SetArray();
	sort.Print();
	sort.Selection_Sort(); 
	cout<<"选择排序后:"<<endl;
	sort.Print();
	
	//归并排序(递归法) 
	cout<<"归并排序(递归)前:"<<endl;
	sort.SetArray();
	sort.Print();
	sort.Merge_Sort1();
	cout<<"归并排序(递归)后:"<<endl;
	sort.Print();
	
	//归并排序(非递归法) 
	cout<<"归并排序(非递归)前:"<<endl;
	sort.SetArray();
	sort.Print();
	sort.Merge_Sort2();
	cout<<"归并排序(非递归)后:"<<endl;
	sort.Print();
	
	return 0;
 } 
