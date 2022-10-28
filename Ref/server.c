#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>

#define BUFSIZE 1024
void error_handling(char *message);

int main(int argc, char **argv)
{
        int serv_sock;
        int clnt_sock;
        char message[BUFSIZE];
        int str_len;
        int clnt_addr_size;

        struct sockaddr_in serv_addr;
        struct sockaddr_in clnt_addr;
        /*
            리눅스/유닉스 시스템에서는 소켓의 통신 대상을 지정하기 위해 주소를 사용한다. 
            struct sockaddr_in {
                short    sin_family;          // 주소 체계:  항상 AF_INET
                u_short  sin_port;            // 16 비트 포트 번호, network byte order
                struct   in_addr  sin_addr;   //  in_addr :    sin_addr : 호스트 ip 주소 
                char     sin_zero[8];         // 전체 크기를 16 비트로 맞추기 위한 dummy
            };

            struct  in_addr {
                u_long  s_addr;     // 32비트 IP 주소를 저장 할 구조체, network byte order
            };
        */ 
 
        if(argc != 2) {
                printf("Usage : &s <port>\n", argv[0]);
                exit(1);
        }

        /*
            SOCKET_STREAM : tcp 
            SOCKET_DGRAM : udp
            SOCKET_RAW : raw 
        */
        serv_sock = socket(PF_INET, SOCK_STREAM, 0);    /* 서버 소켓 생성 */
        if(serv_sock == -1)
                error_handling("socket() error");
	    printf("serv-sock : %d" , serv_sock);
        memset(&serv_addr, 0, sizeof(serv_addr));
        /*
            memset 메모리를 특정 값으로 세팅 
            void* memset(void* ptr,int value,size_t num);
            void* ptr : 세팅 하고자 하는 메모리 주소 
            value : 메모리에 세팅하고자 하는 값 
            size_t num 

            memset이 성공하면 ptr을 반환하고 실패하면 NULL을 반환
        */
        serv_addr.sin_family = AF_INET;
        serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);  // htonl 
        printf("byte %d ", htonl(INADDR_ANY));
        serv_addr.sin_port = htons(atoi(argv[1]));


           /* 소켓에 주소 할당 */

        if(bind(serv_sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr))== -1)
	        error_handling("bind() error");

        if(listen(serv_sock, 5) == -1)  /* 연결 요청 대기 상태로 진입 */
            error_handling("listen() error");

        clnt_addr_size = sizeof(clnt_addr);

          

           /* 연결 요청 수락 */

        clnt_sock = accept(serv_sock, (struct sockaddr*)&clnt_addr, &clnt_addr_size);

        if(clnt_sock == -1)
            error_handling("accept() error");


           /* 데이터 수신 및 전송
          * 클라이언트가 EOF를 보낼 때까지 데이터를 받아서 서버 콘솔에 한번 출력해 주고
          * 클라이언트로 재전송해 주고 있다. */

           while((str_len = read(clnt_sock, message, BUFSIZE))!= 0) {
                   write(clnt_sock, message, str_len);
                    write(1, message, str_len);
           }

        close(clnt_sock);       /* 연결 종료 */
        return 0;
}

void error_handling(char *message)
{
        fputs(message, stderr);
        fputc('\n', stderr);
        exit(1);
}
