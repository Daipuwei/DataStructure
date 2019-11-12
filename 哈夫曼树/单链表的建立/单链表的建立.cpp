#include <iostream>
using namespace std;

typedef struct Code* code;
struct Code
{
	int data;
	code next;
};

class List
{
	private:
		Code list;
	public:
		code Create_List();									//创建单链表 
		code Insert_List(code ptrl);						//在第index个位置后插入元素 
		void Print_List(code ptrl);							//打印单链表 
		code Delete_List(code ptrl);						//删除第index个位置上的元素 
		int List_length(code ptrl);							//求单链表的长度 
};

code List::Create_List()
{
	int N;
	cout<<"请输入单链表的初始节点数:";
	cin>>N;
	cout<<"请输入数据:\n";
	code head,prev,curren,tmp;
	head = new struct Code;
	head->next = NULL;				//封口 
	prev = head;					//*prev指向头结点 
	while(N--)
	{
		curren = new struct Code;
		cin>>curren->data;
		curren->next = NULL;		//*curren结点封口 
		//尾插法 原节点尾部插入curren结点 
		prev->next = curren;
		prev = curren; 
	 } 
	 prev = head->next;
	 
	 return prev;
}

code List::Insert_List(code ptrl)
{
	int list_length = List_length(ptrl);
	cout<<"请输入插入的数据的位置:";
	int index;
	cin>>index;
	cout<<"单链表长度为:"<<list_length<<endl;
	cout<<"请输入插入的数据:";
	int n;
	cin>>n; 
	int i;
	code p,s,ptrl0;
	ptrl0 = ptrl;
	if ( index == 0 )
	{
		p = new struct Code;
		p->data = n;
		s = p;
		p->next = ptrl;
		ptrl = s;
		ptrl0 = ptrl;
	}
	else
	{
		if ( index<= list_length )
		{
			for ( i = 1 ; i < index ; i++ )
			{
				ptrl = ptrl->next;
			 } 
			 p->data = n;
			 p->next = ptrl->next;
			 ptrl->next = p;
		}
		else
		{
			cout<<"这个位置不是表尾的后一个位置,此次只能插入到表尾后面\n";
			for ( i = 1 ; i < list_length ; i++ )
			{
				ptrl = ptrl->next;
			}
			p->data = n;
			p->next = ptrl->next;
			ptrl->next = p;
		}
	}
	return ptrl0;
}

int List::List_length(code ptrl)
{
	int count = 0;
	code p;
	for ( p = ptrl ; p!=NULL; p = p->next)
			count++;
	return count;
}

code List::Delete_List(code ptrl)
{
	int index;
	cout<<"请输入想删除元素的位置:";
	cin>>index;
	int list_length = List_length(ptrl);
	int i;
	code tmp,ptrl0;
	ptrl0 = ptrl;
	cout<<"单链表长度为:"<<list_length<<endl;
	if ( index > list_length )
	{
		cout<<"这个位置不合法！"<<endl;
	}
	else
	{
		if ( index == 1 )
		{
			tmp = ptrl;
			ptrl = ptrl->next;
			ptrl0 = ptrl;
			delete tmp;
		}
		else
		{
			for ( i = 1 ; i < index-1 ;i++ )
			{
				ptrl = ptrl->next;
			 } 
			tmp = ptrl->next;
			ptrl->next = (ptrl->next)->next;
			delete tmp;
		}
	}
	return ptrl0;
 } 

void List::Print_List(code ptrl)
{
	code p;
	cout<<"输出单链表:\n";
	for( p = ptrl;p!=NULL;p = p->next)
		cout<<p->data<<endl;
}

int main()
{
	List list;
	code ptrl;
	//初始化单链表 
	ptrl = list.Create_List();
	list.Print_List(ptrl);
	
	//在第n个位置之后插入数据 
	ptrl=list.Insert_List(ptrl);
	list.Print_List(ptrl);
	
	//删除第n个位置上的元素
	ptrl=list.Delete_List(ptrl);
	list.Print_List(ptrl);
	
	return 0;
 } 
