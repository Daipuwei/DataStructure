#include <iostream>
#include <stack> 
#include <queue>
#include <vector>
#include <set>
#include <map>
#include <cmath>
using namespace std;

class BinaryTree{
	private:
		char data;
		BinaryTree* lchild;
		BinaryTree* rchild;
	public: 
		//二叉树的初始化函数 
		BinaryTree* Create_BinaryTree(){
			BinaryTree* T = new BinaryTree;
			char ch;
			cin>>ch;
			if(ch == '#'){													//“#”是结束标志 
				T = NULL;
			}else{
				T->data = ch;												//对当前结点初始化 
				T->lchild = Create_BinaryTree();						  	//递归构造左子树 
				T->rchild = Create_BinaryTree();							//递归构造右子树 
			}
			return T;
		}
		
		//递归前序遍历 
		void PreorderTraversal(BinaryTree* T){
			if(T == NULL){
				return;
			}
			cout<<T->data<<" ";												//访问根节点并输出 
			T->PreorderTraversal(T->lchild);								//递归前序遍历左子树 
			T->PreorderTraversal(T->rchild);								//递归前序遍历右子树
		}
		
		//非递归前序遍历 
		void PreorderTraversal2(BinaryTree* T){
			stack<BinaryTree*> stack;										//初始化栈 
			BinaryTree* binary_tree_curr = T;								//保存当前结点 
			//当前结点为空跳出循环 
			while(binary_tree_curr || !stack.empty()){
				cout<<binary_tree_curr->data<<" ";							//打印当前结点 
				stack.push(binary_tree_curr);								//当前结点入栈 
				binary_tree_curr = binary_tree_curr->lchild;				//访问左子树 
				//当前结点为空为空，当前结点出栈
				//并把右孩子作为当前结点 
				while(!binary_tree_curr && !stack.empty()){					
					binary_tree_curr = stack.top();
					stack.pop();
					binary_tree_curr = binary_tree_curr->rchild;
				}
			}
		}
		
		//递归中序遍历 
		void InorderTraversal(BinaryTree* T){
			if(T == NULL){
				return;
			}
			T->InorderTraversal(T->lchild);								//递归中序遍历左子树 
			cout<<T->data<<" ";											//访问根节点并输出 
			T->InorderTraversal(T->rchild);								//递归中序遍历左子树 
		}
		
		//非递归中序遍历
		void InorderTraversal2(BinaryTree* T){
			stack<BinaryTree*> stack;									//初始化栈 
			BinaryTree* binary_tree_curr = T;							//保存当前结点 
			while(binary_tree_curr || !stack.empty()){
				if(binary_tree_curr->lchild){							//左孩子非空
					stack.push(binary_tree_curr);						//当前结点入栈 
					binary_tree_curr = binary_tree_curr->lchild;		//遍历左子树 
				}else{
					//左孩子为空，则打印当前结点遍历右子树 
					cout<<binary_tree_curr->data<<" ";					
					binary_tree_curr = binary_tree_curr->rchild;
					//如果为空，且栈不空，则将栈顶节点出栈，并输出该节点，  
            		//同时将它的右孩子设为当前节点，继续判断，直到当前节点不为空   
					while(!binary_tree_curr && !stack.empty()){
						binary_tree_curr = stack.top();
						cout<<binary_tree_curr->data<<" ";
						stack.pop();
						binary_tree_curr = binary_tree_curr->rchild;
					}
				}
			}
		}
		
		//递归后序遍历 
		void PostorderTraversal(BinaryTree* T){
			if(T == NULL){
				return;
			}
			T->PostorderTraversal(T->lchild);						//递归后序遍历左子树 
			T->PostorderTraversal(T->rchild);						//递归后序遍历右子树 
			cout<<T->data<<" ";										//访问并打印根节点 
		}
		
		//非递归后序遍历
		void PostorderTraversal2(BinaryTree* T){
			stack<BinaryTree*> stack;
			BinaryTree* binary_tree_curr = T;					//当前结点 
			BinaryTree* binary_tree_pre = NULL;				   // 上一个结点 
			//先将树的根节点入栈
			stack.push(binary_tree_curr);
			//直到栈空时，结束循环  
			while(!stack.empty()){
				binary_tree_curr = stack.top();				 //当前节点置为栈顶节点  
				//如果当前节点没有左右孩子，或者有左孩子或有孩子，但已经被访问输出，  
            	//则直接输出该节点，将其出栈，将其设为上一个访问的节点  
				if((binary_tree_curr->lchild == NULL && binary_tree_curr->rchild == NULL) ||
					(binary_tree_curr != NULL && binary_tree_curr->lchild == binary_tree_pre || 
												binary_tree_curr->rchild == binary_tree_pre)){
					cout<<binary_tree_curr->data<<" ";
					stack.pop();
					binary_tree_pre = binary_tree_curr; 
				}else{
					//如果不满足上面两种情况,则将其右孩子左孩子依次入栈  
					if(binary_tree_curr->rchild != NULL){
						stack.push(binary_tree_curr->rchild);
					}
					if(binary_tree_curr->lchild != NULL){
						stack.push(binary_tree_curr->lchild);
					} 
				}
			}
		}
		
		//层次遍历
		void LevelOrderTraversal(BinaryTree* T){
			queue<BinaryTree*> queue;
			BinaryTree* cur = T;
			//头结点入队 
			queue.push(cur);
			//队列为空时循环结束 
			while(!queue.empty()){
				//队列头元素出队 
				cur = queue.front();
				queue.pop();
				cout<<cur->data<<" ";
				//左孩子不为空入队 
				if(cur->lchild != NULL){
					queue.push(cur->lchild);
				}
				//右孩子不为空时入队 
				if(cur->rchild != NULL){
					queue.push(cur->rchild);
				}
			} 
		}
		
		//递归二叉树的高度
		int getBinaryTreeHeight(BinaryTree* T){
			if(T){
				//递归求左子树高度 
				int lheight = T->getBinaryTreeHeight(T->lchild);
				//递归求右子树高度 
				int rheight = T->getBinaryTreeHeight(T->rchild);
				//树的高度等于左右子树高度的较大者加1
				int height = (lheight>rheight)?lheight:rheight;
				height++;
				return height;	
			}
			return 0; 
		}
		
		//非递归求二叉树高度
		int getBinaryTreeHeight2(BinaryTree* T){
			if(T == NULL){
				return 0;
			}
			vector<BinaryTree*> queue(110000); 
			int front = -1,rear = -1;
			int last = 0,height = 0;
			BinaryTree* cur = T;
			queue[++rear] = cur;
			while(front < rear){
				cur = queue[++front];
				if(cur->lchild){
					queue[++rear] = cur->lchild;
				}
				if(cur->rchild){
					queue[++rear] = cur->rchild;
				}
				if(front == last){
					height++;
					last = rear;
				}
			}
			return height;
		}
		
		//判断是够为完全二叉树
		bool Judge(BinaryTree* T){
			if(T == NULL){
				return true;
			}
			bool flag = true;
			queue<BinaryTree*> queue;
			BinaryTree* cur = T;
			queue.push(cur);
			while(!queue.empty()){
				cur = queue.front();
				queue.pop();
				//当前结点为真，左右孩子入队
				//否则，循环判断队列在此只够是否有非空的情况 
				if(cur){
					queue.push(cur->lchild);
					queue.push(cur->rchild);
				}else{
					while(!queue.empty()){
						cur = queue.front();
						queue.pop();
						if(cur){
							return false;
						}
					}
				}
			}
			return true;
		} 
		
		//递归打印x结点的祖先结点 
		bool FindAncestors(BinaryTree* T,char data){
			if(T == NULL){
				return false;
			}
			BinaryTree* cur = T;
			if(cur->data == data){
				return true;
			}
			if(FindAncestors(cur->lchild ,data) || FindAncestors(cur->rchild,data)){
				cout<<cur->data<<" ";
				return true; 
			}
			return false;
		}
		
		//非递归打印x结点的祖先结点 
		void FindAncestors2(BinaryTree* T,char data){
			stack<BinaryTree*> stack;
			BinaryTree* cur = T;
			bool flag; 
			
			while(!stack.empty()||cur){
				if(cur){
					stack.push(cur);
					flag = false;		//访问了左孩子
					cur = cur->lchild; 
				}else{
					cur = stack.top();
					stack.pop();
					if(!flag){
						flag = true;		//访问了右孩子 
						stack.push(cur);
						cur = cur->rchild;
					}else{
						if(cur->data == data){
							break;
						}
					}
				}
			}
			while(!stack.empty()){
				cur = stack.top();
				stack.pop();
				cout<<cur->data<<" "; 
			}
		} 
		
		//求二叉树的宽度
		/*int getWidth(BinaryTree* T){
			BinaryTree* queue[100000];
			int index[100000];
			set<int> s;
			BinaryTree* cur = T;
			int front = -1,rear = -1;
			int last = 0,level = 0;
			int cnt = 0;
			queue[++rear] = cur;
			level++;
			while(front < rear){
				cur = queue[++front];
				index[cnt++] = level;
				s.insert(level);
				if(cur->lchild){
					queue[++rear] = cur->lchild;
				}
				if(cur->rchild){
					queue[++rear] = cur->rchild;
				}
				if(front == last){
					level++;
					last = rear;
				}	
			}
			int max = 0,width ,i = 0;
			for(set<int>::iterator it = s.begin() ; it != s.end() ; it++){
				width = 0;
				for(int j = i; j < cnt ; j++){
					if(index[j] == *it){
						width++;
					}else{
						i = j;
						break;
					} 
				}
				if(width > max){
					max = width;
				}
			}
			return max;
		}*/
		
		//求叶子节点带权路径长度之和
		int WPL(BinaryTree* T){
			BinaryTree* queue[100];			//构造容量足够大的队列
			BinaryTree* cur = T;			//指向根节点指针
			int front = -1,rear = -1;		//队头与队尾指针
			//last指向每层的最后一个结点，level代表层数 
			int last = 0,level = 0;
			int sum = 0;				//带权路径长度之和		 
			queue[++rear] = cur;		//根节点入队 
			level++;
			//队列不为空一直进行循环  
			while(front < rear){
				cur = queue[++front];	//根结点出队
				if(cur->lchild == NULL && cur->rchild == NULL){
					int weight = cur->data-'0';
					sum += (level-1)*weight;
				}
				//左孩子非空入队
				if(cur->lchild){			
					queue[++rear] = cur->lchild;
				}
				//右孩子非空入队
				if(cur->rchild){			
					queue[++rear] = cur->rchild;
				}
				//队头指针是该层最后一个结点时 
				if(front == last){			
					level++;				//层数加一 
					//最后一个结点指针下移到下一层的最后一个结点 
					last = rear;			
				}
			}
			return sum;
		}
		
		void set(char ch){
			this->data = ch;
			this->lchild = this->rchild = NULL;
		}
		
		//创建根节点的函数 
		BinaryTree* Creat_Node(char ch){
			BinaryTree* root;
			root = new BinaryTree;
			root->set(ch);
			return root;
		}
		
		//根据先序序列与中序序列构建二叉树
		BinaryTree* Pre_In_Build(char* pre ,char* in, int size){
			if(!pre || !in || size < 0){
				cout<<"输入出错！"<<endl;
				return NULL;
			}
			int root_index = 0;
			//寻找根结点 
			for(root_index = 0 ; root_index < size ; root_index++){
				if(in[root_index] == pre[0]){
					break;
				}else{
					continue;
				}
			}
			if(root_index == size){
				cout<<"先序序列与中序序列不匹配！"<<endl;
				return NULL;
			}
			//创建根结点 
			BinaryTree* root = this->Creat_Node(pre[0]);
			//递归构建左子树 
			if(root_index > 0){
				root->lchild = this->Pre_In_Build(pre+1,in,root_index); 
			}
			//递归构建右子树 
			if(size - root_index - 1 > 0){
				root->rchild = this->Pre_In_Build(pre+root_index+1,in+1+root_index,size-root_index-1);
			}
			return root;
		}
		
		bool PrintPath(BinaryTree* tree,char v,vector<char>& path){
			bool flag = false;
			BinaryTree* cur = tree;
			if(cur == NULL){
				return false;
			}
			path.push_back(cur->data);
			if(!flag && v == cur->data){
				for(int i = 0 ; i < path.size() ; i++){
					cout<<path[i]<<" ";
				}
				cout<<endl;
			}
			if(!flag && cur->lchild){
				flag = this->PrintPath(cur->lchild,v,path);
			}
			if(!flag && cur->rchild){
				flag = this->PrintPath(cur->rchild,v,path);
			}
			path.pop_back();
			return flag;
		} 
};

int main()
{
	/*char pre[8] = {'1', '2', '4', '7', '3', '5', '6', '8'};  
    char in[8] = {'4', '7', '2', '1', '5', '3', '8', '6'};  
	BinaryTree* T = NULL;
	T = T->Pre_In_Build(pre,in,8);*/
	
	cout<<"请初始化二叉树:"<<endl;
	BinaryTree* T;
	T = T->Create_BinaryTree();
	
	cout<<"前序遍历（递归）："<<endl;
	T->PreorderTraversal(T);
	cout<<endl;
	cout<<"前序遍历（非递归）："<<endl;
	T->PreorderTraversal2(T);
	cout<<endl; 
	
	cout<<"中序遍历（递归）："<<endl;
	T->InorderTraversal(T);
	cout<<endl;
	cout<<"中序遍历（非递归）："<<endl;
	T->InorderTraversal2(T);
	cout<<endl; 

	cout<<"后序遍历（递归）："<<endl;
	T->PostorderTraversal(T);
	cout<<endl;
	cout<<"后序遍历（非递归）："<<endl;
	T->PostorderTraversal2(T);
	cout<<endl; 

	cout<<"层次遍历："<<endl;
	T->LevelOrderTraversal(T);
	cout<<endl; 
	
	vector<char> path;
	bool flag = T->PrintPath(T,'5',path);
	
	cout<<"二叉树高度（递归）为:" <<endl;
	cout<<T->getBinaryTreeHeight(T)<<endl;
	
	cout<<"二叉树高度（非递归）为:" <<endl;
	cout<<T->getBinaryTreeHeight2(T)<<endl;
	
	if(T->Judge(T)){
		cout<<"这是棵完全二叉树"<<endl; 
	}else{
		cout<<"这不是棵完全二叉树"<<endl; 
	}

	char data = '5';
	cout<<"递归打印"<<data<<"的祖先结点："<<endl;
	T->FindAncestors(T,data);
	cout<<endl;
	
	cout<<"非递归打印"<<data<<"的祖先结点："<<endl;
	T->FindAncestors2(T,data);
	cout<<endl;
	
/*	cout<<"二叉树的宽度为："<<endl;
	int width = T->getWidth(T);
	cout<<width<<endl;*/  

	cout<<"叶子节点的带权路径之和为:"<<endl;
	int wpl = T->WPL(T);
	cout<<wpl<<endl; 

	return 0;
 } 
