/*
* my_assert() 함수 구현
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

void my_assert(int num, char *filename)
{
	char *executable_file = strtok(filename, "./");
	if (!((num >= 0) && (num <= 100))) {
		fprintf(stderr, "%s: %s:%d: %s: Assertion '((num >= 0) && (num <= 100))' failed. "
				,executable_file,__FILE__,__LINE__,__FUNCTION__);
		abort();
	}
}

void foo(int num, char *filename)
{
	// assert 라이브러리 함수 사용
	assert((num >= 0) && (num <= 100));
	
	// my_assert 사용자 정의 함수 사용
	my_assert(num, filename);
	
	printf("foo: num = %d\n", num);
}

void main(int argc, char *argv[])
{
	int num;
	
	// 명령행 인자가 주어지지 않은 경우 예외 처리
	if (argc < 2) {
		fprintf(stderr, "Usage: assert_test aNumber\n(0 <= aNumber <= 100)\n");
		// stderr : 표준에러출력장치 -> 버퍼링 없이 바로 출력되므로 문제가 생겼을 경우 즉시 출력 가능
		exit(1);
	}
	
	num = atoi(argv[1]); // atoi() : 문자열을 정수로 변환
	foo(num, argv[0]);
}
