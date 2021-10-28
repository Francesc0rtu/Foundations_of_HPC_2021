#include<stdio.h>
#include <stdlib.h>
#include<mpi.h>
int main(int argc, char *argv[]){
    int rank,size,tag=123;
    MPI_Status status;
    int send, rec;
    MPI_Init(&argc,&argv);
    MPI_Comm_size(MPI_COMM_WORLD,&size);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    send = 67 ;
    if (rank == 1){
        printf("rank %d\n",rank) ;
        MPI_Send(&send,0,MPI_INT,0,tag,MPI_COMM_WORLD) ;
    }
    if(rank == 0){
        MPI_Recv(&rec,1,MPI_INT,1,tag,MPI_COMM_WORLD,&status ) ;
        printf("dato ricevuto %d\n", rec) ;
    }
     MPI_Finalize() ; // let MPI finish up /
     return 0;
}
