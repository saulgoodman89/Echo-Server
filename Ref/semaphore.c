#include<stdio.h>
#include<pthread.h>
#include<unistd.h>
#include<semaphore.h>

sem_t semaphore;
int common_value = 0;

void* t_main_plus(void *arg);
void* t_main_minus(void *arg);

int main() {

	pthread_t thread1 , thread2 , thread3 , thread4;

	/*
	 *    sem_init(sem_t *sem , int pshared , unsigned int value);
	 *    
	 *    sem_t *sem 초기화할 세마포어 객체 
	 *    
	 *    pshared
	 *	  0 : thread간 공유 , 1 : process간 공유 
	 *    value 
	 *    세마포어 카운트를 몇으로 초기화 할지 지정
	 *
	 *    return 0 : success 
	 *    return -1 : error 
	 */
	int sem = sem_init(&semaphore,0,1);
	printf("sem : %d \n\n",sem);

	pthread_create(&thread1, NULL, t_main_plus, NULL); // 쓰레드 생성
	pthread_create(&thread2, NULL, t_main_minus, NULL); // 쓰레드 생성
	pthread_create(&thread3, NULL, t_main_plus, NULL); // 쓰레드 생성
	pthread_create(&thread4, NULL, t_main_minus, NULL); // 쓰레드 생성
	
	pthread_join(thread1,NULL);
	pthread_join(thread2,NULL);
	pthread_join(thread3,NULL);
	pthread_join(thread4,NULL);
	
	sleep(7);
	sem_destroy(&semaphore);

}

void* t_main_plus(void *arg)
{
	    int i = 0;		 
		printf("t_main_plus 쓰레드가 연산을 시작합니다. \n");
			 
		
		/*	int sem_wait(sem_t *sem);
		 *	 세마포어 값이 1 이상이면 그 값을 감소시키고 즉시 함수를 빠져나가게 한다.
		 *	 세마포어 값이 0이라면 값이 1 이상이 되ㅣ거나 인터럽트 호출이 있지 않는 이상 현재 지점에서 작업 대기
		 *	 성공이면 0을 리턴 , 에러 발생 시 세마포어 카운트를 감소 시키지 않고 -1을 리턴  
		 */

	sem_wait(&semaphore);
		sleep(10000);
		for(i=0; i<1000000; i++) 
			common_value+=1;
		
	/*
	 * int sem_post(sem_t *sem);
	 * 세마포어 값을 증가시킨다. 
	 * 증가시킨 값이 1이상이 되면 sem_wait에 의해 대기 중인 프로세스 혹인 쓰레드를 깨운다.
	 *
	 *
	 */
	sem_post(&semaphore);				 
		printf("t_main_plus 쓰레드가 종료됩니다.\n");
		return NULL;
}
 
 
void* t_main_minus(void *arg)
{
	    int i = 0; 
		printf("t_main_minus 쓰레드가 연산을 시작합니다. \n");	 
		
		sem_wait(&semaphore);

		for(i=0; i<1000000; i++)
			common_value-=1;
		
		sem_post(&semaphore);		 
		printf("t_main_minus 쓰레드가 종료됩니다.\n");
		return NULL;
}

