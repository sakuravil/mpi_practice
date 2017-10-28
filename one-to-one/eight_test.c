#include <stdio.h>
#include <mpi.h>
#define M 2500
#define P 5

int main(int argc,char **argv){
  int i,N,j=0;
  int num,rank,buffer;
  int ans[5]={1,2,3,4,5},send[5]={0},recv[5]={0};
  double sum_A,sum_B,sum_0;
  MPI_Status status;
  MPI_Init(&argc,&argv);
  MPI_Comm_size(MPI_COMM_WORLD, &num);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

if(rank==0){
  for(i=1;i<=7;i++){
    for(j=0;j<5;j++)send[j]=ans[j];
      MPI_Send(send,5,MPI_INT,i,2,MPI_COMM_WORLD);
    }
  }
  else{
    MPI_Recv(recv,5,MPI_INT,0,2,MPI_COMM_WORLD,&status);
    for(i=0;i<5;i++)ans[i]=recv[i];	
  } 	
  for(i=0;i<5;i++)printf("rank=%d ans[%d]=%d\n",rank,i,recv[i]);
  MPI_Finalize();
}
