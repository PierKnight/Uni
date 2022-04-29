#include <mpi.h>

int main(int argc, char *argv[])
{
    //init di openmpi
    MPI_Init(&argc,&argv);

    int rank;
    //indentificativo del processo
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);

    //numero processi
    int processi = 3;
    MPI_Comm_size(MPI_COMM_WORLD,&processi);
    
    printf("IO SONO %d\n", rank);

    //comando di send argomenti, questo è blocking, ci sono due blocking si blocca fino a quando non è stato ricevuto, oppure si blocca fino a quando non ha inviato tutto nel buffer
    //MPI_SEND (const void* <array di elementi>, <quantità di elementi nell'array>, <tipo dato dell'array>,int <destinazione>(id del processo), int <tag> etichetta,MPI_COMM_WORLD (giusto perchè usiamo questo))
    
    //MPI_Recv(void*,int <quantità>,<tipo del dato>,<id del mittente>,MPI_COMM_WORLD)
    
    MPI_Finalize();
    return 0;
}
