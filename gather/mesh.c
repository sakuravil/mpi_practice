#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include "file.h"
#define M 10000

int main(int argc,char **argv){
  int num,rank,i,j=0,flag=0;
  int box[M]={0},send[M]={0},recv[M]={0};
  MPI_Status status;
  MPI_Init(&argc,&argv);
  MPI_Comm_size(MPI_COMM_WORLD, &num);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  if(rank==0){
    for(i=0;i<M/4;i++)box[i]=i;
  }	else if(rank==1){
    for(i=(M/4)-1;i<(M/2);i++)box[i]=i;
  } else if(rank==2){
    for(i=(M/2)-1;i<((M/4)*3);i++)box[i]=i;
  } else if(rank==3){
    for(i=((M/4)*3)-1;i<M;i++)box[i]=i;
  }

  if(rank==0){
    MPI_Send(box,M/4,MPI_INT,1,0,MPI_COMM_WORLD);
  } else if(rank==1){
    MPI_Recv(box,M/4,MPI_INT,0,0,MPI_COMM_WORLD,&status);
    MPI_Send(box,M/2,MPI_INT,2,0,MPI_COMM_WORLD);
  } else if(rank==2){
    MPI_Recv(box,M/2,MPI_INT,1,0,MPI_COMM_WORLD,&status);
    MPI_Send(box,(M/4)*3,MPI_INT,3,0,MPI_COMM_WORLD);
  } else if(rank==3){
    MPI_Recv(box,(M/4)*3,MPI_INT,2,0,MPI_COMM_WORLD,&status);
  }

  if(rank==3){
    file_write(box,M);
  }

  MPI_Finalize();
}
