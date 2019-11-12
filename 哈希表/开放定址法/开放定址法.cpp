#include <iostream>
#include <cmath> 
#include <cstring> 
using namespace std;

const int MAX = 65535;

class HashTable{
	private:
		int length;		//哈希表表长 
		int size;		//哈希表中已经填入的元素 
		int* data;		//元素表
		int Max_Prime;	//最大素数 
		int* delete_flag;	//删除标志 
	public:
		//构造函数
		HashTable(int length){
			this->length = length;
			this->data = new int[this->length];
			this->Max_Prime = this->getMaxPrime(); 
			this->delete_flag = new int[this->length];
			memset(this->delete_flag,0,sizeof(this->delete_flag[0])*this->length);
			for(int i = 0 ; i < this->length ; i++){
				//初始化最大值，表示未插入 
				this->data[i] = MAX;		 
			}
		}
		
		//判断素数函数 
		bool isPrime(int num){
			bool flag = true;
			if(num <= 1){
				flag = false;
			}else if( num == 2){
				flag = true;
			}else{
				for(int i = 2 ; i < num-1 ; i++){
					//num能被i整除 
					if(num % i == 0){
						flag = false;
						break; 
					}
				}
			}
			return flag;
		}
		
		//寻求小于表长的最大素数
		int getMaxPrime(){
			for(int i = this->length-1 ; i >= 0 ; i--){
				if(this->isPrime(i)){
					return i;
				}
			}
		}
		
		//hash函数
		int hash(int num){
			return num%this->Max_Prime;
		}
		
		//插入函数,利用线性探测法 
		bool Insert_Linear_Probing(int num){
			//哈希表已经被装满，则不在填入 
			if(this->size == this->length){
				return false;
			}
			int index = this->hash(num);
			if(this->data[index] == MAX){
				this->data[index] = num;
			}else{
				int i = 1;
				//寻找合适位置 
				while(this->data[(index+i)%this->length] != MAX){
					i++;
				}
				index = (index+i)%this->length; 
				this->data[index] = num;
			}
			if(this->delete_flag[index] == 1){//之前设置为删除 
				this->delete_flag[index] = 0; 
			}
			this->size++;
			return true;
		}
		
		//建表函数
		void Create_Linear_Probing(int* num , int size){
			for(int i = 0 ; i < size ; i++){
				this->Insert_Linear_Probing(num[i]);
			}
		}
		
		//查找函数 
		int Find_Linear_Probing(int num){
			int flag = -1;
			int index = this->hash(num);
			if(this->data[index] == num && this->delete_flag[index] == 0){
				flag = index;
			}else{
				int i = 1;
				while(1){
					if(this->delete_flag[index+i] == 0){//未设置为已删除 
						if(this->data[index+i] != num){
							//不等于无穷大,也不等于num,则偏移量加1 
							i++;
						}else{//等于num时 
							flag = index+i;
							break;
						}	
					}else{//设置为已删除 
						i++;
					} 
				}
			}
			return flag; 
		}
		
		//线性探测的删除函数
		bool Delete_Linear_Probing(int num){
			int index = this->Find_Linear_Probing(num);
			if(index == -1){
				return false;
			}else{
				this->delete_flag[index] = 1;//设置为已删除 
				this->size--; 
				return true; 
			}
		}
		
		void Print(){
			cout<<"下标\t";
			for(int i = 0 ; i < this->length ; i++){
				printf("%7d ",i);
			}
			cout<<endl<<"元素\t";
			for(int i = 0 ; i < this->length ; i++){
				if(this->delete_flag[i] == 0){
					printf("%7d ",this->data[i]);	
				}else{
					printf("%7d ",MAX);
				}
			}
			cout<<endl;
		}
}; 

int main()
{
	cout<<"请输入哈希表的表长："<<endl;
	int length,size;
	int* data;
	cin>>length;
	cout<<"请输入数组长度："<<endl;
	cin>>size; 
	data = new int[size];
	cout<<"请初始化数组："<<endl;
	for(int i = 0 ; i < size ; i++){
		cin>>data[i];
	}
	
	HashTable hashtable(length);
	hashtable.Create_Linear_Probing(data,size);
	cout<<"哈希表为："<<endl;
	hashtable.Print();
	
	int num;
	cout<<"请输入删除的元素："<<endl;
	cin>>num;
	cout<<"删除前哈希表为："<<endl; 
	hashtable.Print();
	if(hashtable.Delete_Linear_Probing(num)){
		cout<<"删除后哈希表为："<<endl;
		hashtable.Print();	
	}else{
		cout<<"哈希表没有"<<num<<"这个元素"<<endl; 
	}
	
	cout<<"请输入插入的元素："<<endl;
	cin>>num;
	cout<<"插入前哈希表为："<<endl; 
	hashtable.Print();
	if(hashtable.Insert_Linear_Probing(num)){
		cout<<"插入后哈希表为："<<endl;
		hashtable.Print();	
	}else{
		cout<<"哈希表已满，无法插入"<<num<<"这个元素"<<endl; 
	}
	
	return 0;
 } 
