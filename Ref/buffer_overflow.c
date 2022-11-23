#include<stdio.h>
#include<string.h>
int main(void) {
    /*
    const char *inputString = "LiternalString_XYZ";
    
    
 
	strncmp 일정 길이 만큼 문자열 A,B를 비교 
	두 문자열이 같으면 return 0 , 아니면 0이 아닌 값 
    
    int ncmp = strncmp(inputString, "LiternalString", strlen("LiternalString_XYZ"));
    printf("strncmp : %d\n", ncmp); // prints 0.

    int cmp = strcmp(inputString, "LiternalString");
    printf("strcmp : %d\n", cmp); // prints non-zero.
    */

    char buff[15];
    int pass = 0;
    char tempbuff[15];

    printf("\n Enter a password of length between 1 and 15 characters : \n");
    gets(buff);

    printf("\n Enter your password : \n");
    gets(tempbuff);

    if(strcmp(tempbuff, buff))
    {
        printf ("\n Wrong Password \n");
    }
    else
    {
        printf ("\n Correct Password \n");
        pass = 1;
    }

    if(pass)
        printf ("\n Root privileges given to the user \n");

    return 0;


}
