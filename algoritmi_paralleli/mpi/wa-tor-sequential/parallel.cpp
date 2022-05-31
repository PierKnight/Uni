#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include "sequential.cpp"
#define CELL_SIZE 1



//compilazione g++ <file> -lallegro
//g++ parallel.cpp $(pkg-config --libs allegro-5 allegro_main-5 allegro_primitives-5)
//mpiCC parallel.cpp $(pkg-config --libs allegro-5 allegro_main-5 allegro_primitives-5 )
//export DISPLAY=:0


inline void drawWorld(creature* matrix)
{
    int totalFish = 0;
    int totalShark = 0;

    al_clear_to_color(al_map_rgb(0,0,200));

    for(int i = 0;i < ROWS;i++)
    {
        for(int j = 0;j < COLS;j++)
        {
            ALLEGRO_COLOR color;

            int type = matrix[V(i,j)].type;
            if(type == FISH)
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

            if(type > 0)
                al_draw_filled_rectangle(j * CELL_SIZE,i * CELL_SIZE,j * CELL_SIZE + CELL_SIZE,i * CELL_SIZE + CELL_SIZE,color);
        }
    }
    printf("TOTALE PESCI %d\n",totalFish);
    //printf("TOTALE SQUALI %d\n",totalShark);
    al_flip_display();
}

int main(int argc, char *argv[])
{

    creature* matrix = new creature[ROWS * COLS];


    //setup allegro
    ALLEGRO_DISPLAY* display;
   
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
    

    time_t startTime,endTime;
    matrix[V(0,0)].type = FISH;
    
    time(&startTime);

    printf("WEWW\n");


    for(int t = 0;t < 1000;t++)
    {
        srand (time(NULL));
        updateWorld(matrix,0,ROWS);
        //drawWorld(matrix);


        //al_rest(0.001);
    }


    
    time(&endTime);
    printf("TOTAL TIME %f\n",double(endTime - startTime));
    al_destroy_display(display);
    
    return 0;
}
