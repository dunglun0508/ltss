// VietCT Matrix Mul
// A[M][N]*B[N][P]=C[M][P]
#include <stdio.h>
#define M 4
#define N 4
#define P 4
int main(){
	int i,j,k,*A,*B,*C;
	int sum =0;
	A=(int *)malloc(M*N*sizeof(int));
	B=(int *)malloc(N*P*sizeof(int));
	C=(int *)malloc(M*P*sizeof(int));
	printf("Ma tran A:\n");
        for(i=0;i<M;i++)
            for(j=0;j<N;j++)
            	if(i==j)  *(A+i*N+j)=1;
            	else *(A+i*N+j)=0;
            

         for(i=0;i<M;i++){
            for(j=0;j<N;j++)
            	printf("%d  " ,*(A+i*N+j));

            	printf("\n");
            }
         printf("\n");
    printf("Ma tran B:\n");

        for(i=0;i<N;i++)
            for(j=0;j<P;j++)
            	*(B+i*P+j)= i*P+j;

            

         for(i=0;i<N;i++){
            for(j=0;j<P;j++)
            	printf("%d  " ,*(B+i*P+j));

            	printf("\n");
            }

           for(i=0;i<M;i++)
        {
            for(j=0;j<P;j++)
            {
               for(k=0;k<P;k++)
                 sum+=*(A+i*N+k)**(B+k*P+j);
                 *(C+i*P+j)=sum;
            sum=0;
            }
        }
         printf("\n");

    printf("Ma tran C:-\n");
        for(i=0;i<M;i++)
        {
            for(j=0;j<P;j++)
                printf("%d\t",*(C+i*P+j));
            printf("\n");
        }


            return 0;
}
