#include<stdio.h>
#include<mpi.h>
#include<unistd.h>
#include<malloc.h>

#define m 10
#define n 10

void DisplayMatrix(float *A, int row,  int col){
  int i,j;
  for(i=0;i<row;i++){
    for(j=0;j<col;j++) printf("%f \t",*(A+i*col+j));
    printf("\n");
  }
}

int abs(int x)
{
         if (x > 0) return x;
         if (x < 0) return -x;
         if (x == 0) return 0;
}

void khoitao(){
	int i,j;
	float *C;
	C = (float *) malloc ((m*n)*sizeof(float));
	for(i = 0; i<m;i++){
		for (j = 0; j < n; j++){
			if(j ==0){
				*(C+i*n+j)= 1.0;
			}
			else if(j==(n-1)){
				*(C+i*n+j) = 0.0;
			}
			else{
				if(i==0){
					*(C+i*n+j) = *(C+(m-1)*n+j);
				}
			}
		}
	}
}

void tinhtoan(float *C){
	int i,j;
	float *C1,*west,*east,*south,d =10.0,*north, x, max, e = 0.01, C0 = 1.0, C2 = 0.0;
	C1 = (float *) malloc ((m*n)*sizeof(float));
	west= (float *) malloc ((1*1)*sizeof(float));
	east= (float*) malloc ((1*1)*sizeof(float));
	south = (float *) malloc ((1*1)*sizeof(float));
	north = (float *) malloc ((1*1)*sizeof(float));
	while(d>e){
		for(i = 0; i<m; i++){
			for(j = 0; j<n;j++){
				if(j ==0){
					*(C1+i*n+j)= C0;
				}
				else if(j == (n-1)){
					*(C1+i*n+j) = C2;
				}
				else{
					if(i ==0){
						*(west+i*n+j) = *(C+(m-1)*n+j);
					}
					else{
						*(west+i*n+j) = *(C+(i-1)*n+j);
					}
					if(i ==(m-1)){
						*(east+i*n+j) = *(C+0*n+j);
					}
					else{
						*(east+i*n+j) = *(C+(i+1)*n+j);
					}
					*(south+i*n+j) = *(C+i*n+(j+1));
					*(north+i*n+j) = *(C+i*n+(j-1));
					*(C1+i*n+j) = ((*(west+i*n+j)) + (*(east+i*n+j)) + (*(south+i*n+j)) + (*(north+i*n+j)))/4.0;
				}
			}
		}
		max = 0;
		for(i = 0; i<m; i++){
			for(j = 0; j<n; j++){
				x = (*(C1+i*n+j))- (*(C+i*n+j)); 
				abs(x);
				if (x > max){
					max = x;
				}
			}
		}
		d = max;
		for (i = 0; i<m; i++){
			for(j = 0; j<n; j++){
				*(C+i*n+j) = *(C1+i*n+j);
			}
		}
	}

}

int main(int argc, char **argv)
{
	int NP, rank, Mc, i,j;
	float *Tc, *Cc, *C;
	C = (float *) malloc ((m*n)*sizeof(float));
	Tc = (float *) malloc ((Mc*n)*sizeof(float));
	Cc = (float *) malloc ((Mc*n)*sizeof(float));
	MPI_Init (&argc,&argv );
	MPI_Comm_size(MPI_COMM_WORLD,&NP);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Status thongbao;
	Mc = m/NP;
	float Nneighbor[m];
	float Sneighbor[n];
	if (rank == 0){
		khoitao();
		for (i = 0; i<m; i++){
			for(j = 0; j<Mc; j++){
				*(Tc+i*Mc+j) = *(C+i*Mc+j);
			}
		}
		MPI_Scatter(C, Mc*n,MPI_FLOAT,Cc,Mc*n,MPI_FLOAT,0,MPI_COMM_WORLD);
			
	}
		// Comm lb
	if (rank==0){
		for (i = 0; i < m; i++)
		{
			Nneighbor[i] = 1;
		}
		MPI_Send(C+Mc-1,1,MPI_FLOAT,rank+1,rank,MPI_COMM_WORLD);
	} else if (rank!=NP-1) {
		MPI_Recv(&Nneighbor,n,MPI_FLOAT,rank-1,rank-1,MPI_COMM_WORLD,&thongbao);
		MPI_Send(C+Mc-1,1,MPI_FLOAT,rank+1,rank,MPI_COMM_WORLD);
	} else {
		MPI_Recv(&Nneighbor,n,MPI_FLOAT,rank-1,rank-1,MPI_COMM_WORLD,&thongbao);
	}
	// Comm rb
	if (rank==NP-1){
		for (i = 0; i < n; i++)
		{
			Sneighbor[i] =0;
		}
		MPI_Send(C+0,1,MPI_FLOAT,rank-1,rank,MPI_COMM_WORLD);
	} else if (rank!=0) {
		MPI_Recv(&Nneighbor,n,MPI_FLOAT,rank+1,rank+1,MPI_COMM_WORLD,&thongbao);
		MPI_Send(C+0,1,MPI_FLOAT,rank-1,rank,MPI_COMM_WORLD);
	} else {
		MPI_Recv(&Nneighbor,n,MPI_FLOAT,rank+1,rank+1,MPI_COMM_WORLD,&thongbao);
	}
	tinhtoan(C);
	MPI_Gather ( Cc, Mc*n, MPI_FLOAT,C, Mc*n, MPI_FLOAT, 0,MPI_COMM_WORLD);
	if(rank ==0){
		for (i = 0; i<m; i++){
			for(j = 0; j<Mc; j++){
				*(Tc+i*Mc+j) = *(C+i*Mc+j);
			}
		}
	}
	if(rank!=0){
		 MPI_Send(Tc,Mc*n,MPI_FLOAT,0,rank,MPI_COMM_WORLD);
	}
	else{
		for(i= 0; i<m;i++){
			for (int p = 0; p < NP; p++)
			{
				MPI_Recv(C+Mc*p,Mc*n,MPI_FLOAT,p,p,MPI_COMM_WORLD,&thongbao);
			}
		}
	}
		DisplayMatrix(C,m,n);
	
	return 0;
}
