#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#define M 100

  int main(int argc,char **argv){
  int num,rank,i,j=0,flag=0,file_rank=0;
  int box[M]={0},send[M]={0},recv[M]={0};
  MPI_Status status,buf;
  MPI_Init(&argc,&argv);
  MPI_Comm_size(MPI_COMM_WORLD, &num);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_File fh;

  MPI_File_open(MPI_COMM_WORLD,"test.txt",MPI_MODE_CREATE | MPI_MODE_WRONLY, MPI_INFO_NULL, &fh);

  for(i=0;i<M/4;i++){
    if(rank==0)
      box[i]=i;
    else if(rank==1){
      j=i+M/4;
      box[j]=j;
    } else if(rank==2){
      j=i+M/2;
      box[j]=j;
    } else if(rank==3){
      j=i+M/4*3;
      box[j]=j;
    }
  }

  MPI_File_write(fh,buf,1024,MPI_INT,&status);

  MPI_File_close(&fh);
  MPI_Finalize();
}
