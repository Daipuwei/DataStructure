#include <stdio.h>
#include <stdlib.h>
#define LEN sizeof(Bintree)
typedef struct TreeNode *BinTree;
struct TreeNode
{ 
	char Data;
	BinTree Left,Right;
}Bintree;
BinTree CreateTree()
{
	char ch;
	BinTree T;
	scanf("%c",&ch);
	if(ch=='#')
	T=NULL;
	else {
	T=(BinTree)malloc(LEN);
	T->Data=ch;
	T->Left=CreateTree();
	T->Right=CreateTree();
	}
	return T;
}
void PreOrderTraversal(BinTree T)
{
	if(T){
		printf("%c",T->Data);
		PreOrderTraversal(T->Left);
		PreOrderTraversal(T->Right);
	}
}
void MidOrderTraversal(BinTree T)
{
	if(T){
		MidOrderTraversal(T->Left);
		printf("%c",T->Data);
		MidOrderTraversal(T->Right);
	}
}
void PostOrderTraversal(BinTree T)
{
	if(T){
		PostOrderTraversal(T->Left);
		PostOrderTraversal(T->Right);
		printf("%c",T->Data);
	}
}
int main()
{
	BinTree T;
	printf("这棵树为：\n");
	T=CreateTree();
	printf("该树的先序遍历为：\n");
	PreOrderTraversal(T);
	printf("\n");
	printf("该树的中序遍历为：\n");
	MidOrderTraversal(T);
	printf("\n");
	printf("该树的后序遍历为：\n");
	printf("\n");
	PostOrderTraversal(T);
	return 0;
}

