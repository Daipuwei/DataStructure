#include <iostream>
using namespace std;

class AVL{
	private:
		int data;		//结点的键值 
		int height;		//结点的高度 
		AVL* lchild;	//左孩子 
		AVL* rchild;	//右孩子 
	public:
		//查找最小值
		AVL* FindMin(AVL* avl){
			AVL* cur = avl;
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
		AVL* FindMax(AVL* avl){ 
			AVL* cur = avl;
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
		
		//插入函数
		AVL* Insert(AVL* avl,int data){
			//平衡二叉树为空，则构建根节点 
			if(!avl){ 
				avl = new AVL;
				avl->data = data;
				avl->height = 0; 
				avl->lchild = avl->rchild = NULL; 
			}else if(data < avl->data){//若data小于根节点的值，则插入到左子树 
				avl->lchild = avl->Insert(avl->lchild,data);
				int rheight = this->getHeight(avl->rchild);		//右子树高度
				int lheight = this->getHeight(avl->lchild);		//左子树高度
				//如果插入导致左子树失衡，即左子树比右子树高2 
				if(lheight - rheight == 2){
					if(data <avl->lchild->data){
						//插入的结点比左孩子的键值小
						//那么一定是插入到左孩子的左子树上，故进行LL旋转 
						avl = this->SingleLeftRotation(avl);	
					}else{//否则是插入到左孩子的右子树上，故要进行LR旋转 
						avl = this->DoubleLeftRightRotation(avl);
					}
				}
			}else if(data > avl->data){//若data小于根节点的值，则插入到左子树
				avl->rchild = avl->Insert(avl->rchild,data);
				int rheight = this->getHeight(avl->rchild);		//右子树高度
				int lheight = this->getHeight(avl->lchild);		//左子树高度
				//如果插入导致右子树失衡，即右子树比左子树高2
				if(rheight - lheight == 2){
					if(data > avl->rchild->data){
						//插入的结点比右孩子的键值大 
						//那么一定是插入到右孩子的右子树上，故进行RR旋转 
						avl = this->SingleRightRotation(avl);	
					}else{//否则是插入到右孩子的左子树上，故要进行RL旋转 
						avl = this->DoubleRightLeftRotation(avl);
					}
				}
			}
			//更新结点的高度 
			avl->height = this->Max(this->getHeight(avl->lchild),this->getHeight(avl->rchild))+1;
			return avl;
		}
		
		//二叉搜索树的构造,利用data数组构造二叉搜索树 
		AVL* Create(int* data,int size){
			AVL* avl = NULL; 
			for(int i = 0 ; i < size ; i++){
				avl = this->Insert(avl,data[i]);
			}
			return avl;
		}
		
		//删除操作
		AVL* Delete(AVL* avl,int data){
			if(!avl){//树空时，直接返回NULL 
				return avl;
			}else if(data < avl->data){
				//data小于根节点时，到左子树去删除data,则有可能使右子树比左子树高2 
				avl->lchild = this->Delete(avl->lchild,data);
				int rheight = this->getHeight(avl->rchild);		//右子树高度
				int lheight = this->getHeight(avl->lchild);		//左子树高度
				if(rheight - lheight == 2){//右子树比左子树高2时 
					if(data > avl->rchild->data){
						//如果是data比右子树的键值大，在右子树的右子树上，则进行RR旋转 
						avl = this->SingleRightRotation(avl); 
					}else{//否则是data比右子树的键值小，在右子树的左子树上，则进行RL旋转 
						avl = this->DoubleRightLeftRotation(avl); 
					}
				}
			}else if(data > avl->data){
				//data大于根节点时，到右子树去删除data 
				avl->rchild = this->Delete(avl->rchild,data);
				int rheight = this->getHeight(avl->rchild);		//右子树高度
				int lheight = this->getHeight(avl->lchild);		//左子树高度
				if(lheight - rheight == 2){//左子树比右子树高2时 
					if(data < avl->lchild->data){
						//如果是data比左子树的键值小，在左子树的左子树上，则进行LL旋转 
						avl = this->SingleLeftRotation(avl); 
					}else{//否则是data比左子树的键值大，在左子树的右子树上，则进行LR旋转 
						avl = this->DoubleLeftRightRotation(avl); 
					}
				}
			}else{//data等于根节点时 
				if(avl->lchild && avl->rchild){
					//左右子树都不空时，用右子树的最小来代替根节点
					AVL* tmp = this->FindMin(avl->rchild);
					avl->data = tmp->data;
					//删除右子树的最小结点 
					avl->rchild = this->Delete(avl->rchild,tmp->data);
				}else{//当左右子树都为空或者有一个空时 
					AVL* tmp = avl;
					if(!avl->lchild){//左子树为空时 
						avl = avl->rchild;
					}else if(!avl->rchild){//右子树为空时 
						avl = avl->lchild; 
					}
					delete tmp; 
				}
			}
			return avl;
		}
		
		//单左旋：左左旋函数 
		//左子树的左子树导致的失衡，把左子树与根结点进行调整
		//根结点的左孩子做根结点，之前的根结点做现在根结点的右孩子
		//这是因为平衡二叉树一定是二叉搜索树的缘故导致的 
		AVL* SingleLeftRotation(AVL* avl){
			//注意：avl必须有一个左子结点tmp 
  			//将avl与tmp做左单旋，更新avl与tmp的高度，返回新的根结点tmp  
			AVL* tmp = avl->lchild;			 
			avl->lchild = tmp->rchild;
			tmp->rchild = avl;
			avl->height = this->Max(this->getHeight(avl->lchild),this->getHeight(avl->rchild))+1;
			tmp->height = this->Max(this->getHeight(tmp->lchild),this->getHeight(avl))+1;
			return tmp;
		}
		
		//单右旋：右右旋函数 
		//右子树的右子树导致的失衡，把右子树与根结点进行调整
		//根结点的右孩子做根结点，之前的根结点做现在根结点的左孩子
		//这是因为平衡二叉树一定是二叉搜索树的缘故导致的 
		AVL* SingleRightRotation(AVL* avl){
			//注意：avl必须有一个右子结点tmp 
  			//将avl与tmp做右单旋，更新avl与tmp的高度，返回新的根结点tmp  
			AVL* tmp = avl->rchild;			 
			avl->rchild = tmp->lchild;
			tmp->lchild = avl;
			avl->height = this->Max(this->getHeight(avl->lchild),this->getHeight(avl->rchild))+1;
			tmp->height = this->Max(this->getHeight(tmp->rchild),this->getHeight(avl))+1;
			return tmp;
		}
		
		//左右旋转：LR旋转，左子树的右子树插入导致对的失衡 
		AVL* DoubleLeftRightRotation(AVL* avl){
			//注意：avl必须有一个左子结点B，且B必须有一个右子结点C
  			//将avl、B与C做两次单旋，返回新的根结点C
  			//首先对avl的左子树进行单右旋即RR旋转
			avl->lchild = this->SingleRightRotation(avl->lchild);
			//然后对avl进行单左旋即LL旋转
			return this->SingleLeftRotation(avl); 
		}
		
		//右左旋转：RL旋转，右子树的左子树插入导致对的失衡 
		AVL* DoubleRightLeftRotation(AVL* avl){
			//注意：avl必须有一个左子结点B，且B必须有一个右子结点C
  			//将avl、B与C做两次单旋，返回新的根结点C
  			//首先对avl的右子树进行单左旋即LL旋转
			avl->rchild = this->SingleLeftRotation(avl->rchild);
			//然后对avl进行单右旋即RR旋转
			return this->SingleRightRotation(avl); 
		}
		
		//获得树的高度 
		int getHeight(AVL* avl){
			if(!avl){
				return 0;
			}
			return avl->height;
		}
		
		//求两个数的最大值 
		int Max(int a,int b){
			return (a>b)?a:b;
		}
		
		//递归前序遍历 
		void PreorderTraversal(AVL* T){
			if(T == NULL){
				return;
			}
			cout<<T->data<<" ";							//访问根节点并输出 
			T->PreorderTraversal(T->lchild);			//递归前序遍历左子树 
			T->PreorderTraversal(T->rchild);			//递归前序遍历右子树
		}
		
		//递归中序遍历 
		void InorderTraversal(AVL* T){
			if(T == NULL){
				return;
			}
			T->InorderTraversal(T->lchild);				//递归中序遍历左子树 
			cout<<T->data<<" ";							//访问根节点并输出 
			T->InorderTraversal(T->rchild);				//递归中序遍历左子树 
		}
		
		//递归后序遍历 
		void PostorderTraversal(AVL* T){
			if(T == NULL){
				return;
			}
			T->PostorderTraversal(T->lchild);			//递归后序遍历左子树 
			T->PostorderTraversal(T->rchild);			//递归后序遍历右子树 
			cout<<T->data<<" ";							//访问并打印根节点 
		}
		
		int getdata(AVL* avl){
			return avl->data;
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
	AVL* avl;
	avl = new AVL;
	avl = avl->Create(data,size);
	
	cout<<"前序遍历（递归）："<<endl;
	avl->PreorderTraversal(avl);
	cout<<endl;
	
	cout<<"中序遍历（递归）："<<endl;
	avl->InorderTraversal(avl);
	cout<<endl;
	
	cout<<"后序遍历（递归）："<<endl;
	avl->PostorderTraversal(avl);
	cout<<endl;
	
	AVL* avl_max;
	avl_max = avl->FindMax(avl);
	cout<<"二叉搜索树的最大值为："<<endl;
	cout<<avl_max->getdata(avl_max);
	cout<<endl;
	 
	cout<<"二叉搜索树的最小值为："<<endl;
	AVL* avl_min; 
	avl_min = avl->FindMin(avl);
	cout<<avl_min->getdata(avl_min);	 
	cout<<endl;
	
	int num;
	cout<<"请输入要删除的结点："<<endl;
	cin>>num;
	avl = avl->Delete(avl,num);
	cout<<"删除之后："<<endl;
	cout<<"前序遍历（递归）："<<endl;
	avl->PreorderTraversal(avl);
	cout<<endl;
	
	cout<<"中序遍历（递归）："<<endl;
	avl->InorderTraversal(avl);
	cout<<endl;
	
	cout<<"后序遍历（递归）："<<endl;
	avl->PostorderTraversal(avl);
	cout<<endl;
	
	cout<<"请输入要删除的结点："<<endl;
	cin>>num;
	avl = avl->Delete(avl,num);
	cout<<"删除之后："<<endl;
	cout<<"前序遍历（递归）："<<endl;
	avl->PreorderTraversal(avl);
	cout<<endl;
	
	cout<<"中序遍历（递归）："<<endl;
	avl->InorderTraversal(avl);
	cout<<endl;
	
	cout<<"后序遍历（递归）："<<endl;
	avl->PostorderTraversal(avl);
	cout<<endl;
	
	cout<<"请输入要删除的结点："<<endl;
	cin>>num;
	avl = avl->Delete(avl,num);
	cout<<"删除之后："<<endl;
	cout<<"前序遍历（递归）："<<endl;
	avl->PreorderTraversal(avl);
	cout<<endl;
	
	cout<<"中序遍历（递归）："<<endl;
	avl->InorderTraversal(avl);
	cout<<endl;
	
	cout<<"后序遍历（递归）："<<endl;
	avl->PostorderTraversal(avl);
	cout<<endl;	
	
	return 0;
 } 
