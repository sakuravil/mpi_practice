#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include "file.h"
#define M 100

int main(int argc,char **argv){
  int num,rank,i,j=0,flag=0,file_rank=0;
  int box1[M]={0},box2[M]={0},send[M]={0},recv1[M]={0},recv2[M]={0};
  MPI_Status status;
  MPI_Init(&argc,&argv);
  MPI_Comm_size(MPI_COMM_WORLD, &num);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  for(i=0;i<M;i++){
    box1[i]=i;
    box2[i]=i;
  }
  switch(rank){
    case 0: 
      for(i=0;i<M/2;i++)box1[i]*=5;
      for(i=0;i<M/2;i++)send[i]=box1[i];
      MPI_Send(send,M/2,MPI_INT,1,0,MPI_COMM_WORLD);
      for(i=0;i<M/2;i++)send[i]=box2[i];
      MPI_Send(send,M/2,MPI_INT,1,1,MPI_COMM_WORLD);
      break;	

    case 1:
      for(i=M/2;i<M;i++){
      box1[i]*=5;
      recv1[i]=box1[i];
      recv2[i]=box2[i];
      }
      MPI_Recv(recv1,M/2,MPI_INT,0,0,MPI_COMM_WORLD,&status);
      MPI_Recv(recv2,M/2,MPI_INT,0,1,MPI_COMM_WORLD,&status);	
      for(i=0;i<M;i++)printf("rot=%d,box1=%d box2=%d\n",j,recv1[i],recv2[i]);
      break;
  }
  j++;	
  MPI_Finalize();
}
