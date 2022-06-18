#include <mpi.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include "wator/big/wator.cpp"
#define CELL_SIZE 10

#define FISH_COLOR al_map_rgb(200,0,0)
#define SHARK_COLOR al_map_rgb(0,200,0)
#define WATER_COLOR al_map_rgb(0,0,200)


//mpiCC allegro_parallel.cpp $(pkg-config --libs allegro-5 allegro_main-5 allegro_primitives-5 )
//export DISPLAY=:0



inline void createCreatureType(MPI_Datatype* data)
{
    MPI_Aint displacements[3]  = {offsetof(creature,moved),offsetof(creature,energy),offsetof(creature,type)};
    int block_lengths[3]  = {1,1,1};
    MPI_Datatype types[3] = {MPI_CXX_BOOL,MPI_INT,MPI_INT};
    MPI_Type_create_struct(3, block_lengths, displacements, types, data);
    MPI_Type_commit(data);
}

inline void drawWorld(creature* matrix)
{
    int totalFish = 0;
    int totalShark = 0;
    al_clear_to_color(WATER_COLOR);
    al_hold_bitmap_drawing(true);
    for(int i = 0;i < ROWS;i++)
    {
        for(int j = 0;j < COLS;j++)
        {
            int index = V(i,j);
            int type = matrix[index].type;
            if(type == FISH)
            {
                al_draw_filled_rectangle(j * CELL_SIZE,i * CELL_SIZE,j * CELL_SIZE + CELL_SIZE,i * CELL_SIZE + CELL_SIZE,FISH_COLOR);
                totalFish++;
            }
            else if(type == SHARK)
            {
                al_draw_filled_rectangle(j * CELL_SIZE,i * CELL_SIZE,j * CELL_SIZE + CELL_SIZE,i * CELL_SIZE + CELL_SIZE,SHARK_COLOR);
                totalShark++;
            }
        }
    }
    printf("TOTALE PESCI %d\n",totalFish);
    printf("TOTALE SQUALI %d\n",totalShark);
    al_hold_bitmap_drawing(false);
    al_flip_display();
}

int main(int argc, char *argv[])
{


    MPI_Init(&argc,&argv);
    int rank,nProc;
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Comm_size(MPI_COMM_WORLD,&nProc);

    //il numero di righe per processo (senza contare il resto)
    int procRows = ROWS / nProc;

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

    

    creature* drawMatrix;
    //questi array saranno necessari per definire il messaggio di gatherv
    int* recvcounts;
    int* disp;
    double startTime;

    

    ALLEGRO_EVENT_QUEUE* queue = nullptr;
    ALLEGRO_EVENT ev;

    //setup process 0
    ALLEGRO_DISPLAY* display;
    if(rank == 0)
    {
        printf("SETUP ALLEGRO\n");
        if(!al_init())
            printf("Failed Init allegro!\n");
        display = al_create_display(COLS * CELL_SIZE,ROWS * CELL_SIZE);
        if(!display)
            printf("failed to create display!\n");
        
        if(al_init_primitives_addon())
            printf("SETUP DONE\n");
        else
            printf("SETUP NOT DONE\n");

        queue = al_create_event_queue();
        al_register_event_source(queue, al_get_display_event_source(display));


        drawMatrix = new creature[ROWS * COLS];

        recvcounts = new int[nProc];
        disp = new int[nProc];
        int spacing = 0;
        for(int i = 0;i < nProc;i++)
        {
            recvcounts[i] = (procRows + (i < (ROWS % nProc) ? 1 : 0)) * COLS;
            disp[i] = spacing;
            spacing += recvcounts[i];
        }
        startTime = MPI_Wtime();

    }
    if(rank == 1)
        matrix[V(2,0)].type = FISH;

    bool exit = false;

    while(!exit) 
    {

        if(rank == 0)
        {
            if(!al_is_event_queue_empty(queue))
            {
                do {
    				al_wait_for_event(queue, &ev);
    				if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
    					exit = true;
                        MPI_Abort(MPI_COMM_WORLD,0);
    					break;
    				}
    			} while(!al_is_event_queue_empty(queue));
            }
        }
        

        //aggiorna l'interno della matrice
        updateWorld(matrix,3,procRows - 2 + extra,true);
        
        MPI_Request request;

        if(nProc % 2 == 1 && rank == 0) //questo serve per gestire il caso di un numero dispari di processori
        {
            //invio parte di sinistra
            MPI_Isend(&matrix[V(2,0)],2 * COLS,type,(rank + nProc - 1) % nProc,0,MPI_COMM_WORLD,&request);
            //riceve aggiorna e reinvia il bordo di destra
            MPI_Recv(&matrix[V(procRows + 2 + extra,0)],COLS * 2,type,(rank + nProc + 1) % nProc,0,MPI_COMM_WORLD,nullptr);
            updateWorld(matrix, procRows + 1 + extra, 2,false);
            MPI_Isend(&matrix[V(procRows + 2 + extra,0)],2 * COLS,type,(rank + nProc + 1) % nProc,1,MPI_COMM_WORLD,&request);
            
            //riceve il bordo lavorato di sinistra
            MPI_Recv(&matrix[V(2,0)],COLS * 2,type,(rank + nProc - 1) % nProc,1,MPI_COMM_WORLD,nullptr);
          
        }
        else if(rank % 2 == 0) //i processi pari ricevono i bordi, li aggiornano e li rinviano
        {
            //si può notare overhead causato da idle dei processi che devono aspettare ambedue vicini di inviare i bordi
            //cerchiamo di tamponare, (anche se poco cambia visto che questo problema è load balanced)
            //ovvero se arriva prima il messaggio del processo P - 1, allora possiamo subito aggiornare
            MPI_Recv(matrix,COLS * 2,type,(rank + nProc - 1) % nProc,1,MPI_COMM_WORLD,nullptr);
            updateWorld(matrix, 1, 2,false);
            MPI_Isend(matrix,2 * COLS,type,(rank + nProc - 1) % nProc,0,MPI_COMM_WORLD,&request);


            MPI_Recv(&matrix[V(procRows + 2 + extra,0)],COLS * 2,type,(rank + nProc + 1) % nProc,0,MPI_COMM_WORLD,nullptr);
            updateWorld(matrix, procRows + 1 + extra, 2,false);
            MPI_Isend(&matrix[V(procRows + 2 + extra,0)],2 * COLS,type,(rank + nProc + 1) % nProc,1,MPI_COMM_WORLD,&request);
            
        }
        else //i processi dispari inviano i propri bordi e li ricevono
        {
            //invio i miei bordi con annesso vicino 
            //utilizzo un Send non bloccante per far subito computare i processi vicini,inviandoli il prima possibile entrambi
            MPI_Isend(&matrix[V(2,0)],2 * COLS,type,(rank + nProc - 1) % nProc,0,MPI_COMM_WORLD,&request);
            MPI_Isend(&matrix[V(procRows + extra,0)],2 * COLS,type,(rank + nProc + 1) % nProc,1,MPI_COMM_WORLD,&request);
      
            MPI_Recv(&matrix[V(2,0)],COLS * 2,type,(rank + nProc - 1) % nProc,1,MPI_COMM_WORLD,nullptr);
            MPI_Recv(&matrix[V(procRows + extra,0)],COLS * 2,type,(rank + nProc + 1) % nProc,0,MPI_COMM_WORLD,nullptr);
        }

        //utilizzo gatherv per poter raccogliere sub-matrix di dimensione differente a causa del possibile resto dato da ROWS % nProc
        MPI_Gatherv(&matrix[V(2,0)],(procRows + extra) * COLS,type,drawMatrix,recvcounts,disp,type,0,MPI_COMM_WORLD);
        if(rank == 0)
        {
            drawWorld(drawMatrix);
            al_rest(0.1);
        }
        
    
    }



    if(rank == 0)
    {
        printf("TOTAL TIME %f\n",MPI_Wtime() - startTime);
        al_destroy_event_queue(queue);
        al_destroy_display(display);
        delete [] drawMatrix;
        delete [] recvcounts;
        delete [] disp;
    }

    delete [] matrix;
    MPI_Type_free(&type);
    MPI_Finalize();
    
    return 0;
}
