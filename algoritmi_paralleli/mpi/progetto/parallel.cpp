#include <mpi.h>
#include "wator/wator.cpp"
#define CELL_SIZE 10

inline void createCreatureType(MPI_Datatype* data)
{
    MPI_Aint displacements[3]  = {offsetof(creature,moved),offsetof(creature,energy),offsetof(creature,type)};
    int block_lengths[3]  = {1,1,1};
    MPI_Datatype types[3] = {MPI_CXX_BOOL,MPI_INT,MPI_INT};
    MPI_Type_create_struct(3, block_lengths, displacements, types, data);
    MPI_Type_commit(data);
}

int main(int argc, char *argv[])
{


    MPI_Init(&argc,&argv);
    int rank,nProc;
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Comm_size(MPI_COMM_WORLD,&nProc);

    //il numero di righe per processo (senza contare il resto)
    int procRows = ROWS / nProc;
    //rank del processo sinistro
    int left = (rank + nProc - 1) % nProc;
    //rank del processo destro
    int right = (rank + nProc + 1) % nProc;

    if(rank == 0 && ROWS < nProc * 4)
    {
        printf("this wa-tor implementation requieres that the number of rows is at least four times bigger the number of precesses\n");
        MPI_Finalize();
        exit(0);
    }

    MPI_Datatype type;
    createCreatureType(&type);

    //questo serve per distrubuire il resto delle righe (se presenti)
    int extra = (rank < ROWS % nProc) ? 1 : 0;

    creature* matrix = new creature[(procRows + 4 + extra) * COLS];
    initMatrix(matrix,2,procRows + extra,COLS);

    double startTime;

    //setup process 0
    if(rank == 0)
    {
        matrix[V(2,0)].type = FISH;
        startTime = MPI_Wtime();
    }

    for(int t = 0;t < CYCLES;t++)
    {
        //aggiorna l'interno della matrice
        updateWorld(matrix,3,procRows - 2 + extra,true);


        MPI_Request request;

        if(nProc % 2 == 1 && rank == 0) //questo serve per gestire il caso di un numero dispari di processori
        {
            //invio parte di sinistra
            MPI_Isend(&matrix[V(2,0)],2 * COLS,type,left,0,MPI_COMM_WORLD,&request);
            //riceve aggiorna e reinvia il bordo di destra
            MPI_Recv(&matrix[V(procRows + 2 + extra,0)],COLS * 2,type,right,0,MPI_COMM_WORLD,nullptr);
            updateWorld(matrix, procRows + 1 + extra, 2,false);
            MPI_Isend(&matrix[V(procRows + 2 + extra,0)],2 * COLS,type,right,1,MPI_COMM_WORLD,&request);
            
            //riceve il bordo lavorato di sinistra
            MPI_Recv(&matrix[V(2,0)],COLS * 2,type,left,1,MPI_COMM_WORLD,nullptr);
          
        }
        else if(rank % 2 == 0) //i processi pari ricevono i bordi, li aggiornano e li rinviano
        {
            //si può notare overhead causato da idle dei processi che devono aspettare ambedue vicini di inviare i bordi
            //cerchiamo di tamponare, (anche se poco cambia visto che questo problema è load balanced)
            //ovvero se arriva prima il messaggio del processo P - 1, allora possiamo subito aggiornare
            MPI_Recv(matrix,COLS * 2,type,left,1,MPI_COMM_WORLD,nullptr);
            updateWorld(matrix, 1, 2,false);
            MPI_Isend(matrix,2 * COLS,type,left,0,MPI_COMM_WORLD,&request);


            MPI_Recv(&matrix[V(procRows + 2 + extra,0)],COLS * 2,type,right,0,MPI_COMM_WORLD,nullptr);
            updateWorld(matrix, procRows + 1 + extra, 2,false);
            MPI_Isend(&matrix[V(procRows + 2 + extra,0)],2 * COLS,type,right,1,MPI_COMM_WORLD,&request);
            
        }
        else //i processi dispari inviano i propri bordi e li ricevono
        {
            //invio i miei bordi con annesso vicino 
            //utilizzo un Send non bloccante per far subito computare i processi vicini,inviandoli il prima possibile entrambi
            MPI_Isend(&matrix[V(2,0)],2 * COLS,type,left,0,MPI_COMM_WORLD,&request);
            MPI_Isend(&matrix[V(procRows + extra,0)],2 * COLS,type,right,1,MPI_COMM_WORLD,&request);
      
            MPI_Recv(&matrix[V(2,0)],COLS * 2,type,left,1,MPI_COMM_WORLD,nullptr);
            MPI_Recv(&matrix[V(procRows + extra,0)],COLS * 2,type,right,0,MPI_COMM_WORLD,nullptr);
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
