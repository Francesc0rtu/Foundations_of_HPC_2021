#include<stdio.h>
#include <stdlib.h>
#include<mpi.h>


int main(int arg, char* argv[]){

    int rank,size, M;
    int partial_sum=0;

    double start_time, end_time;
    MPI_Status status;
    int master=0, tag=1234;
    int tmp;

    MPI_Init(&arg,&argv);
    MPI_Comm_size(MPI_COMM_WORLD,&size);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);

    int n=atoll(argv[1]);

    start_time = MPI_Wtime();

    for(int i=rank*(n/size); i< (rank+1)*(n/size); i++){
        partial_sum=i+partial_sum;
        }
        printf("%d\n",partial_sum);

    if(rank != 0){
        printf("prima del send rank=%d  partial=%d\n", rank, partial_sum);
        MPI_Send(&partial_sum,0,MPI_INT,master,tag,MPI_COMM_WORLD);
        }
    if(rank==0){
        int M=partial_sum; printf("M=%d\n",M);
        for (int proc=1; proc<size ; proc++) {
                MPI_Recv(&partial_sum,1,MPI_INT,proc,tag,MPI_COMM_WORLD,&status ) ;
                printf("tmp=%d \n",partial_sum);
                M += partial_sum ;
            }
        end_time=MPI_Wtime();
        printf ("result: %d  \n",M);
    }
     MPI_Finalize() ; // let MPI finish up /
    return 0;
}
