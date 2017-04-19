#include <stdio.h>
#include <mpi.h>
#include <malloc.h>
#define M 20

int main(int argc,char **argv){
	int NP,p,i,rank,Mc;
	MPI_Init(&argc,&argv );
	MPI_Comm_size(MPI_COMM_WORLD,&NP);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Status thongbao;

	int *A,*B,*C;
	A = (int *) malloc (M*sizeof(int));
	B = (int *) malloc (M*sizeof(int));
	C = (int *) malloc (M*sizeof(int));
	// Domain decom.
	Mc = M/NP;
	int *Ac,*Bc,*Cc;
	Ac = (int *) malloc (Mc*sizeof(int));
	Bc = (int *) malloc (Mc*sizeof(int));
	Cc = (int *) malloc (Mc*sizeof(int));	
	// Khoi tao
	if (rank==0)
		for (i=0;i<M;i++) {*(A+i) = i;*(B+i) = 2*i;}
	// Phan tan input data
	if (rank==0){
		for (i=0;i<Mc;i++) {*(Ac+i) = *(A+i);*(Bc+i) = *(B+i);}
		for (p=1;p<NP;p++){
			MPI_Send(A+Mc*p,Mc,MPI_INT,p,p,MPI_COMM_WORLD);
			MPI_Send(B+Mc*p,Mc,MPI_INT,p,p,MPI_COMM_WORLD);
		}
	}
	else {
		MPI_Recv(Ac,Mc,MPI_INT,0,rank,MPI_COMM_WORLD,&thongbao);
		MPI_Recv(Bc,Mc,MPI_INT,0,rank,MPI_COMM_WORLD,&thongbao);
	}
	// Tinh toan
	for (i=0;i<Mc;i++) *(Cc+i) = *(Ac+i) + *(Bc+i);
	// Gather Output
	if (rank!=0) 
    	MPI_Send(Cc,Mc,MPI_INT,0,rank,MPI_COMM_WORLD);
    else
    {
    	for (i=0;i<Mc;i++) *(C+i) = *(Cc+i);
    	for (p=1;p<NP;p++) MPI_Recv(C+Mc*p,Mc,MPI_INT,p,p,MPI_COMM_WORLD,&thongbao);
    }
	// Print result
	if (rank==0) for (i=0;i<M;i++) printf("%d\t",*(C+i));
	printf("\n");
	MPI_Finalize();
	return 0;
}

/*
#define M 20
#define dx 0.1
#define dt 0.01
#define Time 10
#define D 0.1

void TinhDF(float *dF, float *T, int Ms,float lbound, float rbound){
	float c,r,l;
	int i;	
	for (i=0;i<Ms;i++){
		c = *(T+i);
		l = (i==0) ? lbound:*(T+i-1);
		r = (i==Ms-1) ? rbound:*(T+i+1);
		*(dF+i) = (l-2*c+r)/(dx*dx);
	}	
}
int main(int argc,char **argv){
	int i;
	float t=0,*T,*dF,*Tc,*dFc,lb,rb;
	T = (float *) malloc (M*sizeof(float));
	dF= (float *) malloc (M*sizeof(float));

	int NP,p,rank,Mc;
	MPI_Init(&argc,&argv );
	MPI_Comm_size(MPI_COMM_WORLD,&NP);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Status thongbao;

	Mc = M/NP;
	Tc = (float *) malloc (Mc*sizeof(float));
	dFc= (float *) malloc (Mc*sizeof(float));
	if (rank==0) {
		for (i=0;i<M;i++) *(T+i) = 25.0;
		for (i=0;i<Mc;i++) *(Tc+i) = *(T+i);
		for (p=1;p<NP;p++) MPI_Send(T+Mc*p,Mc,MPI_FLOAT,p,p,MPI_COMM_WORLD);}
	else
		MPI_Recv(Tc,Mc,MPI_FLOAT,0,rank,MPI_COMM_WORLD,&thongbao);

	while (t<Time){
		// Comm lb
		if (rank==0){
			lb = 100.0;
			MPI_Send(Tc+Mc-1,1,MPI_FLOAT,rank+1,rank,MPI_COMM_WORLD);
		} else if (rank!=NP-1) {
			MPI_Recv(&lb,1,MPI_FLOAT,rank-1,rank-1,MPI_COMM_WORLD,&thongbao);
			MPI_Send(Tc+Mc-1,1,MPI_FLOAT,rank+1,rank,MPI_COMM_WORLD);
		} else {
			MPI_Recv(&lb,1,MPI_FLOAT,rank-1,rank-1,MPI_COMM_WORLD,&thongbao);
		}
		// Comm rb
		if (rank==NP-1){
			rb = 25.0;
			MPI_Send(Tc+0,1,MPI_FLOAT,rank-1,rank,MPI_COMM_WORLD);
		} else if (rank!=0) {
			MPI_Recv(&rb,1,MPI_FLOAT,rank+1,rank+1,MPI_COMM_WORLD,&thongbao);
			MPI_Send(Tc+0,1,MPI_FLOAT,rank-1,rank,MPI_COMM_WORLD);
		} else {
			MPI_Recv(&rb,1,MPI_FLOAT,rank+1,rank+1,MPI_COMM_WORLD,&thongbao);
		}

		TinhDF(dFc,Tc,Mc,lb,rb);
		for (i=0;i<Mc;i++) *(Tc+i) = *(Tc+i) + D* *(dFc+i)*dt;
		t = t + dt;
	}
	if (rank==0) for (i=0;i<Mc;i++) *(T+i) = *(Tc+i);
    if (rank!=0) MPI_Send(Tc,Mc,MPI_FLOAT,0,rank,MPI_COMM_WORLD);
    else for (p=1;p<NP;p++) MPI_Recv(T+Mc*p,Mc,MPI_FLOAT,p,p,MPI_COMM_WORLD,&thongbao);
	if (rank==0) for (i=0;i<M;i++) printf("%.2f ",*(T+i));	
	MPI_Finalize();
return 0;
}
*/