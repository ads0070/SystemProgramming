#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>
#include <math.h>

#define PASSWORDSIZE 12

typedef unsigned long long int tick64_t;
typedef unsigned long int tick32_t;

tick32_t GetTickCount()
{
	tick32_t tick = 0ul;
#if defined(WIN32) || defined(WIN64)
	tick = GetTickCount();
#else
	struct timespec ts;
	clock_gettime(CLOCK_MONOTONIC, &ts);
	tick = (ts.tv_sec*1000ul) + (ts.tv_nsec/1000ul/1000ul);
#endif
	return tick;
}

int main(void) {
	int fd, start;
	int nread, cnt=0, cnt1=0, errcnt=0;
	double typing_msec, typing_sec, typing_per_sec;
	char ch, text[] = {"The magic thing is that you can change it."}, ch1, text1[] = {"Dokdo is Korean territory."};

 	struct termios init_attr, new_attr;
 	fd = open(ttyname(fileno(stdin)), O_RDWR); tcgetattr(fd, &init_attr);
 
 	new_attr = init_attr;
 	new_attr.c_lflag &= ~ICANON;
 	new_attr.c_lflag &= ~ECHO; /* ~(ECHO | ECHOE | ECHOK | ECHONL); */
 	new_attr.c_cc[VMIN] = 1;
 	new_attr.c_cc[VTIME] = 0;
 
 	if (tcsetattr(fd, TCSANOW, &new_attr) != 0) {
 		fprintf(stderr, "터미널 속성을 설정할 수 없음.\n");
	}
 	printf("다음 문장을 그대로 입력하세요.\n%s\n", text);
 	start = GetTickCount();

	while ((nread=read(fd, &ch, 1)) > 0 && ch != '\n') {
		if (ch == text[cnt++])
			write(fd, &ch, 1);
		else {
			write(fd, "*", 1); errcnt++;
		}
	}
 
	printf("\n다음 문장을 그대로 입력하세요.\n%s\n", text1);
 
	while ((nread=read(fd, &ch1, 1)) > 0 && ch1 != '\n') {
		if (ch1 == text1[cnt1++])
			write(fd, &ch1, 1);
		else {
			write(fd, "*", 1);
			errcnt++;
 		}
	}
 
	typing_msec = GetTickCount() - start;
 
	typing_sec = fmod((typing_msec/1000), 60); 
	typing_per_sec = (sizeof(text) / sizeof(int)) / typing_sec; 
 
	printf("\n걸린 시간: %.3lf초\n", typing_sec); 
	printf("분당 %d타를 치셨습니다.\n\n", (int)(typing_per_sec*60));
	printf("타이핑 오류의 횟수는 %d\n", errcnt);
	tcsetattr(fd, TCSANOW, &init_attr);
	close(fd);
}
