#include <iostream>
using namespace std;

class Single_List{
	private:
		int data;
		Single_List* next;
	public:	
		//单链表的创建函数
		Single_List* Create(int len){
			cout<<"请输入要各个结点的数值："<<endl;
			Single_List* prev;
			Single_List* head;
			Single_List* tail;
			head = new Single_List;
			head->data = len;
			head->next = NULL;
			prev = head;
			while(len--){
				tail = new Single_List;
				cin>>tail->data;
				tail->next = NULL;
				prev->next = tail;
				prev = tail;
			}
			return head;
		}
		
		bool Isempty(){
			return this->data == 0;
		}
		
		//单链表的打印函数
		void Print(Single_List* list){
			if(list->Isempty()){
				cout<<"单链表为空"<<endl;
				return;
			}
			int len = list->data;
			Single_List* ptrl = list->next;
			for(int i = 0 ; i < len ; i++){
				cout<<ptrl->data<<" ";	
				ptrl = ptrl->next;
			}
		} 
};

int main()
{
	cout<<"请输入初始化单链表的长度:"<<endl;
	int len;
	Single_List tmp; 
	Single_List* list;
	cin>>len;
	list = tmp.Create(len);
	
	cout<<"单链表如下："<<endl; 
	tmp.Print(list);
	cout<<endl;	
	
	return 0;
 } 
