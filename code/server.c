#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>

#define BUFFER_SIZE 1024
//#define PORT 9180 

void error_handling(char *message);
const char* PORT = "9180";
int main() {
	int server_sock;
	int client_sock;
	char message[BUFFER_SIZE];
	int str_len;
	int client_addr_size;

	/*	
		struct sockaddr_in{
    	sa_family_t		sin_family;		//주소체계
    	uint16_t		sin_port;		//16비트 PORT번호
		struct in_addr	sin_addr;		//32비트(4바이트) IP주소
    	char			sin_zero[8];	//사용되지 않음
		}

	*/
	struct sockaddr_in server_addr;
	struct sockaddr_in client_addr;
	

	server_sock = socket(PF_INET , SOCK_STREAM , 0);
	
	if(server_sock==-1) {
		error_handling("소켓 생성 실패");	
	}

	memset(&server_addr,0,sizeof(server_addr));

	server_addr.sin_family = AF_INET;
	/*
		INADDR_ANY : 서버의 IP 주소를 자동으로 찾아 대입해주는 함수 
		0.0.0.0 으로 대기 중에 있다 클라이언트가 connect로 접속하면 소켓이 바인드 된다. 
	*/
	server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	
	/*
		host byte order 데이터를 network byte order로 변경
		neywork byte order는 big endian이다. 

		atoi
		문자 스트링을 정수로 변환 
		atoi(PORT) : 9180
		htons(atoi(PORT)) : 56355
	*/
	server_addr.sin_port = htons(atoi(PORT));

	/*
		bind : IP / PORT 번호 할당  
		성공시 0 , 실패시 -1 리턴 
		int bind (int __fd, __CONST_SOCKADDR_ARG __addr, socklen_t __len) (소켓의 파일 디스크립터 , 주소 정보 할당 , __addr 구조체의 크기)

		파일 디스크립터 : OS가 파일이나 소켓에 할당한 정수 
		리눅스에서 사용하는 표준 입출력은 파일 디스크립터 값이 할당되어 있다. 

	*/
	if(bind(server_sock,(struct sockaddr*)&server_addr, sizeof(server_addr)) == -1) {
		error_handling("socket bind failed");
	}

	/*
		listen : 클라이언트가 접속 요청을 기다리도록 설정 
		int listen(int sock , int backlog)
		sock : 서버 소켓 
		backlog : 연결 대기 제한 수 
	*/
	if(listen(server_sock, 5) == -1)  /* 연결 요청 대기 상태로 진입 */
			error_handling("listen() error");

	client_addr_size = sizeof(client_addr);		//client 주소 크기 초기화 

	
	/*
		int accept(int sockfd, struct sockaddr *restrict addr,socklen_t *restrict addrlen); (소켓의 fd , 서버 주소 정보에 대한 포인터 , 서버주소 정보 포인터가 가르키는 구조체 크기)

	*/
	client_sock = accept(server_sock, (struct sockaddr*)&client_addr, &client_addr_size);

	if(client_sock == -1)
		error_handling("accept() error");


	/*
		read : 서버 소켓에서 버퍼 사이즈 만큼 메시지를 읽어온다. 
		int ssize_t read(int fd, void *buf, size_t count);	(client 소켓의 fd , 읽은 데이터가 저장될 변수 , 버퍼 사이즈)

	*/
	while((str_len = read(client_sock, message, BUFFER_SIZE))!= 0) {

					/*
						write : 서버소켓에 메시지를 보낸다. 
						ssize_t write(int fd, const void *buf, sizr_t count);	(연결된 소켓 fd , 데이터가 저장된 버퍼 , 메시지 크기)
						ssize_t : signed int 

					*/
                  	write(client_sock, message, str_len);
                    write(1, message, str_len);		//1이 어떤 의미인지 확인 필요
	}

	close(client_sock);       /* 연결 종료 */
}

void error_handling(char *message)
{
		/*
			fputs : 파일에 문자열을 쓰는 함수 
			int fputs(const char* str, FILE* pFile); (파일에 쓸 문자열 , 파일 포인터)
			stderr : 표준 에러 
		*/
        fputs(message, stderr);

		/*
			fputc : 파일에 문자를 하나씩 쓰는 함수 
			int fputc(int c, FILE* pFile);  (넣을 문자 or 숫자 / 표준 에러)
		*/
        fputc('\n', stderr);
        exit(1);
}

