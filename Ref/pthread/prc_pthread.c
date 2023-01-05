#include<stdio.h>
#include<pthread.h>

/*
    pthread_create 직후 pthread_join을 호출하지만 쓰레드가 바로 멈추지 않고 루틴을 다 실행한 후 종료된다. 
*/
void *threadRoutine(void *arg) {
    for(int i=0; i<10; i++) {
        printf("i : %d \n",i);
        sleep(2);
    }
    return NULL;
}

int main() {  
    pthread_t threadID;
    /*
        int pthread_create(pthread_t *thread, const pthread_attr_t *attr, void *(*start_routine)(void*), void *arg)
        pthread_t *thread : 스레드 아이디 
        const pthread_attr_t *attr : 스레드의 특성 정의.
        보통 NULL을 지정하고 
        
        void *(*start_routine)(void*) : 스레드에서 실행할 함수 포인터 

        void *arg : start_routine에 전달될 인자. 
    */
    pthread_create(&threadID, NULL , threadRoutine, NULL);

    /*
        thread가 끝날 때 까지 기다렸다가 종료 
        int pthread_join(pthread_t thread, void **retval)
        pthread_t thread : thread_id
        void **retval : pthread_create에서 start_routine의 리턴 값 저장 

    */

    int joinNum = pthread_join(threadID, NULL);
    printf("pthread_join Num : %d ",joinNum);
    return 0;
}