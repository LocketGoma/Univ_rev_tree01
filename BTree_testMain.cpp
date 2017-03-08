#include <stdio.h>
#include "binaryTree.h"
int main()
{
	int ary[] = { 14, 25, 12, 18, 16, 15, 5, 23, 7, 17, 3, 13, 6 };
	int arySize = sizeof(ary) / sizeof(ary[0]);
	Tree  myTree;
	Node *resp;
	int searchData;
	int deleteData;

	initTree(&myTree);
	for (int i = 0; i < arySize; i++)
	{
		addNode(&myTree, &ary[i], compareInt);
	}

	// 중위 순회를 이용한 정렬된 상태로 출력하기
	printf("* 중위순회 결과 : ");
	inorderTraverse(myTree.root, printInt);  // 실제 첫번째 데이터노드의 주소 전달
	printf("\n\n");

	// 전위 순회 이용 출력하기
	printf("* 전위순회 결과 : ");
	preorderTraverse(myTree.root, printInt); // 실제 첫번째 데이터노드의 주소 전달
	printf("\n\n");
	// 후위 순회 이용 출력하기
	printf("* 후위순회 결과 : ");
	postorderTraverse(myTree.root, printInt); // 실제 첫번째 데이터노드의 주소 전달
	printf("\n\n");

	// 노드 검색
	searchData = 3;
	resp = searchNode(&myTree, &searchData, compareInt);
	if (resp != NULL) printf("%d 찾음!!\n\n", resp->data);
	else printf("%d 못찾음!!\n\n", searchData);

	searchData = 99;
	resp = searchNode(&myTree, &searchData, compareInt);
	if (resp != NULL) printf("%d 찾음!!\n\n", resp->data);
	else printf("%d 못찾음!!\n\n", searchData);

	searchData = 19;
	resp = searchNode(&myTree, &searchData, compareInt);
	if (resp != NULL) printf("%d 찾음!!\n\n", resp->data);
	else printf("%d 못찾음!!\n\n", searchData);

	searchData = 23;
	resp = searchNode(&myTree, &searchData, compareInt);
	if (resp != NULL) printf("%d 찾음!!\n\n", resp->data);
	else printf("%d 못찾음!!\n\n", searchData);

	// 노드 삭제
	printf("Node 삭제...\n");
	deleteData = 7;
	resp=deleteNode(&myTree, &deleteData, compareInt); // 유형1 : 삭제할 노드의 오른쪽 자식이 없는 경우
	if (resp != NULL)
		printf("%d 삭제성공!\n", deleteData);
	else
		printf("%d 삭제 실패!!\n", deleteData);

	deleteData = 18;
	resp = deleteNode(&myTree, &deleteData, compareInt); // 유형2 : 삭제할 노드의 오른쪽 자식의 왼쪽 자식이 없는 경우
	if (resp != NULL)
		printf("%d 삭제성공!\n", deleteData);
	else
		printf("%d 삭제 실패!!\n", deleteData);

	//--테스트
	postorderTraverse(myTree.root, printInt); // 실제 첫번째 데이터노드의 주소 전달
	printf("\n\n");
	//--


	deleteData = 14;
	resp = deleteNode(&myTree, &deleteData, compareInt); // 유형3 : 그외 모든 경우
	if (resp != NULL)
		printf("%d 삭제성공!\n", deleteData);
	else
		printf("%d 삭제 실패!!\n", deleteData);
	
	deleteData = 123;
	resp = deleteNode(&myTree, &deleteData, compareInt); // 없는 데이터일 경우
	if (resp != NULL)
		printf("%d 삭제성공!\n", deleteData);
	else
		printf("%d 삭제 실패!!\n", deleteData);
	
	printf("\n삭제후의 tree내의 자료 출력 : ");
	inorderTraverse(myTree.root, printInt);  
	printf("\n\n");
	
	// Tree 소멸 (전체 모드 삭제)
	printf("Tree 전체 노드 삭제(Tree 소멸...)\n");
	destroyTree(&myTree, printInt);
	
	return 0;
}
//-------------------------------------
//   int type 보조 함수     
//-------------------------------------
/*--------------------------------------------------------------------------------------
함수명 및 기능: compareInt() – 전달인자로 넘겨진 int값 비교
전달인자: p1 - 첫번째 데이터의 주소
p2 - 두번째 데이터의 주소
리턴값: 첫번째 데이터가 크면 1, 같으면 0, 작으면 -1 리턴
--------------------------------------------------------------------------------------*/
int compareInt(DataType *p1, DataType *p2)
{    
	if (*p1 > *p2) return 1;
	else if (*p1 == *p2) return 0;
	else return -1;
}
/*--------------------------------------------------------------------------------------
함수명 및 기능: printInt() – 전달인자로 넘겨진 int값을 정해진 format으로 출력 함
전달인자: p - 출력할 정수의 주소
리턴값: 없음
--------------------------------------------------------------------------------------*/
void printInt(DataType *p)
{
	printf("%4d", *p);
}

/*--------------------------------------------------------------------------------------
 [실행 결과]

* 중위순회 결과 :    3   5   6   7  12  13  14  15  16  17  18  23  25

* 전위순회 결과 :   14  12   5   3   7   6  13  25  18  16  15  17  23

* 후위순회 결과 :    3   6   7   5  13  12  15  17  16  23  18  25  14

3 찾음!!

99 못찾음!!

19 못찾음!!

23 찾음!!

Node 삭제...
7 삭제성공!
18 삭제성공!
14 삭제성공!
123 삭제 실패!!

삭제후의 tree내의 자료 출력 :    3   5   6  12  13  15  16  17  23  25

Tree 전체 노드 삭제(Tree 소멸...)
   3   6   5  13  12  17  16  23  25  15

 ------------------------------------------------------------------------------------------ */
