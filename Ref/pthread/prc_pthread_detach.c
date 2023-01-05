#include<stdio.h>
#include<pthread.h>

void *threadRoutine(void *arg) {
    for(int i=0; i<10; i++) {
        printf("i : %d \n",i);
        sleep(2);
    }
    return NULL;
}

int main() {  
    pthread_t threadID;

    pthread_create(&threadID, NULL , threadRoutine, NULL);

    /*
        join처럼 쓰레드가 끝나기를 기다리지 않고 바로 종료. 
        int pthread_detach(pthread_t thread)
        성공 시 0을 리턴 
    */
    int detachNum = pthread_detach(threadID);
    printf("pthread_detach Num : %d \n",detachNum);
    return 0;
}