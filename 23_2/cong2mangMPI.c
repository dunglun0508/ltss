#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <malloc.h>

int main(int argc, char *argv[])
{
	int rank, size, i, *A, *B, *C, np;
    A = (int *) malloc(20*sizeof(int));
    B = (int *) malloc(20*sizeof(int));
    C = (int *) malloc(20*sizeof(int));
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	int mc, *Ac, *Bc, *Cc; mc = 20/size;
	Ac = (int *) malloc(mc*sizeof(int));
    Bc = (int *) malloc(mc*sizeof(int));
	Cc = (int *) malloc(mc*sizeof(int));
	MPI_Status thongbao;
    if(rank == 0) {
        for(i = 0;i<20;i++) 
    	{
    		*(A+i) = i + 1; 
    		*(B+i) = 2*(i+1); 
    	}

    	for (i = 0; i < mc; i++)
    	{
    		*(Ac+i) = *(A+i);
    		*(Bc+i) = *(B+i);
    	}
    	for (np = 1; np < size; np++)
    	{
    		
    		MPI_Send(A+mc*np, mc, MPI_INT,np,np,MPI_COMM_WORLD);
    		MPI_Send(B+mc*np, mc, MPI_INT,np,np,MPI_COMM_WORLD);
    	}
    }

    if(rank != 0){
        MPI_Recv(Ac, mc, MPI_INT, 0, rank, MPI_COMM_WORLD, &thongbao);
        MPI_Recv(Bc, mc, MPI_INT, 0, rank, MPI_COMM_WORLD, &thongbao);
    }
    for (i = 0; i < mc; i++){*(Cc+i) = *(Ac+i) + *(Bc+i);}
    if (rank == 2)
    {
    	for (int i = 0; i < mc; i++)
    	{
    		printf("%d\t", *(Cc+i));
    	}
    }
    MPI_Finalize();
	return 0;
}
