#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>

#define BUFFER_SIZE 1024
#define PORT 9180 

void error_handling(char *message);

int main() {
	int server_sock;
	int client_sock;
	char message[BUFFER_SIZE];
	int str_len;
	int client_addr_size;

	struct sockaddr_in server_addr;
        struct sockaddr_in client_addr;
	

	server_sock = socket(PF_INET , SOCK_STREAM , 0);
	
	if(server_sock==-1) {
		error_handling("소켓 생성 실패");	
	}

	memset(&server_addr,0,sizeof(server_addr));
	
}

void error_handling(char *message)
{
        fputs(message, stderr);
        fputc('\n', stderr);
        exit(1);
}

