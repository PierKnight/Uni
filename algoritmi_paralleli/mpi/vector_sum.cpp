#include <stdio.h>
#include <mpi.h>


void printArray(int* array,int size)
{
    for(int i = 0;i < size;i++)
        printf("%d\n",array[i]);
}

int main(int argc, char *argv[])
{
    MPI_Init(&argc,&argv);

    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);

    int numProc;
    MPI_Comm_size(MPI_COMM_WORLD,&numProc);
    numProc -= 1;

    int tag = 0;

    //ESISTE LA BARRIER
    //MPI_Barrier(MPI_COMM_WORLD);

    //il tempo si prende con
    //MPI_Wtime();

    if(rank == 0) //MASTER
    {
        int* vector = new int[numProc];

        for(int i = 0;i < numProc;i++)
            vector[i] = i;

        for(int i = 0;i < numProc;i++)
            MPI_Send(&vector[i],1,MPI_INT,i,tag,MPI_COMM_WORLD);

        for(int i = 0;i < numProc;i++)
        {
            MPI_Recv(&vector[i],1,MPI_INT,MPI_ANY_SOURCE,tag,MPI_COMM_WORLD,nullptr);
        }

        printArray(vector,numProc);

        delete [] vector;
    }
    else //SLAVE
    {
        int receivedValue;
        //RICEVO IL VALORE
        MPI_Recv(&receivedValue,1,MPI_INT,0,tag,MPI_COMM_WORLD,nullptr);

        //MOLTIPLICO PER 2
        receivedValue *= 2;

        MPI_Send(&receivedValue,1,MPI_INT,0,tag,MPI_COMM_WORLD);


    }

    MPI_Finalize();


    return 0;
}

