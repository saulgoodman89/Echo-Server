#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <pthread.h>

#define BUFFER_SIZE 1024
#define BACK_LOG 5
#define PORT "9180"

void *conn_handler(void *);
void error_handling(char *message);
pthread_t pthread;
//pthread_t pthread[5];
int back_log_count = 0;

int main() {
	int server_sock = 0;
	int client_sock = 0;
	int client_addr_size = 0;

	/*	
		struct sockaddr_in{
    	sa_family_t		sin_family;		//주소체계
    	uint16_t		sin_port;		//16비트 PORT번호
		struct in_addr	sin_addr;		//32비트(4바이트) IP주소
    	char			sin_zero[8];	//사용되지 않음
		}


		struct  in_addr {
			u_long  s_addr;     // 32비트 IP 주소를 저장 할 구조체, network byte order
		};

	*/
	struct sockaddr_in server_addr;
	struct sockaddr_in client_addr;
	
	/*
		int socket(int domain, int type, int protocol);
		PF_INET // IPV4
		
		SOCKET_STREAM : tcp 
		SOCKET_DGRAM : udp
		SOCKET_RAW : raw 
	*/
	
	server_sock = socket(PF_INET , SOCK_STREAM , 0);
	
	if(server_sock==-1) {
		error_handling("소켓 생성 실패");	
	}

	memset(&server_addr,0,sizeof(server_addr));

	server_addr.sin_family = AF_INET;
	/*
		INADDR_ANY : 서버의 IP 주소를 자동으로 찾아 대입해주는 함수 
		0.0.0.0 으로 대기 중에 있다 클라이언트가 connect로 접속하면 소켓이 바인드 된다. 

		특정 IP를 지정하고자 한다면 
		inet_addr(ip주소) 추가 

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
		운영체제에 소켓이 사용자가 지정한 포트를 사용한다고 알리는 것. 
		bind 에러가 발생한다 -> 현재 지정된 포티가 사용되고 있다. 
		 
		성공시 0 , 실패시 -1 리턴 
		int bind (int __fd, __CONST_SOCKADDR_ARG __addr, socklen_t __len) (소켓의 파일 디스크립터 , 주소 정보 할당 , __addr 구조체의 크기)


	*/
	if(bind(server_sock,(struct sockaddr*)&server_addr, sizeof(server_addr)) == -1) {
		error_handling("socket bind failed");
	}

	/*
		listen : 클라이언트가 접속 요청을 기다리도록 설정 
		요청이 수신되거나 에러가 발생되는 경우 l
		int listen(int sock , int backlog)
		sock : 서버 소켓 
		backlog : 연결 대기 제한 수 
	*/
	if(listen(server_sock, BACK_LOG) == -1)  /* 연결 요청 대기 상태로 진입 */
			error_handling("listen() error");
	else  {
			puts("서버 동작 중 . . . . .  ");
		//	++back_log_count;
	}


	client_addr_size = sizeof(client_addr);		//client 주소 크기 초기화 
	
	printf("backlog count : %d \n",back_log_count);

	
	/*	연결 요청 수락 
		int accept(int sockfd, struct sockaddr *restrict addr,socklen_t *restrict addrlen); (소켓의 fd , 서버 주소 정보에 대한 포인터 , 서버주소 정보 포인터가 가르키는 구조체 크기)

	*/
	while (1) {
		client_sock = accept(server_sock, (struct sockaddr*)&client_addr, &client_addr_size);
		
		if(client_sock == -1)
			error_handling("accept() error");

	//	if(BACK_LOG > back_log_count) 
		pthread_create(&pthread,NULL,conn_handler , &client_sock);
	}

	//fputs(back_log_count,stdout);


}

void *conn_handler(void *fd) 
{
	int str_len = 0;
	int client_sock = *(int*)fd;	
	char message[BUFFER_SIZE] = "";
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
			printf("클라이언트에 전달 받은 메시지 : %s",message);
	}
	close(client_sock);       /* 연결 종료 */
	pthread_join(pthread,0);
//	--back_log_count;
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

