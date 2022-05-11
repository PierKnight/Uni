#include <stdio.h>
#include <mpi.h>

int main(int argc, char *argv[])
{
    MPI_Init(&argc,&argv);

    //send delle informazioni in maniera asincrona non bloccante
    //stessi paramentri della send bloccante ma alla fine abbiamo MPI_REQUEST
    //MPI_REQUEST serve pre indentificare quel send
    //MPI_Request m;
    
    //MPI_WAIT riceve come argomento MPI_REQUEST e rimane in wait finchè il send async non è stato completato

    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);

    int nProc;
    MPI_Comm_size(MPI_COMM_WORLD,&nProc);

    int size = 1000000;

    int* megaLista = new int[size];


    if(rank == 0)
    {
        for(int i = 0;i < size;i++)
            megaLista[i] = 222;

        MPI_Request req;
        MPI_Isend(megaLista,size,MPI_INT,1,1,MPI_COMM_WORLD,&req);


        MPI_Wait(&req,nullptr);
        printf("INVIATO TUTTO!\n");



    }
    else
    {
        MPI_Recv(megaLista,size,MPI_INT,0,1,MPI_COMM_WORLD,nullptr);
        printf("RICEVUTO TUTTO! %d\n",megaLista[0]);     
    }
    delete [] megaLista;
    MPI_Finalize();
    return 0;
}
