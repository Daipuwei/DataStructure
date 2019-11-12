#include <iostream>
using namespace std;

//带头结点的单链表类，头结点存放单链表长度 
class Single_List{
	private:
		int data;
		Single_List* next;
	public:	
		//单链表的创建函数，尾插法 
		Single_List* Create(int len){
			Single_List* prev,*head,*tail;
			head = new Single_List;
			head->data = len;
			head->next = NULL;
			prev = head;
			if(len == 0){
				goto end;
			}
			cout<<"请输入各个结点的数值："<<endl; 
			while(len--){
				int data;
				tail = new Single_List;
				cin>>data;
				this->attach(prev,tail,data); 
				prev = tail;
			}
			end:	return head;
		}
		
		void attach(Single_List* prev,Single_List* tail,int data){
			tail->next = NULL;
			tail->data = data;
			prev->next = tail;
		}
		
		int getLength(Single_List* list){
			return list->data;
		}
		
		//判断单链表是否为空的函数 
		bool Isempty(Single_List* list){
			return list->data == 0;
		}
		
		//单链表的打印函数
		void Print(Single_List* list){
			if(list->Isempty(list)){
				cout<<"单链表为空"<<endl;
				return;
			}
			Single_List* pre;
			pre = list->next;
			while(pre){
				cout<<pre->data<<" ";
				pre = pre->next;
			}
		}
		
		//在第index个结点后面插入数值为data的结点的函数 
		Single_List* Insert(Single_List* list,int index ,int data){
			Single_List* prev = list;
			Single_List* insert;
			insert = new Single_List;
			int len = list->getLength(list);
			//链表为空时,无论index为多少，只能插在第一个位置 
			if(this->Isempty(list)){
				this->attach(prev,insert,data);
				list->data++;
				return list;
			}
			//如果插入的位置大于等于链表长度直接插到末尾， 
			index = (list->data <= index)?list->data:index;
			for(int i = 0 ; i < index ; i++){
				prev = prev->next;
			}
			insert->data = data;
			insert->next = prev->next;
			prev->next = insert;
			list->data++;
			return list;
		}
		
		//寻找第k个结点的函数,只适用链表不为空的情况 
		Single_List* Findkth(Single_List* list ,int k){
			Single_List* prev;
			prev = list;
			for(int i = 0 ; i < k ; i++){
				prev = prev->next;
			} 
			return prev;
		}
		
		//寻找数值为N的结点的函数
		int FindN(Single_List* list,int N){
			int result = -1;
			Single_List* prev;
			prev = list;
			int len = this->getLength(list); 
			for(int i = 0 ; i < len ; i++){
				prev = prev->next;
				if(prev->data == N){
					result = i;
					break;
				}
			}
			return result; 
		}
		
		//删除数值为N的结点的函数 
		void DeleteN(Single_List* list,int N){
			int index = this->FindN(list,N);
			//不存在数值为N的情况 
			if(index == -1){
				cout<<"单链表不存在数值为"<<N<<"的结点"<<endl;
				return;
			}
			this->Deletekth(list,index+1);
		}
		
		//删除第k个结点的函数
		void Deletekth(Single_List* list,int k){
			int len = list->data;
			if(this->Isempty(list)){
				cout<<"单链表为空无法删除"<<endl;
				return; 
			}
			Single_List* del_pre;
			del_pre = this->Findkth(list,k-1);
			del_pre->next = del_pre->next->next;
			list->data--;
		}
		
		//逆转链表函数
		Single_List* Reverse(Single_List* list){
			//单链表为空时 
			if(this->Isempty(list)){
				return list;
			}
			Single_List* head,*front,*rear,*tag;
			head = list;				//保存头结点 
			//front，rear用于逆转，tag用于记录未逆转的链表 
			front = list->next;			
			rear = front->next;
			front->next = NULL;
			while(rear){
				tag = rear->next;
				rear->next = front;
				front = rear;
				rear = tag;
			}
			head->next = front;
			return head;
		}
		
		//对两个升序链表进行升序合并函数 
		Single_List* Merge(Single_List* list1,Single_List* list2){
			if(list1 == NULL){
				return list1;
			}
			if(list2 == NULL){
				return list2;
			}
			Single_List* list;			//建立合并链表的头结点，存放两个链表长度之和 
			list = new Single_List;
			list->data = list1->data+list2->data;
			list->next = NULL;
			Single_List* prev1,*prev2,*tail,*head,*tag;
			prev1 = list1->next;		//指向list32的第一个结点（不是存放长度的头结点，即头结点之后的结点）
			prev2 = list2->next;
			head = new Single_List;		//建立新链表的空头结点 
			tag = head;					//保存空头结点的地址 
			head->next = NULL;			 
			while(prev1 && prev2){
				tail = new Single_List;
				if(prev1->data <= prev2->data){
					this->attach(head,tail,prev1->data);
					head = tail;
					prev1 = prev1->next;
				}else{
					this->attach(head,tail,prev2->data);
					head = tail;
					prev2 = prev2->next;
				}
			}
			if(prev1){
				head->next = prev1;
			}
			if(prev2){
				head->next = prev2;
			}
			list->next = tag->next;
			return list;					
		}
		
		//链表排序，冒泡排序
		Single_List* Sort(Single_List* list){
			Single_List* head,*prev1,*prev2;
			head = list;
			prev1 = list->next;
			while(prev1){
				prev2 = prev1->next;
				while(prev2){
					if(prev1->data > prev2->data){
						prev1->data += prev2->data;
						prev2->data = prev1->data - prev2->data;
						prev1->data -= prev2->data;
					}	
					prev2 = prev2->next;
				}
				prev1 = prev1->next;
			}
			return head;
		}
		
		//删除所有值为x的结点 
		Single_List* Delete_X(Single_List* list ,int data){
			Single_List* head,*front;
			front = list;
			while(front->next != NULL){
				/*cout<<"删除前："<<endl;
				this->Print(list);
				cout<<endl;*/
				if(front->next->data == data){
					front->next = front->next->next;
					list->data--;
				}else{
					front = front->next;
				}
				/*cout<<"删除后："<<endl;
				this->Print(list);
				cout<<endl;*/ 
			}
			return list;
		}
		
		//删除最小值结点 
		Single_List* Delete_min(Single_List* list){
			Single_List* front,*tmp;
			int min = list->next->data;
			tmp = list;
			front = list->next;
			while(front->next != NULL){
				/*cout<<"删除前："<<endl;
				this->Print(list);
				cout<<endl;*/
				if(front->next->data < min){
					min = front->next->data;
					tmp = front; 
				}
				front = front->next;
				/*cout<<"删除后："<<endl;
				this->Print(list);
				cout<<endl;*/ 
			}
			front = tmp->next;
			tmp->next = front->next;
			list->data--;
			delete front;
			return list;
		}
		
		//删除值在strat与end之间的结点
		Single_List* Delete_between(Single_List* list,int start ,int end){
			if(start > end){
				return list;
			}
			if(list->next == NULL){
				return list;
			}
			Single_List* front;
			front = list;
			while(front->next != NULL){
				if(front->next->data >= start && front->next->data <= end){
					Single_List* tmp;
					tmp = front->next;
					front->next = tmp->next;
					delete tmp;
					continue;		
				}else{
					front = front->next;
				} 
			}
			return list;
		}
		
		//递增打印所有结点
		void Print_increase(Single_List* list){
			Single_List* pre,*rear,*tmp;
			pre = list;
			while(pre->next != NULL){
				Single_List* min;
				min = pre;
				rear = pre->next;
				while(rear->next != NULL){
					if(rear->next->data < min->next->data){
						min = rear;
					}
					rear = rear->next;
				}
				tmp = min->next;
				//cout<<"fdsxc:"<<min->data<<endl; 
				cout<<tmp->data<<" ";
				min->next = tmp->next;
				delete tmp;
			}
		}
		
		//A存奇数结点，B存偶数结点
		Single_List* Create_2(Single_List* A,Single_List* B){
			int cnt = 0;
			B = new Single_List;
			B->next = NULL;
			Single_List* pre,*even,*odd;
			pre = A->next;
			even = B;
			odd = A;
			A->next = NULL; 
			
			while(pre != NULL){
				cnt++;
				if(cnt % 2 == 0){
					//cout<<"dsah:"<<pre->data<<endl;
					even->next = pre;
					even = even->next;
				}else{
					//cout<<"gfdbghfn:"<<pre->data<<endl;
					odd->next = pre;
					odd = odd->next;
				}
				pre = pre->next;
			}
			even->next = NULL;
			odd->next = NULL;
			return B; 
		} 
};

int main()
{
	cout<<"请输入初始化单链表的长度:"<<endl;
	int len;
	Single_List tmp; 
	Single_List* list1,*list2,*list;
	cin>>len;
	list1 = tmp.Create(len);
	cout<<"单链表如下："<<endl; 
	tmp.Print(list1);
	cout<<endl;
	cin>>len;
	list2 = tmp.Create(len);
	cout<<"单链表如下："<<endl; 
	tmp.Print(list2);
	cout<<endl;
	list = tmp.Merge(list1,list2);
	tmp.Print(list);
	cout<<endl;
	list = tmp.Reverse(list);
	tmp.Print(list );
	cout<<endl;
	
	/*cout<<"排序后为:"<<endl;
	list = tmp.Sort(list);
	tmp.Print(list);
	cout<<endl;*/
	
	/*list = tmp.Delete_min(list);
	tmp.Print(list);*/
	/*list = tmp.Delete_between(list,5,8);
	tmp.Print(list);*/
	
	/* 
	cout<<"请输入初始化单链表的长度:"<<endl;
	Single_List* list1;
	cin>>len;
	list1 = tmp.Create(len);
	cout<<"第二个单链表如下："<<endl; 
	tmp.Print(list1);
	cout<<endl;
	cout<<"排序后为:"<<endl;
	list1 = tmp.Sort(list1);
	tmp.Print(list1);
	cout<<endl;
	
	cout<<"合并后链表为:"<<endl;
	Single_List* merge_list = tmp.Merge(list,list1);
	tmp.Print(merge_list);
	cout<<endl;
	
	cout<<"请输入插入结点的位置："<<endl;
	int index,data;
	cin>>index;
	cout<<"插入前单链表如下："<<endl; 
	tmp.Print(list);
	cout<<endl<<"请输入插入结点的数值："<<endl;
	cin>>data;
	list = tmp.Insert(list,index,data);
	cout<<"插入后单链表如下："<<endl; 
	tmp.Print(list);
	cout<<endl;
	
	
	cout<<"请输入删除结点的位置："<<endl;
	cin>>index;
	cout<<"删除前单链表如下："<<endl; 
	tmp.Print(list);
	tmp.Deletekth(list,index);
	cout<<endl<<"删除后单链表如下："<<endl; 
	tmp.Print(list);
	cout<<endl;
	
	cout<<"请输入删除结点的数值："<<endl;
	cin>>data;
	cout<<"删除前单链表如下："<<endl; 
	tmp.Print(list);
	tmp.DeleteN(list,data);
	cout<<endl<<"删除后单链表如下："<<endl; 
	tmp.Print(list);
	cout<<endl;

	cout<<"逆转单链表前,单链表如下："<<endl;
	tmp.Print(list);
	cout<<endl<<"逆转单链表后,单链表如下："<<endl;
	list = tmp.Reverse(list); 
	tmp.Print(list); */
	
	return 0;
 } 
