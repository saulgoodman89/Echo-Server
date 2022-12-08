#include<stdlib.h>
#include<stdio.h>
#include<string.h>
char access;
char buffer[4];
int keg(const char *cs, const char *ct);

int main(int argc, char **argv)
{
	char *A = argv[1];
	char *B = "pass";
	access = 'n';
	strcpy(buffer,A); 
	
	if(strcmp(buffer,B)==0){
	access = 'y';
	}
	
	if(access == 'y'){
		printf("\nThis is a secret \n");
	}
	else
	{
		printf("\nAccess Denied \n");
	}


	if(strncmp(buffer,B,5)==0){
		printf("###");
		access = 'y';
	}
	
	if(access == 'y'){
		printf("\n strncmp This is a secret \n");
	}
	else
	{
		printf("\n strncmp Access Denied \n");
	}

      
      if(memcmp(buffer,B,5)==0){
            printf("###");
            access = 'y';
	}
	
	if(access == 'y'){
		printf("\n memcmp This is a secret \n");
	}
	else
	{
		printf("\n memcmp Access Denied \n");
	}
	

	

	const char* str1 = "BlockDMask";
	const char* str2 = "Block";
	const char* str3 = "BlockDMask";
	const char* str4 = "BlockFMask";
	const char* str5 = "BlockAMask";
	/*
	printf("strcmp(str1,str2) strcmp = %d \n",memcmp(str1,str2,7));	//68
	printf("strcmp(str1,str3) strcmp = %d \n",memcmp(str1,str3,7));	//0  
	printf("strcmp(str1,str4) strcmp = %d \n",memcmp(str1,str4,7));	//-2
	printf("strcmp(str1,str5) strcmp = %d \n",memcmp(str1,str5,7));	//3
	*/

	/* strcmp
	두 문자열이 같으면 return 0 , 
	다르면 문자열 s1>s2 면 s1 마지막 문자의 아스키 코드 값을 리턴
			s1<s2면 s1과 s2 마지막 문자열의 아스키 코드 값이 차를 리턴  

	비교하고자 하는 기준이 없어 문자열 끝을 확인하기 위해 '\0' 문자를 사용 



	printf("strcmp(str1,str2) strcmp = %d \n",strcmp(str1,str2));	//68  D : 68
	printf("strcmp(str1,str3) strcmp = %d \n",strcmp(str1,str3));	//0	  
	printf("strcmp(str1,str4) strcmp = %d \n",strcmp(str1,str4));	//-2  D<F  D : 68 / F : 70
	printf("strcmp(str1,str5) strcmp = %d \n",strcmp(str1,str5));	//3  D>A  68 >65 
	//https://blockdmask.tistory.com/391

	strcmp로 비교 시 
	./global_buffer_overflow abcyyyyyyyyyy 
	This is a secre

	if(strcmp(buffer,B)==0){
		access = 'y';
	}
	
	if(access == 'y'){
		printf("\nThis is a secret");
	}
	else
	{
		printf("\nAccess Denied");
	}
	*/


	/*
		int strncmp(const char* str1, const char* str2, size_t n);
		str1 : 비교할 문자열 1
		str2 : 비교할 문자열 2
		n : 비교할 문자열 길이
		str1 , str2를 n번째 까지 비교한다. 

	
	printf("strcmp(str1,str2) strcmp = %d \n",strncmp(str1,str2,7));	//68
	printf("strcmp(str1,str3) strcmp = %d \n",strncmp(str1,str3,7));	//0  
	printf("strcmp(str1,str4) strcmp = %d \n",strncmp(str1,str4,7));	//-2
	printf("strcmp(str1,str5) strcmp = %d \n",strncmp(str1,str5,7));	//3
	
	

	printf("buffer : %s\n",buffer);
	printf("B : %s \n",B);

	if(strncmp(buffer,B,5)==0){
		printf("###");
		access = 'y';
	}
	
	if(access == 'y'){
		printf("\nThis is a secret \n");
	}
	else
	{
		printf("\nAccess Denied \n");
	}
	*/

	/*
		memcmp
		int memcmp(const void *s1, const void *s2, size_t n);
		s1 : 비교할 첫 번째 주소 
		s2 : 비교할 두 번째 주소 
		n : 비교할 바이트 수 

		두 메모리 블록이 정확히 같다면 0을 리턴 , 다르다면 s1과 s2의 크기에 따라 -1 혹은 1 리턴 
		n값을 0으로 두면 무조건 0을 리턴한다. 
	
	

	if(memcmp(buffer,B,0) == 0) {
		printf("memcmp == 0 \n");
	}else {
		printf("memcmp != 0 \n");
	}*/



return 0;

}

