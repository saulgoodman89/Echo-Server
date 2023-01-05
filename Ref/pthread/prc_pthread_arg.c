#include<stdio.h>
#include<pthread.h>

void *threadRoutine(void *arg) {
    char *message = (char *)arg;
    printf("message : %s \n",message);
    for(int i=0; i<10; i++) {
        printf("i : %d \n",i);
        sleep(2);
    }
    return NULL;
}

int main() {  
    pthread_t threadID;
   char message[10] = "hello";
   pthread_create(&threadID, NULL , threadRoutine, (void*)message);

    int joinNum = pthread_join(threadID, NULL);
    return 0;
}