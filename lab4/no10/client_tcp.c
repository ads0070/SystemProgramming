#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/time.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <time.h>

#define MAXLINE     1000
#define NAME_LEN    20

char *EXIT_STRING = "exit";

int tcp_connect(int af, char *servip, unsigned short port);
void errquit(char *mesg) { perror(mesg); exit(1); }

int main(int argc, char *argv[]) {
	char bufname[NAME_LEN];	//name
	char bufmsg[MAXLINE];	//message
	char bufall[MAXLINE + NAME_LEN];
	int maxfdp1;	//max socket descriper
	int s;		//socket
	int namelen;
	fd_set read_fds;
	time_t ct;
	struct tm tm;

	if (argc != 4) {
		printf("manual : %s sever_ip  port name \n", argv[0]);
		exit(0);
	}

	s = tcp_connect(AF_INET, argv[1], atoi(argv[2]));
	if (s == -1)
		errquit("tcp_connect fail");

	puts("connect success.");
	maxfdp1 = s + 1;
	FD_ZERO(&read_fds);

	while (1) {
		FD_SET(0, &read_fds);
		FD_SET(s, &read_fds);
		if (select(maxfdp1, &read_fds, NULL, NULL, NULL) < 0)
			errquit("select fail");
		if (FD_ISSET(s, &read_fds)) {
			int nbyte;
			if ((nbyte = recv(s, bufmsg, MAXLINE, 0)) > 0) {
				bufmsg[nbyte] = 0;
				write(1, "\033[0G", 4);
				printf("%s", bufmsg);
				fprintf(stderr, "%s>", argv[3]);

			}
		}
		if (FD_ISSET(0, &read_fds)) {
			if (fgets(bufmsg, MAXLINE, stdin)) {
				
				fprintf(stderr, "\033[1A");
				ct = time(NULL);
				tm = *localtime(&ct);
				sprintf(bufall, "[%02d:%02d:%02d]%s>%s", tm.tm_hour, tm.tm_min, tm.tm_sec, argv[3], bufmsg);
				if (send(s, bufall, strlen(bufall), 0) < 0)
					puts("Error : Write error on socket.");
				if (strstr(bufmsg, EXIT_STRING) != NULL) {
					puts("Good bye.");
					close(s);
					exit(0);
				}
			}
		}
	} // end of while
}

int tcp_connect(int af, char *servip, unsigned short port) {
	struct sockaddr_in servaddr;
	int  s;
	// create socket
	if ((s = socket(af, SOCK_STREAM, 0)) < 0)
		return -1;

	bzero((char *)&servaddr, sizeof(servaddr));
	servaddr.sin_family = af;
	inet_pton(AF_INET, servip, &servaddr.sin_addr);
	servaddr.sin_port = htons(port);

	// connect response
	if (connect(s, (struct sockaddr *)&servaddr, sizeof(servaddr))
		< 0)
		return -1;
	return s;
}
