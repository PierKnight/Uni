#include <mpi.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
    MPI_Init(&argc,&argv);

    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);

    if(rank == 0)
    {
        int valore_da_inviare = 5;
        MPI_Send(&valore_da_inviare,1,MPI_INT,1,0,MPI_COMM_WORLD);
        printf("HO INVIATO IL VALORE! %d\n",valore_da_inviare);
    }
    else
    {
        int valoreRicevuto;
        MPI_Status status;
        
        MPI_Recv(&valoreRicevuto,1,MPI_INT,0,0,MPI_COMM_WORLD,&status);

        printf("HO RICEVUTO IL VALORE! %d\n",valoreRicevuto);
    }


    MPI_Finalize();
    return 0;
}
