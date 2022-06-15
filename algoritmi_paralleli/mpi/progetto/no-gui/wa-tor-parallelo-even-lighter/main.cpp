#include <mpi.h>
#include "wator.cpp"
#define CELL_SIZE 10



//compilazione g++ <file> -lallegro
//g++ parallel.cpp $(pkg-config --libs allegro-5 allegro_main-5 allegro_primitives-5)
//mpiCC parallel.cpp $(pkg-config --libs allegro-5 allegro_main-5 allegro_primitives-5 )
//export DISPLAY=:0



inline void createCreatureType(MPI_Datatype* data)
{
    MPI_Aint displacements[2]  = {offsetof(creature,moved),offsetof(creature,energy)};
    int block_lengths[2]  = {1,1};
    MPI_Datatype types[2] = {MPI_CXX_BOOL,MPI_INT};
    MPI_Type_create_struct(2, block_lengths, displacements, types, data);
    MPI_Type_commit(data);
}

int main(int argc, char *argv[])
{


    MPI_Init(&argc,&argv);
    int rank,nProc;
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Comm_size(MPI_COMM_WORLD,&nProc);

    if(rank == 0 && ROWS < nProc * 4)
    {
        printf("this wa-tor implementation requieres that the number of rows is at least four times bigger the number of precesses\n");
        MPI_Abort(MPI_COMM_WORLD,0);
    }

    MPI_Datatype type;
    createCreatureType(&type);

    //questo serve per distrubuire il resto delle righe (se presenti)
    int extra = (rank < ROWS % nProc) ? 1 : 0;

    creature* matrix = new creature[(ROWS / nProc + 4 + 1) * COLS];

    double startTime;

    //setup process 0
    if(rank == 0)
    {
        matrix[V(2,0)].setType(FISH);
        startTime = MPI_Wtime();
    }

    for(int t = 0;t < 1000;t++)
    {
        //aggiorna l'interno della matrice
        updateWorld(matrix,3,ROWS / nProc - 2 + extra,true);


        MPI_Request request;
        if(rank % 2 == 0) //i processi pari ricevono i bordi, li aggiornano e li rinviano
        {
            MPI_Recv(matrix,COLS * 2,type,(rank + nProc - 1) % nProc,1,MPI_COMM_WORLD,nullptr);
            MPI_Recv(&matrix[V(ROWS / nProc + 2 + extra,0)],COLS * 2,type,(rank + nProc + 1) % nProc,0,MPI_COMM_WORLD,nullptr);

            updateWorld(matrix, 1, 2,false);
            updateWorld(matrix, ROWS / nProc + 1 + extra, 2,false);

            MPI_Isend(matrix,2 * COLS,type,(rank + nProc - 1) % nProc,0,MPI_COMM_WORLD,&request);
            MPI_Isend(&matrix[V(ROWS / nProc + 2 + extra,0)],2 * COLS,type,(rank + nProc + 1) % nProc,1,MPI_COMM_WORLD,&request);
            
        }
        else //i processi dispari inviano i propri bordi e li ricevono
        {
            //invio i miei bordi con annesso vicino 
            MPI_Isend(&matrix[V(2,0)],2 * COLS,type,(rank + nProc - 1) % nProc,0,MPI_COMM_WORLD,&request);
            MPI_Isend(&matrix[V(ROWS / nProc + extra,0)],2 * COLS,type,(rank + nProc + 1) % nProc,1,MPI_COMM_WORLD,&request);
            
            MPI_Recv(&matrix[V(2,0)],COLS * 2,type,(rank + nProc - 1) % nProc,1,MPI_COMM_WORLD,nullptr);
            MPI_Recv(&matrix[V(ROWS / nProc + extra,0)],COLS * 2,type,(rank + nProc + 1) % nProc,0,MPI_COMM_WORLD,nullptr);
        }

        MPI_Barrier(MPI_COMM_WORLD);
    
    }



    if(rank == 0)
    {
        printf("TOTAL TIME %f\n",MPI_Wtime() - startTime);
    }

    delete [] matrix;
    MPI_Finalize();
    
    return 0;
}
