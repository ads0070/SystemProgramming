/*
* 동적 메모리 할당
*/

#include <stdio.h>
#include <stdlib.h>

void main()
{
	int col, row, num = 100;
	int i = 0, j = 0, k = 0;
	
	printf("행의 크기(세로), 열의 크기(가로)를 입력하세요: ");
	scanf("%d %d", &row, &col);
	
	// 배열의 세로
	int **arr1 = malloc(sizeof(int *) * row);	// 이중 포인터에 (int 포인터 크기 * row)만큼 동적 메모리 할당
	int **arr2 = malloc(sizeof(int *) * row);
	
	// 배열의 가로	
	for (i = 0; i < row; i++) {
		arr1[i] = malloc(sizeof(int) * col);	// (int의 크기 * col)만큼 동적 메모리 할당
		arr2[i] = malloc(sizeof(int) * col);
	}
	
	// 두 개의 행렬 각 요소에 값 할당
	for (i = 0; i < row; i++) {
		for (j = 0; j < col; j++) {
        		arr1[i][j] = i + j;
        		arr2[i][j] = num;
        		num--;
        	}
	}
	
	// 행렬A와 행렬B 출력
	printf("\n행렬 A와 행렬 B\n");
	for (i = 0; i < row; i++) {
		for (j = 0; j < col; j++) {
			printf("%d ", arr1[i][j]);
		}
		printf("   ");
		for (k = 0; k < col; k++) {
			printf("%d ", arr2[i][k]);
		}
		printf("\n");
	}
	
	printf("----------------\n");
	printf("두 행렬의 합\n");
	printf("----------------\n");
	
	// 행렬 A와 행렬 B를 더한 결과 출력
	for (i = 0; i < row; i++) {
		for (j = 0; j < col; j++) {
			printf("%d ", arr1[i][j] + arr2[i][j]);
		}
		printf("\n");
	}
	
	free(arr1[0]);	// arr1 배열의 가로 공간 메모리 해제
	free(arr1);	// arr1 배열의 세로 공간 메모리 해제
	free(arr2[0]);	// arr2 배열의 가로 공간 메모리 해제
	free(arr2);	// arr2 배열의 세로 공간 메모리 해제
}
