#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>

#define BUFFER_SIZE 1024
const char* PORT = "9180";

void error_handling(char *message);

int main() {
    char ipaddr[15];
    int sock;
    struct sockaddr_in server_addr;
    char message[BUFFER_SIZE];
    int str_len;
    

    printf("IP 주소를 입력하세요 : ");
    scanf("%s :", ipaddr);


    sock = socket(PF_INET, SOCK_STREAM, 0);   /* 서버 접속을 위한 소켓 생성 */

    if(sock == -1)
            error_handling("socket() error");

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr(ipaddr);
    server_addr.sin_port = htons(atoi(PORT));

    
    /*
        connect : 서버로 접속 요청 
        int connect(int sockfd, const struct sockaddr *serv_addr, socklen_t addrlen)  (서버 소켓 fd , 서버 주소 정보 구조체 포인터 , 서버 구조 정보 포인터 구조체 크기)
    */
    if( connect(sock, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1) 
            error_handling("connect() error");

    while(1) {
        /* 메시지 입력 전송*/
        fputs("전송할 메시지를 입력하세요(q to quit) : ", stdout);

        /*
            fgets : 파일에서 문자열을 가져오는 함수 
        */  
        fgets(message, BUFFER_SIZE, stdin);

        if(!strcmp(message, "q\n")) // strcmp : 두 개의 문자열을 비교하여 문자열이 같다면 0을 리턴 , 다르면 이외의 값 
                break;

        write(sock, message, strlen(message));

        /* 메시지 수신 출력 */

        str_len = read(sock, message, BUFFER_SIZE-1);
        message[str_len] = 0;
        printf("서버로부터 전송된 메시지 : %s \n", message);
    }
    close(sock);
}

void error_handling(char *message)
{
        fputs(message, stderr);
        fputc('\n', stderr);
        exit(1);
}

