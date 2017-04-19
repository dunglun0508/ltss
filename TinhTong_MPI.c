#include <stdio.h>
#include <mpi.h>
#include <malloc.h>

#define N 20


int main(int argc, char *argv[])
{
	int *A,size,rank;
	
	A =(int *)malloc ((N)*sizeof(int));
	for (int i = 0; i < N; i++)
	{
		*(A+i) = -(i*i) - 5*i +10;
	}
 	MPI_Init(&argc, &argv);
 	MPI_Comm_size(MPI_COMM_WORLD, &size);
  	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  	int mc,*Ac, *tong,*max;
  	mc=N/size;
  	Ac =(int *)malloc ((mc)*sizeof(int));
  	tong =(int *)malloc ((size)*sizeof(int));
  	max =(int *)malloc ((size)*sizeof(int));
  	MPI_Scatter(A,mc,MPI_INT,Ac,mc,MPI_INT,0,MPI_COMM_WORLD);
  	int *tongc;

  	tongc =(int *)malloc (1*sizeof(int));
  	*(tongc+0)=0;
  	for (int i = 0; i < mc; ++i)
  	{
  		*(tongc+0)=*(tongc+0)+*(Ac+i);
  	}
  	int *maxc;
  	tongc =(int *)malloc (1*sizeof(int));
  	*(maxc+0)=*(Ac+0);
  	for (int i = 0; i < mc; ++i)
  	{
  		if(*(Ac+i)>*(maxc+0)){
  			*(maxc+0)=*(Ac+i);
  		}
  	}
  	MPI_Gather(tongc,1,MPI_INT,tong,1,MPI_INT,0,MPI_COMM_WORLD);
  	MPI_Gather(maxc,1,MPI_INT,max,1,MPI_INT,0,MPI_COMM_WORLD);
  	if (rank==0)
  	{
  		int tongtoancuc = 0;
  		for (int i = 0; i < size; ++i)
  		{
  			tongtoancuc = tongtoancuc + *(tong+i);
  		}
  		printf("Tong toan cuc la: %d\n",tongtoancuc );
  	}

  	

  	
  	MPI_Finalize();
	return 0;
}
