#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/keyboard.h>
#include "sequential.cpp"
#include "creature.cpp"
#include <stdio.h>
#define WATER_C al_map_rgb(0,30,140)
#define CELL_SIZE 20


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
                color = WATER_C;
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

            al_draw_filled_rectangle(j * CELL_SIZE,i * CELL_SIZE,j * CELL_SIZE + CELL_SIZE,i * CELL_SIZE + CELL_SIZE,color);
        }
    }
    printf("TOTALE PESCI %d\n",totalFish);
    printf("TOTALE SQUALI %d\n",totalShark);
    al_flip_display();
}



//compilazione g++ <file> -lallegro
//g++ allegro.cpp $(pkg-config --libs allegro-5 allegro_main-5 allegro_primitives-5)
//g++ allegro.cpp $(pkg-config --libs allegro-5 allegro_main-5 allegro_primitives-5 )
//export DISPLAY=:0
int main(int argc, char *argv[])
{

    srand (time(NULL));
    bool initialize = al_init();

    if(!initialize)
    {
        printf("FAILED TO INITIALIZE\n");
        return -1;
    }

    //al_set_new_display_flags(ALLEGRO_WINDOWED);
    ALLEGRO_DISPLAY* display = al_create_display(COLS * CELL_SIZE,ROWS * CELL_SIZE);

    if(!display)
    {
        printf("failed to create display!\n");
        return -1;
    }

    
    al_init_primitives_addon();
    al_install_keyboard();

    
    ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue();
    al_register_event_source(queue,al_get_display_event_source(display));

    ALLEGRO_EVENT ev;


    
    creature* matrix = new creature[ROWS * COLS];


    
    for(int i = 0;i < ROWS * COLS;i++)
    {
        int val = rand() % 3;
        matrix[i].type = val == 0 ? WATER : (val == 1 ? FISH : WATER);
        if(val == 2)
        {
            matrix[i].type = SHARK;
            matrix[i].energy = START_ENERGY;
        }
        else if(val == 1)
            matrix[i].energy = 1;
    }
    while(true)
    {

        srand (time(NULL));
        
        drawWorld(matrix);
        updateWorld(matrix,0,ROWS);
        

        al_rest(0.1);    


        if(!al_event_queue_is_empty(queue))
        {
            al_wait_for_event(queue,&ev);
            if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
                break;
        }
    
        
        
    }
    

    delete [] matrix;
    printf("CLOSE\n");


    al_destroy_display(display);

    return 0;
}
