#include<stdio.h>


void changePtr(int** ptr1 , int** ptr2) {

	*ptr1 = *ptr2;
	*ptr2 = *ptr1;
}

int main() {
	int def1 = 10;
	int def2 = 20;
	int* a = &def1;
	int* b = &def2;

	printf("a,b 출력  A : %d   B : %d \n",*a , *b);
	
	changePtr(&a,&b);

	printf("### a,b 출력  A : %d   B : %d \n",*a , *b);

	//http://eirenehue.egloos.com/v/1000688
}


/*
int global_val = 30;

void call_by_value(int *val)
{
	        val = &global_val;
}

void call_by_refer(int **ref)
{
	        *ref = &global_val;
}

int main()
{
	        int local_val = 10;
			int *value = &local_val;
			int *refer = &local_val;

			printf("before : *value=%d, *refer=%d\n", *value, *refer);
			call_by_value(value);	
			call_by_refer(&refer);	//포인터 변수의 주소값 , *refer에 &global_val를 넣게되면 refer값이 변경된다. 
			printf("after  : *value=%d, *refer=%d\n", *value, *refer);
}*/



/*
void call_by_value(int val)
{
	        val = 20;
}

void call_by_refer(int *ref)
{
	        *ref = 20;
}

int main()
{
	        int value = 10;
			int refer = 10;

			printf("before : value=%d, refer=%d\n", value, refer);
			call_by_value(value);
			call_by_refer(&refer);
			printf("after  : value=%d, refer=%d\n", value, refer);
}*/
