/*
* my_perror() 함수 구현
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

void my_perror(char *front_str)
{
	if (front_str == NULL) {
		printf("%s\n", strerror(errno));
	}
	else {
		printf("%s: %s\n", front_str, strerror(errno));
	}
	return;
}

void main(int argc, char *argv[])
{
	FILE *f;
	
	// 명령행 인자가 주어지지 않은 경우 예외처리
	if(argc < 2) {
		printf("Usage: perror_use file_name\n");
		exit(1);
	}
	
	if((f=fopen(argv[1], "r")) == NULL) {
		// perror 라이브러리 함수 사용
		perror(NULL);
		perror("fopen");
		
		// my_perror 사용자 정의 함수 사용
		my_perror(NULL);
		my_perror("fopen");
		
		exit(1);
	}
	
	printf("Open a file \%s\".\n", argv[1]);
	
	fclose(f);
	return;
}
