#include <stdio.h>
#include <mpi.h>
#define M 2500
#define P 5

int main(int argc,char **argv){
  int i,j,N;
  int num,rank;
  int num1[20][20],num2[20][20];
  double sum_A,sum_B,sum_0;
  MPI_Status status;
  MPI_Datatype mpi_1;
  MPI_Init(&argc,&argv);
  MPI_Comm_size(MPI_COMM_WORLD, &num);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Type_vector(20,1,20,MPI_INT,&mpi_1);
  MPI_Type_commit(&mpi_1);

  for(i=0;i<20;i++){
    for(j=0;j<20;j++){
      num1[i][j]=rank+1;
    }
  }

  if(!rank){
    MPI_Send(&num1[0][0],1,mpi_1,1,0,MPI_COMM_WORLD);
    MPI_Recv(&num1[0][19],1,mpi_1,1,0,MPI_COMM_WORLD,&status);		
  } else{
  MPI_Recv(&num1[0][0],1,mpi_1,0,0,MPI_COMM_WORLD,&status);
  MPI_Send(&num1[0][19],1,mpi_1,0,0,MPI_COMM_WORLD);
  }

  if(!rank){
    printf("rank:%d\n\n",rank);
    printf("   ");
    for(i=0;i<20;i++){
      printf("%2d ",i);
    }
    printf("\n");

    for(i=0;i<20;i++){
      printf("%2d ",i);
      for(j=0;j<20;j++){
        printf("%2d ",num1[i][j]);
      }
      printf("\n");
    }
      printf("\n");
  } else{
    printf("rank:%d\n\n",rank);
    printf("   ");
    for(i=0;i<20;i++){
      printf("%2d ",i);
    }
    printf("\n");

    for(i=0;i<20;i++){
      printf("%2d ",i);
      for(j=0;j<20;j++){
        printf("%2d ",num1[i][j]);
    }
      printf("\n");
    }
    printf("\n");
  }

  MPI_Finalize();
  return (0);
}
