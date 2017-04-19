#include <stdio.h>
#include <malloc.h>
#include <mpi.h>

#define M 20
#define Time 1
#define dx 0.1
#define dt 0.01
#define D 0.1

void DHB2(float *T, float *dT, float *lb, float *rb, int Mc){
  int i;
  float c,l,r;
  for (i=0;i<M;i++){
    c = *(T+i);
    l = (i==0)? *lb: *(T+i-1);
    r = (i==M-1)? *rb: *(T+i+1);
    *(dT+i) = (l-2*c+r)/(dx*dx);
  }
}
int main(){
  int i, p, rank, MP, NC;
  float t = 0, *T, dT;
  T =(float *)malloc ((M)*sizeof(float));
  dT =(float *)malloc ((M)*sizeof(float));
  Tc =(float *)malloc ((M)*sizeof(float));
  dTc =(float *)malloc ((M)*sizeof(float));

  if(rank = 0)
  MPI_Init(&argc, &argv);
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  // khai bao bien
  int i;
  float t= 0, *T, *dT;
  T =(float *)malloc ((M)*sizeof(float));
  dT =(float *)malloc ((M)*sizeof(float));
//khoitao
  for(i=0;i<M;i++)
    *(T+i)=25.0;
  while (t<Time) {
      DHB2(T, dT);
      for(i=0;i<Mc;i++)
      *(T+i)=*(T+i)+D* *(dT+i)*dt;
      t = t+dt;
    }
  //in ra KQ
  for(i=0;i<M;i++) printf("%f\n",*(T+i) );
//
  return 0;
}
