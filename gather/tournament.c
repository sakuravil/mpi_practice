#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include "file.h"
#define M 10000

int main(int argc,char **argv){
  int num,rank,i,j=0,flag=0,file_rank=0;
  int box[M]={0},send[M]={0},recv[M]={0};
  MPI_Status status;
  MPI_Init(&argc,&argv);
  MPI_Comm_size(MPI_COMM_WORLD, &num);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  switch(rank){
    case 0:
      for(i=0;i<M/4;i++)box[i]=i;
      MPI_Send(box,M/4,MPI_INT,1,0,MPI_COMM_WORLD);
      break;

    case 1:
      for(i=M/4;i<M/2;i++)box[i]=i;
      MPI_Recv(box,M/4,MPI_INT,0,0,MPI_COMM_WORLD,&status);
      MPI_Send(box,M/2,MPI_INT,3,0,MPI_COMM_WORLD);
      break;

    case 2:
      for(i=M/2;i<M/4*3;i++)box[i]=i;
      MPI_Send(&box[M/2],M/4,MPI_INT,3,0,MPI_COMM_WORLD);
      break;

    case 3:
      for(i=M/4*3;i<M;i++)box[i]=i;
      MPI_Recv(&box[M/2],M/4,MPI_INT,2,0,MPI_COMM_WORLD,&status);
      MPI_Recv(box,M/2,MPI_INT,1,0,MPI_COMM_WORLD,&status);
      break;
  }

  if(rank==3)file_write(box,M);
  MPI_Finalize();
}
