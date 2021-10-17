/*
*  시험 점수 구조체 동적 할당, 트리 검색
*/

#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>
#include <search.h>

struct student {
	char student_name[10];
	int mid;
	int final;
};

struct student *root = NULL;	// 루트 노드

// 학생 이름 중복 비교 함수
int compare(const void *cp1, const void*cp2) {
	return strcmp(((struct student *)cp1)->student_name,((struct student*)cp2)->student_name);
}

// twalk가 노드를 처음 만날때 출력
void print_node(const void *nodeptr, VISIT order, int level)
{
	if (order == preorder || order == leaf) {
		printf("이름 = %s, 중간점수 = %d 기말점수 = %d \n",(*(struct student **)nodeptr)->student_name,
								    (*(struct student **)nodeptr)->mid,
								    (*(struct student **)nodeptr)->final);
	}
}

void main() {
	int i, student_number;
	struct student **ret;
    
	printf("학생 수를 입력해주세요 : ");
	scanf("%d",&student_number);

	if(student_number <= 0 || student_number == '\0') {
		abort();
	}
    
	struct student *tree[student_number];

	for(i = 0; i<sizeof(tree) / sizeof(struct student *); i++) {
	
		tree[i] = malloc(sizeof(struct student));
		printf("트리에 추가할 학생 이름, 중간 점수, 기말 점수를 입력해주세요 : ");
		scanf("%s %d %d",tree[i]->student_name,&tree[i]->mid,&tree[i]->final); 
		
		// 트리에 학생 데이터 넣기
		ret = (struct student **) tsearch((void *) tree[i],(void **) &root, compare); // tsearch() : 이진 트리로부터 특정 항목 탐색
		printf("\"%s\" 님이 ", (*ret)->student_name);
		
		// tree[i]가 tsearch()로 탐색한 항목과 같으면 이미 존재, 다르면 추가되었다고 출력.
		if (*ret == tree[i])
			printf("트리에 추가되었습니다.\n\n");
		else
			printf("트리에 이미 존재합니다.\n\n");
	}
	
	twalk((void *) root, print_node);	// twalk() : 이진 트리 방문

	for (int i = 0; i < sizeof(tree) / sizeof(struct student *); i++) {
		free(tree[i]);
	}
}
