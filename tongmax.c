#include <stdio.h>
#include <malloc.h>
#define N 20
int main(){
	int *A,max;
	A =(int *)malloc ((N)*sizeof(int));
	
	for (int i = 0; i < N; ++i)
	{
		*(A+i)=-(i*i)-5*i+10;
	}

	int S=0;
	for (int i = 0; i < N; ++i)
	{
		S = S + *(A+i);
	}
	max=*(A+0);
	for (int i = 0; i < N; ++i)
	{
		if(*(A+i)>max){
			max = *(A+i);
		}
	}
	for (int i = 0; i < N; ++i)
	{
		printf("%d\n",*(A+i));
	}
	printf("tong la: %d\n",S);
	printf("Max la: %d\n",max );
	return 0;
}