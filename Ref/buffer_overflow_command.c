/*
#include<stdio.h>
#include<stdio.h>


int main() {
    	   char name[200];
        printf("What is your name?\n");
        scanf("%s", name);
        bo(name, "date");

}

int bo(char *name, char *cmd){
        char c[40];
        char buffer[40];
        printf("Name buffer address:    %x\n", buffer);
        printf("Command buffer address: %x\n", c);
        strcpy(c, cmd);
        strcpy(buffer, name);
        printf("Goodbye, %s!\n", buffer);
        printf("Executing command: %s\n", c);
        fflush(stdout);
        system(c);
}*/


#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int bo(char *name, char *cmd){
        char c[40], n[40];
        printf("Name is at %p; command is at %p\n", n, c);
        strcpy(c, cmd);
        strcpy(n, name);
        printf("Goodbye, %s!\n", n);
        printf("Executing command: %s\n", n);
        fflush(stdout);
        system(c);
}

int main(){
        char name[200];
        printf("What is your name?\n");
        scanf("%s", name);
        bo(name, "date");
}
