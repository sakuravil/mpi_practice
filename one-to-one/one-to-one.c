#include <stdio.h>
#include <mpi.h>
#define M 2500
#define P 5

int main(int argc,char **argv){
  int i,N,j=0;
  int num,rank,buffer;
  int ans[5]={},send[5]={},recv[5]={};
  double sum_A,sum_B,sum_0;
  MPI_Status status;
  MPI_Init(&argc,&argv);
  MPI_Comm_size(MPI_COMM_WORLD, &num);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

if(rank==0){
  for(i=0;i<5;i++)send[i]=i;
}

if(rank==0){
  MPI_Send(send, 5, MPI_INT, 1, 2, MPI_COMM_WORLD);
}

if(rank==1){
  MPI_Recv(recv, 5, MPI_INT, 0, 2, MPI_COMM_WORLD,&status);
}

for(i = 0; i < 5; i++)
  printf("rank=%d send[%d]=%d\n", rank, i, send[i]);
  MPI_Finalize();
}
