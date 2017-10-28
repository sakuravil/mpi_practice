#include        <stdio.h>
#include        <stdlib.h>
#include        <string.h>
#include        <math.h>
#include        "mpi.h"
#define M 100
#define P 2

static char str[20]={};

void io(int id,int pro,int max,MPI_Status status){
  int i,start=max/pro*id;
  MPI_File fp1;

  MPI_File_delete("A.dat",MPI_INFO_NULL);
  MPI_File_open(MPI_COMM_WORLD,"A.dat",MPI_MODE_CREATE | MPI_MODE_WRONLY,MPI_INFO_NULL,&fp1);
  MPI_File_set_view(fp1,M*id*sizeof(str),MPI_CHAR,MPI_CHAR,"native",MPI_INFO_NULL);
  MPI_File_seek(fp1,id*M,MPI_SEEK_SET);

  for(i=start;i<start + max/pro;i++){
    sprintf(str,"%d %.6f\n",i,i*(id+0.5));
    MPI_File_write_ordered(fp1,&str[0],strlen(str),MPI_CHAR,&status);
  }
  MPI_File_sync(fp1);
  MPI_File_close(&fp1);
}


int main(int argc,char **argv){
  int num,rank;
  int i,N;

  MPI_Status status;
  MPI_Init(&argc,&argv);
  MPI_Comm_size(MPI_COMM_WORLD, &num);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  int start=M/P*rank;

  io(rank,P,M,status);
  MPI_Finalize();
}
