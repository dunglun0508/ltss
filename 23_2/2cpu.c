#include <stdio.h>
#include <mpi.h>
#include <stdlib.h>
int main(int argc, char **argv){
    int i,rank, size;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD,&size);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Status thongbao;
    if(rank==0){
        int *A;
        A = (int *)malloc(5*sizeof(int));
        for(i = 0; i<5;i++) *(A+i)= i+1;
        printf("A:\n");
        for(i = 0; i<5;i++) printf("%d\t", *(A+i));
        printf("\n");
        printf("A[2]=%d\n", *(A+2));
        MPI_Send(A,5,MPI_INT,1,8,MPI_COMM_WORLD);
    }
    if (rank==1){
        int *B,*C;
        B= (int*)malloc(5*sizeof(int));
        C = (int*)malloc(5*sizeof(int));
        MPI_Recv(B,5, MPI_INT, 0, 8, MPI_COMM_WORLD,&thongbao);
        for (i=0;i<5;i++) *(C+i)=2* *(B+i);
        printf("C:\n");
        for (i=0;i<5;i++) printf("%d\t", *(C+i)); 
        printf("\n");
    }
    MPI_Finalize();
}
