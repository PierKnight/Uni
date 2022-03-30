#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

int fuel = 0;
int numT = 3;


const int MAX_CAPACITY = 1000;

pthread_mutex_t mutex;
pthread_cond_t condition;



void* filler(void* arg)
{
    while(true)
    {
        sleep(1);
        pthread_mutex_lock(&mutex);
        while(fuel + 50 > MAX_CAPACITY)
            pthread_cond_wait(&condition,&mutex);

        fuel += 20;
        printf("Filler ha messo: fuel count %d",fuel);
        pthread_cond_broadcast(&condition);
        pthread_mutex_unlock(&mutex);
    }

    return NULL;
}

void* car(void* arg)
{
    while(true)
    {
        sleep(1);
        pthread_mutex_lock(&mutex);
        while(fuel < 50)
            pthread_cond_wait(&condition,&mutex);

        fuel -= 50;
        printf("Macchina ha consumato: fuel count %d",fuel);
        pthread_cond_broadcast(&condition);
        pthread_mutex_unlock(&mutex);
    }

    return NULL;
}


int main(int argc, char const *argv[])
{
    

    pthread_mutex_init(&mutex,NULL);
    pthread_cond_init(&condition,NULL);

    pthread_t threads[numT];

    for(int i = 0;i < numT;i++)
    {
        int var;
        if(i < numT / 2)
            var = pthread_create(&threads[i],NULL,&filler,NULL);
        else
            var = pthread_create(&threads[i],NULL,&car,NULL);

    }
    for(int i = 0;i < numT;i++)
        pthread_join(threads[i],NULL);


    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&condition);





    return 0;
}
