#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <vector>

class World
{
    public:
    std::vector<bool> slots;
    pthread_mutex_t lock;

    World(int space):slots(space,false){}

};

class Formica
{
    
    public:
    World* world;
    int pos;
    int direction;
    pthread_t thread;
    
    Formica(World* w,int p):world(w),pos(p)
    {
    }

    void move()
    {
        if(pos + direction >= world -> slots.size() || pos + direction < 0)
        {
            direction *= -1;
            return;
        }
    
        if(world -> slots[pos + direction])
        {
            direction *= -1;
            return;
        }

        world -> slots[pos] = false;
        pos += direction;
        world -> slots[pos] = true;
    }   
};

void* runFormica(void* arg)
{
    Formica formica = *(Formica*)arg;


    pthread_mutex_lock(&formica.world -> lock);
    formica.world -> slots[formica.pos] = true;
    if(rand() % 2 == 0)
        formica.direction = 1;
    else
        formica.direction = -1;
    pthread_mutex_unlock(&formica.world -> lock);



    while(true)
    {
        sleep(rand() % 3);

        pthread_mutex_lock(&formica.world -> lock);
        formica.move();

        for(int i = 0;i < formica.world -> slots.size();i++)
        {
            if(formica.world -> slots[i])
                printf("x");
            else
                printf("-");
        }
        printf("\n");
        pthread_mutex_unlock(&formica.world -> lock);
    }
    return NULL;
}







int SIZE = 10;
int ANT_AMOUNT = 6;

int main()
{   

    if(ANT_AMOUNT >= SIZE)
        return 0;

    World world(10);
    pthread_mutex_init(&world.lock,NULL);

    std::vector<int> validSlots;
    for(int i = 0;i < SIZE;i++)
        validSlots.push_back(i);


    std::vector<Formica> formiche;

    srand(time(NULL));


    for(int i = 0;i < ANT_AMOUNT;i++)
    {

        int posList = rand() % validSlots.size();
        Formica formica(&world,validSlots[posList]);

        
        pthread_create(&formica.thread,NULL,&runFormica,&formica);


        validSlots.erase(validSlots.begin() + posList);
        formiche.push_back(formica);
    }

    for(int i = 0;i < ANT_AMOUNT;i++)
        pthread_join(formiche[i].thread,NULL);

    pthread_mutex_destroy(&world.lock);

    return 0;
}

