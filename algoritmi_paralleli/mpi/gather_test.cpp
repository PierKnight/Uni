#include <mpi.h>
#include <stdio.h>
//#define SIZE 2

int main(int argc, char *argv[])
{
    
    MPI_Init(&argc,&argv);

    int nProc;
    MPI_Comm_size(MPI_COMM_WORLD,&nProc);

    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);


    int size = rank == 0 ? 2 : 3;

    int* test = new int[size];
    for(int i = 0;i < size;i++)
        test[i] = rank + i;

    
    int* receive;

    MPI_Gather(test,size,MPI_INT,receive,3,MPI_INT,0,MPI_COMM_WORLD);

    if(rank == 0)
    {
        for(int i = 0;i < 5;i++)
            printf("I valori sono: %d\n",receive[i]);
    }


    delete [] test;

    MPI_Finalize();




    return 0;
}
