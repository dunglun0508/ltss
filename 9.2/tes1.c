// VietCT Matrix Mul
// A[M][N]*B[N][P]=C[M][P]
#include <stdio.h>
#include <omp.h>
#include <stdlib.h>
#define M 4
#define N 4
#define P 4

int main(){
	int i,j,k,*A,*B,*C;
	int sum =0;
    int id , i1, i2;
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
    omp_set_num_threads(4);
    #pragma omp parallel private(id,i,j,k,i1,i2,sum)
    {
        id = omp_get_thread_num();
        i1 = (P/4)*id;
        i2 = (P/4)*(id+1);
    
           for(i=0;i<M;i++)
        
            for(j=i1;j<i2;j++)
            {
                sum=0;
               for(k=0;k<P;k++)
                 sum+=*(A+i*N+k)**(B+k*P+j);
                 *(C+i*P+j)=sum;
            }
        
    
    }

    printf("Ma tran C:-\n");
        for(i=0;i<M;i++)
        {
            for(j=0;j<P;j++)
                printf("%d\t",*(C+i*P+j));
            printf("\n");
        }
    

            return 0;
}
