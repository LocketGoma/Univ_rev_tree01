#include <stdio.h>
#include <malloc.h>
#include <assert.h>
#include "binaryTree.h"

/* -------------------------------------------------------------------------------------
함수명 : initTree - 트리 관리 구조체를 초기화 하는 함수
전달인자 : tr - Tree 구조체의 주소
리턴 값 : 없음
--------------------------------------------------------------------------------------*/
void initTree(Tree *tr)
{
	tr->root = NULL;
	tr->nodeCnt = 0;
}
/* --------------------------------------------------------------------------------------
함수명 : makeNode - 새 노드를 만들어 새 노드의 주소를 리턴하는 함수
전달인자 : data - 새 노드에 저장될 값(데이터)
left - 새 노드의 left 멤버 값
right - 새 노드의 right 멤버 값
리턴 값 : 새 노드의 주소 / 메모리 할당 실패 시 NULL pointer 
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
함수명 : addNode - 노드를 삽입하는 함수
전달인자 : tr - Tree 구조체의 주소
data - 새 노드에 저장될 데이터 저장 공간의 주소
compare - data영역 비교를 위한 보조함수의 시작주소
리턴 값 : 새 노드의 주소 / 메모리 할당 실패 시 NULL pointer
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
함수명 : inorderTraverse - 중위순회(정렬 순서로 출력)
전달인자 : np - 방문할 노드의 주소
print - data영역을 출력하는 보조함수의 주소
리턴 값 : 없음
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
함수명 : preorderTraverse - 전위순회
전달인자 : np - 방문할 노드의 주소
print - data영역을 출력하는 보조함수의 주소
리턴 값 : 없음
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
함수명 : postorderTraverse - 후위순회
전달인자 : np - 방문할 노드의 주소
print - data영역을 출력하는 보조함수의 주소
리턴 값 : 없음
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
함수명 : searchNode - data에 해당하는 노드 검색
전달인자 : tr - Tree 구조체의 주소
data - 검색할 데이터 저장 공간의 시작주소
compare - data영역 비교를 위한 보조함수의 시작주소
리턴 값 : 찾은 노드의 주소 / 못찾으면 NULL pointer
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
함수명 : deleteNode - data에 해당하는 노드 삭제
전달인자 : tr - Tree 구조체의 주소
data - 삭제할 데이터의 시작주소
compare - data영역 비교를 위한 보조함수의 시작주소
리턴 값 : 삭제한 노드의 parent 노드의 주소 / 못찾으면(삭제 실패 시) NULL pointer
---------------------------------------------------------------------------------------*/
Node * deleteNode(Tree *tr, DataType *data, int(*compare)(DataType *, DataType *))
{
	// TODO	
	Node * del=searchNode(tr, data, compare);
	Node * delP = tr->root; // 부모노드 찾기
	//---- 삭제될 노두, 그의 부모노드
	//--부모노드 탐색 파트
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
	//---부모노드 탐색파트  끝
	Node * mov;
	Node * movP;
	printf("[%d]\n", del->data);
	//--- 삭제파트
	if (del == tr->root);
		//delP = tr; 삭제될 노드가 root인 경우
		
	while (1) {
		if (del == NULL) {
			return NULL;
		}
		if (del->left == del->right) { // 0.리프일때 (=자식노드 0개)
			free(del);
			return delP;
		}
		else if (del->right == NULL) { //1. 삭제노드 우측 노드 없을때 -> 좌측 끌올
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
		else if (del->right->left == NULL) { //2. 삭제노드 우측의 좌측이 없을때 -> 우측 끌올
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
		else{ // 3. 그 외
			mov = del->right;
			movP = mov;
			while(mov->left != NULL) { //삭제된 노드 대체 : 우측 sub트리 그룹의 가장 좌측
				mov = mov->left;
			}
			if(mov->right != NULL) {
				while (movP->left != NULL) {
					movP = movP->left;
				}
				movP->left = mov->right;
				mov->right = NULL;
			}
			printf("옮길값 :%d\n", mov->data);

			if (tr->root == del) {
				printf(">>입성<<");
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
		

	// 유형1 : 삭제할 노드의 오른쪽 자식이 없는 경우-삭제할 노드의 왼쪽 자식이 son역할
	
	// 유형2 : 삭제할 노드의 오른쪽 자식의 왼쪽 자식이 없는 경우-삭제할 노드의 오른쪽 자식이 son역할
	
	// 유형3 : 그외 모든 경우-삭제한 노드의 오른쪽 서브트리에서 삭제할 데이터와 가장 가까운 값을 찾음
	
	// 삭제될 노드 대신 자식(son) 역할을 할 노드를 위치시킴
	return NULL;
}
/* --------------------------------------------------------------------------------------
함수명 : destroyTree - tree 내의 모든 노드 삭제(tree 소멸)
전달인자 : tr - Tree 구조체의 주소
print - data영역을 출력하는 보조함수의 주소
리턴 값 : 없음
---------------------------------------------------------------------------------------*/
void destroyTree(Tree * tr, void(*print)(DataType *))
{
	postorderDelete(tr->root, print);  // 데이터 노드는 순회 하며 삭제
	tr->root = NULL;
	tr->nodeCnt = 0;
}

/* --------------------------------------------------------------------------------------
함수명 : postorderDelete - postorder(후위 순회)방식의 노드 삭제(재귀호출 함수)
전달인자 : np - 방문할 노드의 주소
print - data영역을 출력하는 보조함수의 주소
리턴 값 : 없음
---------------------------------------------------------------------------------------*/
void postorderDelete(Node *np, void(*print)(DataType *))
{

}
