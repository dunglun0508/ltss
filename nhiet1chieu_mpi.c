#include <stdio.h>
#include <malloc.h>
#include <mpi.h>

#define M 20
#define Time 2
#define dx 0.1
#define dt 0.01
#define D 0.1

void DHB2(float *T, float *dT, float lb, float rb, int Mc){
  int i;
  float c,l,r;
  for (i=0;i<Mc;i++){
    c = *(T+i);
    l = (i==0)? lb: *(T+i-1);
    r = (i==Mc-1)? rb: *(T+i+1);
    *(dT+i) = (l-2*c+r)/(dx*dx);
  }
}
int main(int argc,char **argv){
  // khai bao bien
  int NP,i,rank,Mc;
  MPI_Init(&argc,&argv );
  MPI_Comm_size(MPI_COMM_WORLD,&NP);
  MPI_Comm_rank(MPI_COMM_WORLD,&rank);
  MPI_Status thongbao;
  float t= 0, *T, *dT, *Tc, *dTc,lb,rb;
  Mc = M/NP;
  T =(float *)malloc ((M)*sizeof(float));
  dT =(float *)malloc ((M)*sizeof(float));
  Tc = (float *)malloc ((Mc)*sizeof(float));
  dTc =(float *)malloc ((Mc)*sizeof(float));

//phan tan du lieu
if(rank ==0)
  for(i=0;i<M;i++)
    *(T+i)=25.0;
  MPI_Scatter(T,Mc,MPI_FLOAT,Tc,Mc,MPI_FLOAT,0, MPI_COMM_WORLD);

//khoitao - tinh lb
while(t<Time){
  if(rank==0){
    lb= 100.0;
    MPI_Send(Tc+Mc-1,1,MPI_FLOAT,rank+1,rank+1,MPI_COMM_WORLD);
  }
  else if(rank!= NP-1){
    MPI_Recv(&lb,1,MPI_FLOAT,rank-1,rank, MPI_COMM_WORLD,&thongbao);
    MPI_Send(Tc+Mc-1,1,MPI_FLOAT,rank+1,rank+1,MPI_COMM_WORLD);
  }
  else{
    MPI_Recv(&lb,1,MPI_FLOAT,rank-1,rank, MPI_COMM_WORLD,&thongbao);
    
  }
  if(rank==NP-1){
    rb= 25.0;
    MPI_Send(Tc+0,1,MPI_FLOAT,rank-1,rank-1,MPI_COMM_WORLD);
  }
  else if(rank != 0){
    MPI_Recv(&rb,1,MPI_FLOAT,rank+1,rank, MPI_COMM_WORLD,&thongbao);
    MPI_Send(Tc,1,MPI_FLOAT,rank-1,rank-1,MPI_COMM_WORLD);
  }
  else{
    MPI_Recv(&rb,1,MPI_FLOAT,rank+1,rank, MPI_COMM_WORLD,&thongbao);
  }

  DHB2(Tc,dTc,lb,rb,Mc);

  for(i=0;i<Mc;i++){
    *(Tc+i)=*(Tc+i)+D* *(dTc+i)*dt;
    t = t+dt;
  }
    }
MPI_Gather(Tc,Mc,MPI_FLOAT,T,Mc,MPI_FLOAT,0,MPI_COMM_WORLD);
  // in ra KQ
if(rank==0)
  for(i=0;i<M;i++) printf("%f\n",*(T+i) );
  MPI_Finalize();
  return 0;
}
