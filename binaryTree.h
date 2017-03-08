#pragma once
#include "datatype.h"
typedef struct _node Node;
struct _node
{
	DataType data;   // 데이터 저장 멤버
	Node *left;      // 왼쪽 자식 노드를 가리키는 포인터 멤버
	Node *right;     // 오른쪽 자신 노드를 가리키는 포인터 멤버
};

typedef struct _tree
{
	Node *root;   // 트리의 head node를 가리키는 포인터 멤버
	int nodeCnt;  // 총 노드의 개수
}Tree;

void initTree(Tree *tr);              // 트리 관리 구조체를 초기화 하는 함수
Node * makeNode(DataType *data,Node *, Node *);   // 새노드를 만들어 새노드의 주소를 리턴하는 함수
Node *addNode(Tree *tr, DataType *data, int (*compare)(DataType *, DataType *));    // 노드를 삽입하는 함수
void inorderTraverse(Node *np, void (*print)(DataType *));    // 중위순회(정렬 순서로 출력)
void preorderTraverse(Node *np, void (*print)(DataType *));       // 전위순회
void postorderTraverse(Node *np, void (*print)(DataType *));    // 후위순회
Node * searchNode(Tree *tr, DataType  *data, int (*compare)(DataType *, DataType *));   // data에 해당하는 노드 검색 / 찾은 노드의 주소 리턴, 못찾으면 NULL 리턴
Node * deleteNode(Tree *tr, DataType *data, int (*compare)(DataType *, DataType *));  // data에 해당하는 노드 삭제 / 삭제한 노드의 parent의 주소 리턴
void destroyTree (Tree * tr, void (*print)(DataType *));    // tree내의 모든 노드 삭제(tree 소멸)
void postorderDelete(Node *np, void (*print)(DataType *)); // postorder(후위 순회)방식의 노드 삭제 재귀호출 함수