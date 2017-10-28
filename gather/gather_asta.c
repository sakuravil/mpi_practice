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
      for(i=0;i<M/4;i++)send[i]=i; 
      MPI_Gather(send,M/4,MPI_INT,recv,M/4,MPI_INT,3,MPI_COMM_WORLD);
      break;

    case 1:
      for(i=(M/4);i<(M/2);i++){ 
        send[j]=i;
        j++;
      }
      MPI_Gather(send,M/4,MPI_INT,recv,M/4,MPI_INT,3,MPI_COMM_WORLD);
      j=0;
      break;

    case 2:
      for(i=(M/2);i<((M/4)*3);i++){ 
        send[j]=i;
        j++;
      }
      MPI_Gather(send,M/4,MPI_INT,recv,M/4,MPI_INT,3,MPI_COMM_WORLD);
      j=0;
      break;

    case 3:
      for(i=((M/4)*3);i<M;i++){ 
        send[j]=i;
        j++;
      }
      MPI_Gather(send,M/4,MPI_INT,recv,M/4,MPI_INT,3,MPI_COMM_WORLD);
      j++;
      break;
  }

  if(rank==3)file_write(recv,M);
  //if(rank==3)for(i=0;i<M;i++)printf("rank=%d;recv[%d]=%d\n",rank,i,recv[i]);
  MPI_Finalize();
}
