#include <mpi.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include "sequential.cpp"
#define CELL_SIZE 20



//compilazione g++ <file> -lallegro
//g++ parallel.cpp $(pkg-config --libs allegro-5 allegro_main-5 allegro_primitives-5)
//mpiCC parallel.cpp $(pkg-config --libs allegro-5 allegro_main-5 allegro_primitives-5 )
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
    printf("TOTALE PESCI %d\n",totalFish);
    //printf("TOTALE SQUALI %d\n",totalShark);
    al_flip_display();
}

int main(int argc, char *argv[])
{


    MPI_Init(&argc,&argv);
    int rank,nProc;
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Comm_size(MPI_COMM_WORLD,&nProc);

    MPI_Datatype type;
    createCreatureType(&type);


    MPI_Datatype borderType;

    int lenghts[] = {COLS * 2,COLS * 2};
    int displacements[] = {0,(ROWS / nProc - 2) * COLS};
    
    MPI_Type_indexed(2,lenghts,displacements,type,&borderType);
    MPI_Type_commit(&borderType);

    creature* matrix = new creature[ROWS / nProc * COLS];


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

    double startTime;
    if(rank == 0)
    {
        allMatrix = new creature[ROWS * COLS]; 
        //for(int i = 0;i < 10;i++)
        //    matrix[rand() % (ROWS / nProc * COLS)].type = FISH;
        matrix[V(5,5)].type = FISH;
        startTime = MPI_Wtime();
    }

    for(int t = 0;t < 1000;t++)
    {
        srand (time(NULL) * rank);


        int size = ROWS / nProc * COLS;
    

        //aggiorna quello che può aggiornare
        updateWorld(matrix,1,ROWS / nProc - 1,false);

        //raccogli tutto nel root
        MPI_Gather(matrix,1,borderType,allMatrix,1,borderType,0,MPI_COMM_WORLD);
        

        //aggiorna i bordi e disegna
        if(rank == 0)
        {
            

            //printf("AGG %d\n",allMatrix[V(15,0)]);
            //aggiorno i bordi nel master
            for(int i = 0;i < nProc;++i)
            {
                int row = i * (ROWS / nProc);
                int row2 = i == 0 ? ROWS - 1 : row - 1;
                //int row2 = row - 1;
                
                updateWorld(allMatrix,row2,row2 + 1,true);
                updateWorld(allMatrix,row,row + 1,true);
            }


            //drawWorld(allMatrix);
            //al_rest(0.4);
        }

        //reinvia tutto
        MPI_Scatter(allMatrix,1,borderType,matrix,1,borderType,0,MPI_COMM_WORLD);
    
    }

    

    
    
    if(rank == 0)
    {
        printf("TOTAL TIME %f\n",MPI_Wtime() - startTime);
        al_destroy_display(display);
    }
    MPI_Finalize();
    
    return 0;
}
