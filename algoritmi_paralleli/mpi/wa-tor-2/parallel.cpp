#include <mpi.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include "sequential.cpp"
#define CELL_SIZE 20



inline void sendWalls(MPI_Datatype type,creature* matrix,int rank,int nProc,MPI_Request* requests)
{
    
    //invio al processo prima di me
    MPI_Isend(&matrix[V(1,0)],COLS,type,(rank - 1 + nProc) % nProc,0,MPI_COMM_WORLD,&requests[0]);
    //invio al processo dopo di me
    MPI_Isend(&matrix[V(ROWS / nProc,0)],COLS,type,(rank + 1 + nProc) % nProc,0,MPI_COMM_WORLD,&requests[1]);

}


inline void receiveWalls(MPI_Datatype type,creature* matrix,int rank,int nProc)
{
    MPI_Status status;
    MPI_Recv(&matrix[V(0,0)],COLS,type,(rank - 1 + nProc) % nProc,0,MPI_COMM_WORLD,&status);
    MPI_Recv(&matrix[V(ROWS / nProc + 1,0)],COLS,type,(rank + 1 + nProc) % nProc,0,MPI_COMM_WORLD,&status);


    updateWorld(matrix,1,ROWS / nProc + 1);
    //updateWorld(matrix,ROWS / nProc,ROWS / nProc + 1);
}

void sendAndReceive(MPI_Datatype type,creature* matrix,int rank,int nProc)
{
    MPI_Status status;
    /*
    MPI_Sendrecv(&matrix[V(1,0)],COLS,type,(rank - 1 + nProc) % nProc,0,
         &matrix[V(0,0)],COLS,type,(rank - 1 + nProc) % nProc,0,MPI_COMM_WORLD,&status);

    MPI_Sendrecv(&matrix[V(ROWS / nProc,0)],COLS,type,(rank + 1 + nProc) % nProc,0,
         &matrix[V(ROWS / nProc + 1,0)],COLS,type,(rank + 1 + nProc) % nProc,0,MPI_COMM_WORLD,&status);
    */

   if(rank % 2 == 0)
   {
        MPI_Send(&matrix[V(1,0)],COLS,type,(rank - 1 + nProc) % nProc,0,MPI_COMM_WORLD);
        MPI_Send(&matrix[V(ROWS / nProc,0)],COLS,type,(rank + 1 + nProc) % nProc,1,MPI_COMM_WORLD);
        MPI_Recv(&matrix[V(0,0)],COLS,type,(rank - 1 + nProc) % nProc,1,MPI_COMM_WORLD,&status);
        MPI_Recv(&matrix[V(ROWS / nProc + 1,0)],COLS,type,(rank + 1 + nProc) % nProc,0,MPI_COMM_WORLD,&status);
   }
   else
   {
        MPI_Recv(&matrix[V(0,0)],COLS,type,(rank - 1 + nProc) % nProc,1,MPI_COMM_WORLD,&status);
        MPI_Recv(&matrix[V(ROWS / nProc + 1,0)],COLS,type,(rank + 1 + nProc) % nProc,0,MPI_COMM_WORLD,&status);
        MPI_Send(&matrix[V(1,0)],COLS,type,(rank - 1 + nProc) % nProc,0,MPI_COMM_WORLD);
        MPI_Send(&matrix[V(ROWS / nProc,0)],COLS,type,(rank + 1 + nProc) % nProc,1,MPI_COMM_WORLD);
   }

    //updateWorld(matrix,1,2);
    //updateWorld(matrix,ROWS / nProc,ROWS / nProc + 1);

    updateWorld(matrix,1,ROWS / nProc + 1);
}


inline void updateMatrix(creature* matrix,int nProc)
{

    //non è possibile farlo se le righe per ogni processo sono inferiori o uguali a 2
    if(ROWS / nProc <= 2) return;
    //aggiorno solamente la parte interna
    //updateWorld(matrix,2,ROWS / nProc - 1);
    
    //updateWorld(matrix,1,ROWS / nProc + 1);

}


inline void sendHaloCells(MPI_Datatype type,creature* matrix,int rank,int nProc)
{
    MPI_Send(&matrix[V(0,0)],COLS,type,(rank - 1 + nProc) % nProc,0,MPI_COMM_WORLD);
    MPI_Send(&matrix[V(ROWS / nProc + 1,0)],COLS,type,(rank + 1 + nProc) % nProc,0,MPI_COMM_WORLD);
}

inline void receiveUpdates(MPI_Datatype type,creature* matrix,int rank,int nProc)
{
    MPI_Status status;
    MPI_Recv(&matrix[V(1,0)],COLS,type,(rank - 1 + nProc) % nProc,0,MPI_COMM_WORLD,&status);
    MPI_Recv(&matrix[V(ROWS / nProc,0)],COLS,type,(rank + 1 + nProc) % nProc,0,MPI_COMM_WORLD,&status);
}

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
    for(int i = 0;i < ROWS;i++)
    {
        for(int j = 0;j < COLS;j++)
        {
            ALLEGRO_COLOR color;

            int type = matrix[V(i,j)].type;
            if(type == WATER)
                color = al_map_rgb(0,0,200);
            else if(type == FISH)
            {
                color = al_map_rgb(200,0,0);
                totalFish++;
            }
            else if(type == SHARK)
            {
                color = al_map_rgb(0,200,0);
                totalShark++;
            }

            if(matrix[V(i,j)].moved)
                printf("OH NO! %d, %d",i,j);

            al_draw_filled_rectangle(j * CELL_SIZE,i * CELL_SIZE,j * CELL_SIZE + CELL_SIZE,i * CELL_SIZE + CELL_SIZE,color);
        }
    }
    //printf("TOTALE PESCI %d\n",totalFish);
    //printf("TOTALE SQUALI %d\n",totalShark);
    al_flip_display();
}

int main(int argc, char *argv[])
{


    MPI_Init(&argc,&argv);
    int rank,nProc;
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Comm_size(MPI_COMM_WORLD,&nProc);

    srand (time(NULL));

    MPI_Datatype type;
    createCreatureType(&type);
    

    bool firstTime = true;

    creature* matrix = new creature[(ROWS + 2) / nProc * COLS];

    //MPI_Request* requests = new MPI_Request[2];


    //setup allegro
    
    ALLEGRO_DISPLAY* display;
    if(rank == 0)
    {
        printf("SETUP ALLEGRO\n");
        if(!al_init())
            printf("FUCK!\n");
        display = al_create_display(COLS * CELL_SIZE,ROWS * CELL_SIZE);
        if(!display)
            printf("failed to create display!\n");
        
        if(al_init_primitives_addon())
            printf("SETUP DONE\n");
        else
            printf("SETUP NOT DONE\n");
    }
    


    creature* allMatrix;

    if(rank == 0)
    {
        allMatrix = new creature[ROWS * COLS]; 
        //for(int i = 0;i < 10;i++)
        //    matrix[rand() % (ROWS / nProc * COLS)].type = FISH;
        matrix[V(2,0)].type = FISH;
    }
    while(true)
    {
    
        //receive new creatures moved from other processors
        //if(!firstTime)
        //    receiveUpdates(type,matrix,rank,nProc);
        firstTime = false;

        //processore 0 farà la gather di tutto e disegna la matrice, questo potrà essere facoltativo per il showcase

        int size = (ROWS / nProc) * COLS;
    
        
        MPI_Gather(&matrix[V(1,0)],size,type,allMatrix,size,type,0,MPI_COMM_WORLD);
        printf("GATHER!%d\n",rank);
        
        if(rank == 0)
        {
            drawWorld(allMatrix);
            printf("DRAW\n");
            al_rest(0.8);


            printf("VALUE: %d\n",matrix[ROWS / nProc + 1].type);
            
        }

        MPI_Barrier(MPI_COMM_WORLD);
        printf("BARRIER!%d\n",rank);
        
        //printf("UPDATE MATRIX!%d\n",rank);
        
        //updateMatrix(matrix,nProc);
    
        sendAndReceive(type,matrix,rank,nProc);



        //sendHaloCells(type,matrix,rank,nProc);

        printf("VALUE %d\n",matrix[V(ROWS / nProc + 1,0)].type);

        //MPI_Sendrecv(&matrix[V(0,0)],COLS,type,(rank - 1 + nProc) % nProc,0,&matrix[V(ROWS / nProc,0)],COLS,type,(rank + 1 + nProc) % nProc,0,MPI_COMM_WORLD,nullptr);
        
        
        matrix[V(ROWS / nProc + 1,0)].moved = false;
        MPI_Sendrecv(&matrix[V(ROWS / nProc + 1,0)],COLS,type,(rank + 1 + nProc) % nProc,0,&matrix[V(1,0)],COLS,type,(rank - 1 + nProc) % nProc,0,MPI_COMM_WORLD,nullptr);

        matrix[V(ROWS / nProc + 1,0)].type = WATER;
        printf("TEST %d\n",ROWS / nProc + 1);
    
    }

    
    
    if(rank == 0)
        al_destroy_display(display);
    MPI_Finalize();
    
    return 0;
}
