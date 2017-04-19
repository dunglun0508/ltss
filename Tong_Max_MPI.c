#include <stdio.h>
#include <malloc.h>
#include <mpi.h>
#define  N       20
//==================================
main(int argc, char *argv[])
{
 int i,Nc, NP, rank;
 int *A, *Ac, *Tong, *Max;
  MPI_Status status;
  MPI_Init (&argc, &argv);
  MPI_Comm_size (MPI_COMM_WORLD, &NP);
  MPI_Comm_rank (MPI_COMM_WORLD, &rank);
//==================================
  Nc = N/NP;
//==================================
  A  = (int *) malloc (N*sizeof(int));
  Ac = (int *) malloc (Nc*sizeof(int));
  Tong = (int *) malloc (NP*sizeof(int));
  Max  = (int *) malloc (NP*sizeof(int));  
//==================================
  if (rank==0){
  	for (  i = 0 ; i < N ; i++ ){ 
      *(A+i) = -i*i - 5*i + 10;
      printf("%d :",*(A+i));
    }
    printf("\n");
  }
//==================================
  if (rank==0){
    int Tongtest = 0;
    for (  i = 0 ; i < N ; i++ ) 
        Tongtest = Tongtest + *(A+i);
    printf("Tong C = %d\n", Tongtest);

    int Maxtest = *(A+0);
    for (  i = 1 ; i < N ; i++ )
      if (*(A+i) > Maxtest)
        Maxtest = *(A+i);
    printf("Max C = %d\n", Maxtest);  
  }
//==================================
  MPI_Scatter(A,Nc,MPI_INT,Ac,Nc,MPI_INT,0,MPI_COMM_WORLD);
//==================================  
    int *TongLocal;
    TongLocal = (int *) malloc (1*sizeof(int));
    *(TongLocal +0)= 0;
    for (  i = 0 ; i < Nc ; i++ ) 
        *(TongLocal +0) = *(TongLocal +0) + *(Ac+i);

    int *MaxLocal;
    MaxLocal = (int *) malloc (1*sizeof(int));
    *(MaxLocal + 0)= *(Ac+0);
    for (  i = 1 ; i < Nc ; i++ )
      if (*(Ac+i) > *(MaxLocal + 0))
        *(MaxLocal + 0) = *(Ac+i);
//================================== 
  MPI_Gather(TongLocal,1,MPI_INT,Tong,1,MPI_INT,0,MPI_COMM_WORLD);
  MPI_Gather(MaxLocal,1,MPI_INT,Max,1,MPI_INT,0,MPI_COMM_WORLD);
//==================================  
if (rank==0){
    int TongToancuc = 0;
    for (  i = 0 ; i < NP ; i++ ) 
        TongToancuc = TongToancuc + *(Tong+i);
    printf("Tong MPI = %d\n", TongToancuc);

    int MaxToancuc = *(Max+0);
    for (  i = 1 ; i < NP ; i++ )
      if (*(A+i) > MaxToancuc)
        MaxToancuc = *(Max+i);
    printf("Max MPI = %d\n", MaxToancuc);  
  }
//================================== 
  MPI_Finalize();
  return 0;
}   	
