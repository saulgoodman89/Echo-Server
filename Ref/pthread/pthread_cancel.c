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
    int pthread_setcancelstate(int state, int *oldstate)
    pthread_cancel() 요청을 받았을 때 어떻게 처리할지 cancel state를 set하는 함수 
    PTHREAD_ENABLE
    PTHREAD_DISABLE 이 있다.

    PTHREAD_CANCEL_ENABLE : 취소 상태를 활성화 시킴.
    PTHREAD_CANCEL_DISABLE : 취소 상태를 비활성화 시킴.

    */

    
    /*
        int pthread_cancel (pthread_t tid);
        thread를 종료 요청.
        성공 시 0을 리턴  
    */
    int cancelSateNum = pthread_setcancelstate(PTHREAD_CANCEL_DISABLE,PTHREAD_CANCEL_ENABLE);
    printf("setcancelstate : %d",cancelSateNum);
    int cancelNum = pthread_cancel(threadID);
    printf("cancel Num : %d",cancelNum);
    return 0;
}