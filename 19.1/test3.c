#include <stdio.h>
#include <omp.h>
#define N 10
#define M 5
int main(){
	int i,  *A,  *B,  *C  ;
       int id;
	A = (int  *)malloc (N*sizeof(int));
	B = (int  *)malloc (N*sizeof(int));
       C = (int  *)malloc (N*sizeof(int));
       int start ;
       int stop ;
       int ns;
       omp_set_num_threads(M);
       #pragma omp parallel private(id, start, stop,i)
       {
              id = omp_get_thread_num();
              ns = N/M;
              start =id*ns;
              stop = (id+1)*ns-1;
              for(i=start;i<=stop;i++){
                *(A+i)=i;
                *(B+i)=i;
              }
              for(i=start;i<=stop;i++)
                *(C+i) = *(A+i)+*(B+i);       
       }

              printf("Mang A:\n");
              for(i=0;i<N;i++) printf("%d\t", *(A+i));
              printf("\n");
              printf("Mang B:\n");
              for(i=0;i<N;i++) printf("%d\t", *(B+i));
              printf("\n");
              printf("Mang C:\n");
              for(i=0;i<N;i++) printf("%d\t", *(C+i));
              printf("\n");
          return 0;

}
