#include <iostream>
#include <stack>
using namespace std;

int MAX = -32767;

class BinarySearchTree{
	private:
		int data;
		BinarySearchTree* lchild;
		BinarySearchTree* rchild;
	public:
		//查找最小值
		BinarySearchTree* FindMin(BinarySearchTree* BST){
			BinarySearchTree* cur = BST;
			//搜索树为空时，返回NULL 
			if(cur == NULL){
				return NULL;
			} 
			while(cur){
				//左子树为空时，返回该节点 
				if(cur->lchild == NULL){
					return cur;
				}else{//否则在左子树里找最小值 
					cur = cur->lchild;
				}
			}
		}
		
		//查找最大值
		BinarySearchTree* FindMax(BinarySearchTree* BST){ 
			BinarySearchTree* cur = BST;
			//搜索树为空时，返回NULL
			if(cur == NULL){
				return NULL;
			} 
			while(cur){
				//右子树为空时,返回该节点 
				if(cur->rchild == NULL){
					return cur; 
				}else{//否则在左子树里找最小值 
					cur = cur->rchild;
				}
			}
		}
		
		//按值查找结点
		BinarySearchTree* Find(BinarySearchTree* BST,int data){
			BinarySearchTree* cur = BST;
			//搜索树为空，返回NULL 
			if(cur == NULL){
				return NULL; 
			}
			while(cur){
				//根节点值与data相等，返回根节点 
				if(cur->data == data){
					return cur;
				}else if(cur->data < data){
					//比data小，则在左子树里寻找 
					cur = cur->lchild;
				}else{//否则在右子树里寻找 
					cur = cur->rchild;
				}
			}
		}
		
		//插入函数
		BinarySearchTree* Insert(BinarySearchTree* BST,int data){
			//搜索树为空，则构建根节点 
			if(!BST){
				BST = new BinarySearchTree;
				BST->data = data;
				BST->lchild = BST->rchild = NULL; 
			}else{
				//若data小于根节点的值，则插入到左子树 
				if(data < BST->data){
					BST->lchild = BST->Insert(BST->lchild,data);
				}else if(data > BST->data){
					//若data小于根节点的值，则插入到左子树
					BST->rchild = BST->Insert(BST->rchild,data);
				}
			}
			return BST;
		}
		
		//二叉搜索树的构造,利用data数组构造二叉搜索树 
		BinarySearchTree* Create(int* data,int size){
			BinarySearchTree* bst = NULL; 
			for(int i = 0 ; i < size ; i++){
				bst = this->Insert(bst,data[i]);
			}
			return bst;
		}
		
		//递归前序遍历 
		void PreorderTraversal(BinarySearchTree* T){
			if(T == NULL){
				return;
			}
			cout<<T->data<<" ";							//访问根节点并输出 
			T->PreorderTraversal(T->lchild);			//递归前序遍历左子树 
			T->PreorderTraversal(T->rchild);			//递归前序遍历右子树
		}
		
		//递归中序遍历 
		void InorderTraversal(BinarySearchTree* T){
			if(T == NULL){
				return;
			}
			T->InorderTraversal(T->lchild);				//递归中序遍历左子树 
			cout<<T->data<<" ";							//访问根节点并输出 
			T->InorderTraversal(T->rchild);				//递归中序遍历左子树 
		}
		
		//递归后序遍历 
		void PostorderTraversal(BinarySearchTree* T){
			if(T == NULL){
				return;
			}
			T->PostorderTraversal(T->lchild);			//递归后序遍历左子树 
			T->PostorderTraversal(T->rchild);			//递归后序遍历右子树 
			cout<<T->data<<" ";							//访问并打印根节点 
		}
				
		//删除操作 
		BinarySearchTree* Delete(BinarySearchTree* BST,int data){
			if(!BST){//树空时，直接返回NULL 
				return BST;
			}else if(data < BST->data){
				//data小于根节点时，到左子树去删除data 
				BST->lchild = this->Delete(BST->lchild,data);
			}else if(data > BST->data){
				//data大于根节点时，到右子树去删除data 
				BST->rchild = this->Delete(BST->rchild,data); 
			}else{//data等于根节点时 
				if(BST->lchild && BST->rchild){
					//左右子树都不空时，用右子树的最小来代替根节点
					BinarySearchTree* tmp = this->FindMin(BST->rchild);
					BST->data = tmp->data;
					//删除右子树的最小结点 
					BST->rchild = this->Delete(BST->rchild,tmp->data);
				}else{//当左右子树都为空或者有一个空时 
					BinarySearchTree* tmp = BST;
					if(!BST->lchild){//左子树为空时 
						BST = BST->rchild;
					}else if(!BST->rchild){//右子树为空时 
						BST = BST->lchild; 
					}
					delete tmp; 
				}
			}
			return BST;
		}
		
		int getdata(BinarySearchTree* BST){
			return BST->data;
		}
		
		void FindK(BinarySearchTree* BST , int k){
			stack<BinarySearchTree*> stack;                                   //初始化栈 
            BinarySearchTree* binary_tree_curr = BST;                           //保存当前结点 
            while(binary_tree_curr || !stack.empty()){
                if(binary_tree_curr->rchild){                           //右孩子非空
                    stack.push(binary_tree_curr);                       //当前结点入栈 
                    binary_tree_curr = binary_tree_curr->rchild;        //遍历右子树 
                }else{
                    //右孩子为空，则打印当前结点遍历左子树 
                    if(binary_tree_curr->data >= k){
                    	cout<<binary_tree_curr->data<<" ";                  	
					} 
                    binary_tree_curr = binary_tree_curr->lchild;
                    //如果为空，且栈不空，则将栈顶节点出栈，并输出该节点，  
                    //同时将它的左孩子设为当前节点，继续判断，直到当前节点不为空   
                    while(!binary_tree_curr && !stack.empty()){
                        binary_tree_curr = stack.top();
                        if(binary_tree_curr->data >= k){
                    		cout<<binary_tree_curr->data<<" ";                  	
						} 
                        stack.pop();
                        binary_tree_curr = binary_tree_curr->lchild;
                    }
                }
            }
		}
		
		//删除最小值
		BinarySearchTree* DeleteMin(BinarySearchTree* BST){
			BinarySearchTree* cur = BST;	//当前结点 
			BinarySearchTree* parent = BST;	//当前结点的父节点
			if(cur == NULL){
				return BST;
			}
			//当前结点的左子树非空则一直循环 
			while(cur->lchild != NULL){
				parent = cur;		//保存当前结点父节点 
				cur = cur->lchild;	//把当前结点指向左子树 
			}
			if(cur == BST){//当前结点为根结点，即只有右子树 
				BST = BST->rchild;
			}else{
				if(cur->rchild == NULL){//右子树为空，即为叶子节点 
					parent->lchild = NULL; 		//父节点左子树置空
					delete cur;
				}else{//右子树非空 
					parent->lchild = cur->rchild;	//把当前结点右子树放到父节点的左子树上 
					delete cur;
				}
			}
			return BST;
		}
		
		//删除最大值
		BinarySearchTree* DeleteMax(BinarySearchTree* BST){
			BinarySearchTree* cur = BST;	//当前结点 
			BinarySearchTree* parent = BST;	//当前结点的父节点
			if(cur == NULL){
				return BST;
			}
			//当前结点右子树非空则一直循环 
			while(cur->rchild != NULL){
				parent = cur;		//保存当前结点父节点 
				cur = cur->rchild;	//把当前结点指向右子树 
			}
			if(cur == BST){//当前结点为根结点，即只有左子树 
				BST = BST->lchild;
			}else{
				if(cur->lchild == NULL){//左子树为空，即为叶子节点 
					parent->rchild = NULL;		//父节点右子树置空 
					delete cur;
				}else{//左子树非空 
					parent->rchild = cur->lchild;	//把当前结点左子树放到父节点的右子树上 
					delete cur;
				}
			}
			return BST;
		}
		
		//判断是否为二叉排序树 
		bool Judge(BinarySearchTree* root,int& MAX){
			if(root == NULL){//树为空则为二叉排序树 
				return true;
			}
			bool bst_l,bst_r;
			bst_l = Judge(root->lchild,MAX);//判断左子树是否为二叉排序树
			if(!bst_l || MAX > root->data){
				return false;
			}
			MAX = root->data;
			bst_r = Judge(root->rchild,MAX);//判断右子树是否为二叉排序树
			if(!bst_r || MAX < root->data){
				return false;
			}
			return true; 
		} 
};

int main()
{
	int size;
	cout<<"请输入结点个数："<<endl; 
	cin>>size;
	int* data;
	data = new int[size];
	cout<<"请输入每个结点的值："<<endl;
	for(int i = 0 ; i < size ; i++){
		cin>>data[i];
	}
	BinarySearchTree* bst;
	bst = new BinarySearchTree;
	bst = bst->Create(data,size);
	
	cout<<"前序遍历（递归）："<<endl;
	bst->PreorderTraversal(bst);
	cout<<endl;
	
	cout<<"中序遍历（递归）："<<endl;
	bst->InorderTraversal(bst);
	cout<<endl;
	
	cout<<"后序遍历（递归）："<<endl;
	bst->PostorderTraversal(bst);
	cout<<endl;
	
	BinarySearchTree* bst_max;
	bst_max = bst->FindMax(bst);
	cout<<"二叉搜索树的最大值为："<<endl;
	cout<<bst_max->getdata(bst_max);
	cout<<endl;
	cout<<"删除最大值后："<<endl;
	bst = bst->DeleteMax(bst);
	cout<<"前序遍历（递归）："<<endl;
	bst->PreorderTraversal(bst);
	cout<<endl;
	
	cout<<"中序遍历（递归）："<<endl;
	bst->InorderTraversal(bst);
	cout<<endl;
	
	cout<<"后序遍历（递归）："<<endl;
	bst->PostorderTraversal(bst);
	cout<<endl;
	
	cout<<"二叉搜索树的最小值为："<<endl;
	BinarySearchTree* bst_min; 
	bst_min = bst->FindMin(bst);
	cout<<bst_min->getdata(bst_min);	 
	cout<<endl;
	cout<<"删除最小值后："<<endl;
	bst = bst->DeleteMin(bst);
	cout<<"前序遍历（递归）："<<endl;
	bst->PreorderTraversal(bst);
	cout<<endl;
	
	cout<<"中序遍历（递归）："<<endl;
	bst->InorderTraversal(bst);
	cout<<endl;
	
	cout<<"后序遍历（递归）："<<endl;
	bst->PostorderTraversal(bst);
	cout<<endl;
	
	int num;
	cout<<"请输入要删除的结点："<<endl;
	cin>>num;
	bst = bst->Delete(bst,num);
	cout<<"删除之后："<<endl;
	cout<<"前序遍历（递归）："<<endl;
	bst->PreorderTraversal(bst);
	cout<<endl;
	
	cout<<"中序遍历（递归）："<<endl;
	bst->InorderTraversal(bst);
	cout<<endl;
	
	cout<<"后序遍历（递归）："<<endl;
	bst->PostorderTraversal(bst);
	cout<<endl;
	
	return 0;
 } 
