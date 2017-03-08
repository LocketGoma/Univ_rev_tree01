#include <stdio.h>
#include <malloc.h>
#include <assert.h>
#include "binaryTree.h"

/* -------------------------------------------------------------------------------------
�Լ��� : initTree - Ʈ�� ���� ����ü�� �ʱ�ȭ �ϴ� �Լ�
�������� : tr - Tree ����ü�� �ּ�
���� �� : ����
--------------------------------------------------------------------------------------*/
void initTree(Tree *tr)
{
	tr->root = NULL;
	tr->nodeCnt = 0;
}
/* --------------------------------------------------------------------------------------
�Լ��� : makeNode - �� ��带 ����� �� ����� �ּҸ� �����ϴ� �Լ�
�������� : data - �� ��忡 ����� ��(������)
left - �� ����� left ��� ��
right - �� ����� right ��� ��
���� �� : �� ����� �ּ� / �޸� �Ҵ� ���� �� NULL pointer 
---------------------------------------------------------------------------------------*/
Node * makeNode(DataType *data, Node * left, Node *right)
{
	Node *np;
	np = (Node *)malloc(sizeof(Node));
	if (np != NULL) {
		np->data = *data;
		np->left = left;
		np->right = right;
	}
	return np;
}

/* --------------------------------------------------------------------------------------
�Լ��� : addNode - ��带 �����ϴ� �Լ�
�������� : tr - Tree ����ü�� �ּ�
data - �� ��忡 ����� ������ ���� ������ �ּ�
compare - data���� �񱳸� ���� �����Լ��� �����ּ�
���� �� : �� ����� �ּ� / �޸� �Ҵ� ���� �� NULL pointer
---------------------------------------------------------------------------------------*/
Node *addNode(Tree *tr, DataType *data, int(*compare)(DataType *, DataType *))
{
	Node *tIn = (makeNode(data, NULL, NULL));
	Node *tShot = tr->root;
	while (tIn!=NULL) {
		if (tr->root == NULL) {
			tr->root = tIn;
			return tIn;
			break;
		}
		else if (compare(&tShot->data, data) == 1) {
			if (tShot->left == NULL) {
				tShot->left = tIn;
				return tIn;
				break;
			}
			else
				tShot = tShot->left;
		}
		else if (compare(&tShot->data, data) == -1) {
			if (tShot->right == NULL) {
				tShot->right = tIn;
				return tIn;
				break;
			}
			else
				tShot = tShot->right;
		} 
	}
	return NULL;
}
/* --------------------------------------------------------------------------------------
�Լ��� : inorderTraverse - ������ȸ(���� ������ ���)
�������� : np - �湮�� ����� �ּ�
print - data������ ����ϴ� �����Լ��� �ּ�
���� �� : ����
---------------------------------------------------------------------------------------*/
void inorderTraverse(Node *np, void(*print)(DataType *))
{
	if (np == NULL)
		return;
	else {
		inorderTraverse(np->left, printInt);
		print(&np->data);
		inorderTraverse(np->right, printInt);
		
	}
}

/* --------------------------------------------------------------------------------------
�Լ��� : preorderTraverse - ������ȸ
�������� : np - �湮�� ����� �ּ�
print - data������ ����ϴ� �����Լ��� �ּ�
���� �� : ����
---------------------------------------------------------------------------------------*/
void preorderTraverse(Node *np, void(*print)(DataType *))
{
     // TODO	
	if (np == NULL)
		return;
	else {
		print(&np->data);
		preorderTraverse(np->left, printInt);
		preorderTraverse(np->right, printInt);
	}
}
/* --------------------------------------------------------------------------------------
�Լ��� : postorderTraverse - ������ȸ
�������� : np - �湮�� ����� �ּ�
print - data������ ����ϴ� �����Լ��� �ּ�
���� �� : ����
---------------------------------------------------------------------------------------*/
void postorderTraverse(Node *np, void(*print)(DataType *))
{
	if (np == NULL)
		return;
	else {
		postorderTraverse(np->left, printInt);
		postorderTraverse(np->right, printInt);
		print(&np->data);

	}
}
/* --------------------------------------------------------------------------------------
�Լ��� : searchNode - data�� �ش��ϴ� ��� �˻�
�������� : tr - Tree ����ü�� �ּ�
data - �˻��� ������ ���� ������ �����ּ�
compare - data���� �񱳸� ���� �����Լ��� �����ּ�
���� �� : ã�� ����� �ּ� / ��ã���� NULL pointer
---------------------------------------------------------------------------------------*/
Node * searchNode(Tree *tr, DataType  *data, int(*compare)(DataType *, DataType *))
{
	Node *tShot = tr->root;
	int flag = compare(&tShot->data, data);
	while (1){
		if (tShot == NULL) {
			break;
		}
		flag = compare(&tShot->data, data);
		if (flag == 0) {
			return tShot;
		}
		else if (flag == 1) {
			tShot = tShot->left;
		}
		else if (flag == -1)
			tShot = tShot->right;
	}

	return NULL;
}

/* --------------------------------------------------------------------------------------
�Լ��� : deleteNode - data�� �ش��ϴ� ��� ����
�������� : tr - Tree ����ü�� �ּ�
data - ������ �������� �����ּ�
compare - data���� �񱳸� ���� �����Լ��� �����ּ�
���� �� : ������ ����� parent ����� �ּ� / ��ã����(���� ���� ��) NULL pointer
---------------------------------------------------------------------------------------*/
Node * deleteNode(Tree *tr, DataType *data, int(*compare)(DataType *, DataType *))
{
	// TODO	
	Node * del=searchNode(tr, data, compare);
	Node * delP = tr->root; // �θ��� ã��
	//---- ������ ���, ���� �θ���
	//--�θ��� Ž�� ��Ʈ
		int flag[3];
		int swit = 0; // 0 - left, 1 - right
		if (del == NULL) return NULL;
	while (1) {
		if (delP == NULL) break;
		if (del==tr->root) break;
		flag[0] = compare(&delP->data, data);
		if(delP->left!=NULL) flag[1] = compare(&delP->left->data , data);
		if(delP->right!=NULL) flag[2] = compare(&delP->right->data, data);
		
		if (flag[1] == 0) {
			break;
		}
		if (flag[2] == 0) {
			swit = 1;
			break;
		}
		if (flag[0] == 1) {
			delP = delP->left;
		}
		else if (flag[0] == -1)
			delP = delP->right;
	}
	//---�θ��� Ž����Ʈ  ��
	Node * mov;
	Node * movP;
	printf("[%d]\n", del->data);
	//--- ������Ʈ
	if (del == tr->root);
		//delP = tr; ������ ��尡 root�� ���
		
	while (1) {
		if (del == NULL) {
			return NULL;
		}
		if (del->left == del->right) { // 0.�����϶� (=�ڽĳ�� 0��)
			free(del);
			return delP;
		}
		else if (del->right == NULL) { //1. ������� ���� ��� ������ -> ���� ����
			if (del == tr->root) {
				tr->root = del->left;
			}
			else if (swit == 0) {
				delP->left = del->left;
			}
			else if (swit == 1) {
				delP->right = del->left;
			}
			free(del);
			return delP;
		}
		else if (del->right->left == NULL) { //2. ������� ������ ������ ������ -> ���� ����
			if (del == tr->root) {
				tr->root = del->right;
		}
		else if (swit == 0) {
				delP->left = del->right;
				delP->left->left = del->left;
			}
			else if (swit == 1) {
				delP->right = del->right;
				delP->right->left = del->left;
			}
			free(del);
			return delP;
		}
		else{ // 3. �� ��
			mov = del->right;
			movP = mov;
			while(mov->left != NULL) { //������ ��� ��ü : ���� subƮ�� �׷��� ���� ����
				mov = mov->left;
			}
			if(mov->right != NULL) {
				while (movP->left != NULL) {
					movP = movP->left;
				}
				movP->left = mov->right;
				mov->right = NULL;
			}
			printf("�ű氪 :%d\n", mov->data);

			if (tr->root == del) {
				printf(">>�Լ�<<");
				tr->root = mov;
				tr->root->left = del->left;
				tr->root->right = del->right;
				printf("%d\n", tr->root->right->data);
				free(del);
				return tr->root;
			}
			else if (swit == 0) {
				delP->left = mov;
				delP->left->left = del->left;
				delP->left->right = del->right;
			}
			else if (swit == 1) {
				delP->right = mov;
				delP->right->left = del->left;
				delP->right->right = del->right;
			}
			free(del);
			return delP;	
		}
	}
		

	// ����1 : ������ ����� ������ �ڽ��� ���� ���-������ ����� ���� �ڽ��� son����
	
	// ����2 : ������ ����� ������ �ڽ��� ���� �ڽ��� ���� ���-������ ����� ������ �ڽ��� son����
	
	// ����3 : �׿� ��� ���-������ ����� ������ ����Ʈ������ ������ �����Ϳ� ���� ����� ���� ã��
	
	// ������ ��� ��� �ڽ�(son) ������ �� ��带 ��ġ��Ŵ
	return NULL;
}
/* --------------------------------------------------------------------------------------
�Լ��� : destroyTree - tree ���� ��� ��� ����(tree �Ҹ�)
�������� : tr - Tree ����ü�� �ּ�
print - data������ ����ϴ� �����Լ��� �ּ�
���� �� : ����
---------------------------------------------------------------------------------------*/
void destroyTree(Tree * tr, void(*print)(DataType *))
{
	postorderDelete(tr->root, print);  // ������ ���� ��ȸ �ϸ� ����
	tr->root = NULL;
	tr->nodeCnt = 0;
}

/* --------------------------------------------------------------------------------------
�Լ��� : postorderDelete - postorder(���� ��ȸ)����� ��� ����(���ȣ�� �Լ�)
�������� : np - �湮�� ����� �ּ�
print - data������ ����ϴ� �����Լ��� �ּ�
���� �� : ����
---------------------------------------------------------------------------------------*/
void postorderDelete(Node *np, void(*print)(DataType *))
{

}
