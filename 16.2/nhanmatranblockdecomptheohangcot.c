#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#define M 6
#define N 6
#define P 6
int main(){
int i,j,k,*A, *B, *C, S;
int id, idh, idc,starth, stoph, startc, stopc ;
int NT = 6, NTc = 3, NTh;
A = (int *) malloc (M*N*sizeof(int));
B = (int *) malloc (N*P*sizeof(int));
C = (int *) malloc (M*P*sizeof(int));
omp_set_num_threads(NT);
NTh = NT/NTc;
#pragma omp parallel private (i, j,k,id, startc, stopc,starth, stoph, S,idh, idc)
{
	id = omp_get_thread_num();
	idh = id/NTc;
	idc = id%NTc;
	starth = idh*(M/NTh);
	stoph = (idh+1)*(M/NTh);
	startc = idc*(P/NTc);
	stopc = (idc+1)*(P/NTc);
	for(i= starth; i<stoph; i++){
		for (j = 0; j<N; j++){
			if(i == j){
			*(A+i*N+j) = 1;
			}
			else {
				*(A+i*N+j) = 0;
			}
		}
	}
	for(j= 0; j<N; j++){
		for (k = startc; k<stopc; k++){
			*(B+j*P+k) = j*P+k;	
		}
	}
	for(i = starth; i<stoph; i++){
		for(k = startc; k<stopc; k++){
			S = 0;
			for (j = 0; j<N; j++) S = S + *(A+i*N+j) * *(B+j*P+k);
			*(C+i*P+k) = S;
		}
	}
}

for(i= 0; i<M; i++){
	for (j = 0; j<N; j++)
		printf("%d \t", *(A+i*N+j));
	printf("\n");
}



for(i= 0; i<N; i++){
	for (j = 0; j<P; j++)
		printf("%d \t", *(B+i*P+j));
	printf("\n");
}

for(i= 0; i<M; i++){
	for (j = 0; j<P; j++)
		printf("%d \t", *(C+i*P+j));
	printf("\n");
}

}

