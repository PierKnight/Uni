#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>


const int n = 10;
int buffer[n];
int size = 0;
pthread_mutex_t mutex;
pthread_cond_t condFull;
pthread_cond_t condEmpty;

void* produce(void*)
{
    while(true)
    {
        sleep(1 + (rand() % 3) / 2);
        pthread_mutex_lock(&mutex);

        while(size >= n)
            pthread_cond_wait(&condFull,&mutex);

        buffer[size] = rand() % 10;
        printf("Inserito numero: %d nello slot %d \n", buffer[size],size);
        ++size;

        pthread_cond_broadcast(&condEmpty);
        pthread_mutex_unlock(&mutex);
    }
}

void* consume(void*)
{
    while(true)
    {
        sleep(1 + (rand() % 3) / 2);
        pthread_mutex_lock(&mutex);

        while(size <= 0)
            pthread_cond_wait(&condEmpty,&mutex);

        printf("HO preso il numero: %d nello slot %d \n", buffer[size - 1],size - 1);
        --size;

        pthread_cond_broadcast(&condFull);
        pthread_mutex_unlock(&mutex);
    }
}

int main(int argc, char const *argv[])
{

    pthread_mutex_init(&mutex,NULL);
    pthread_cond_init(&condFull,NULL);
    pthread_cond_init(&condEmpty,NULL);

    pthread_t test1;
    pthread_t test2;

    pthread_create(&test1,NULL,&produce,NULL);
    pthread_create(&test2,NULL,&consume,NULL);




    pthread_join(test1,NULL);
    pthread_join(test2,NULL);





    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&condFull);
    pthread_cond_destroy(&condEmpty);
    
    return 0;
}
