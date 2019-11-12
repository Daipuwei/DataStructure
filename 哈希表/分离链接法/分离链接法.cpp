#include <iostream>
#include <vector>
using namespace std;

struct node{
	int data;
	struct node* next;	
};

typedef struct node Node;

class HashTable{
	private:
		vector<Node*> nodes;
		int length;
		int Max_Prime;
	public:
		//构造函数
		HashTable(int length){
			this->length = length;
			nodes.reserve(this->length);
			this->Max_Prime = this->getMaxPrime();
			for(int i = 0 ; i < this->length ; i++){
				this->nodes.push_back(this->Create_Node(i));
			}
		}
		
		Node* Create_Node(int num){
			Node* node = new Node;
			node->data = num;
			node->next = NULL;
			return node;
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
			return num % this->Max_Prime;
		}
		
		Node* Attach(Node* node1 ,Node* node2){
			Node* cur = node1;
			while(1){
				if(cur->next == NULL){
					cur->next = node2;
					break;
				}
				cur = cur->next;
			}
			return node1;
		}
		
		//插入函数 
		void Insert(int num){
			//计算结点所在的地址 
			int index = this->hash(num);
			//建立结点 
			Node* node = NULL;
			node = this->Create_Node(num); 
			//把结点连接到合适的地址结点上 
			Node* tmp = NULL;
			tmp = this->nodes[index];
			this->nodes[index] = this->Attach(tmp,node);
		} 
		
		//建表函数
		void Create(int size,int* num){
			for(int i = 0 ; i < size ; i++){
				//插入结点
				this->Insert(num[i]);
			}
		}
		
		//删除结点
		bool Delete(int num){
			int index = this->hash(num);
			Node* cur = this->nodes[index];
			while(cur->next->data != num){
				cur = cur->next;
			}
			if(cur == NULL){//在哈希表中未找到num 
				return false;
			}
			Node* tmp = cur->next;
			cur->next = cur->next->next;
			delete tmp;
			return true; 
		}
		
		void Print_List(Node* node){
			Node* cur = node;
			while(cur){
				cout<<cur->data<<" ";
				cur = cur->next; 
			}
		}
		
		//查找函数 
		int Find(int num){
			int index = this->hash(num);
			Node* cur = this->nodes[index];
			while(cur->data != num){
				cur = cur->next;
			}
			if(cur == NULL){//哈希表中没有num 
				index = -1;
			}
			return index;
		}
		
		//打印函数
		void Print(){
			cout<<"下标\t元素："<<endl;
			for(int i = 0 ; i < this->nodes.size() ; i++){
				if(this->nodes[i]->next != NULL){
					cout<<i<<":\t";
					this->Print_List(this->nodes[i]->next);
					cout<<endl; 
				}
			}
		} 
};

int main()
{
	cout<<"请输入哈希表长度："<<endl;
	int length;
	cin>>length;
	cout<<"请输入需要插入的元素个数："<<endl;
	int size;
	int* data;
	cin>>size;
	data = new int[size];
	cout<<"请初始化元素："<<endl;
	for(int i = 0 ; i < size ; i++){
		cin>>data[i];
	}
	
	HashTable hashtable(length); 
	hashtable.Create(size,data);
	cout<<"哈希表为："<<endl;
	hashtable.Print();
	
	int num,index;
	cout<<"请输入要寻找的元素："<<endl;
	cin>>num;
	index = hashtable.Find(num);
	if(index == -1){
		cout<<"哈希表中没有"<<num<<"这个元素"<<endl; 
	}else{
		cout<<num<<"在地址为"<<index<<"所指向的链表里"<<endl; 
	}
	
	cout<<"请输入要插入的元素："<<endl;
	cin>>num;
	cout<<"插入前哈希表为："<<endl;
	hashtable.Print(); 
	cout<<"插入后哈希表为："<<endl;
	hashtable.Insert(num);
	hashtable.Print();
	 
	cout<<"请输入要删除的元素："<<endl;
	cin>>num;
	cout<<"删除前哈希表为："<<endl;
	hashtable.Print(); 
	cout<<"删除后哈希表为："<<endl;
	hashtable.Delete(num);
	hashtable.Print();
	
	return 0;
 } 
