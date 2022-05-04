#include <stdio.h>
#include <mpi.h>


int main(int argc, char *argv[])
{
    MPI_Init(&argc,&argv);
    
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);

    int numProc;
    MPI_Comm_size(MPI_COMM_WORLD, &numProc);

    int tag = 0;
    char message[100]; //message storage

    //IL MASTER
    if(rank == 0)
    {
        MPI_Status status;
        //RICEVO LE STRINGHE
        for(int i = 1;i < numProc;i++)
        {
            MPI_Recv(message,100,MPI_CHAR,MPI_ANY_SOURCE,tag,MPI_COMM_WORLD,&status);
            printf("HO RICEVUTO: %s\n",message);
        }

    }
    else //GLI SLAVE
    {
        sprintf(message,"SALVE DAL PROCESSO %d",rank);
        //MANDO LA STRINGA
        MPI_Send(message,strlen(message) + 1, MPI_CHAR ,0, tag ,MPI_COMM_WORLD);
    }

    MPI_Finalize();

    return 0;
}
