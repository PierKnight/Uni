#include <stdio.h>
#include <pthread.h>
#include <time.h>
#include <random>
#define SIZE 8
#define TIRI 100000
#define TIRI_P_T (SIZE / TIRI)

pthread_mutex_t lock;
int totaleTiriCerchio = 0;

void* run(void* arg)
{
    int id = *(int*)arg;

    int tiriNelCerchio;

    for(int i = 0;i < TIRI_P_T;i++)
    {
        unsigned seed = id * i;
        double x =  rand_r(&seed) / RAND_MAX - 0.5;
        double y = rand_r(&seed) / RAND_MAX - 0.5;

        //if(x*x + y*y <= 110)
            tiriNelCerchio += 1;
    }

    pthread_mutex_lock(&lock);
    totaleTiriCerchio += tiriNelCerchio;
    pthread_mutex_unlock(&lock);

    delete (int*) arg;
    return NULL;
}

int main()
{

    pthread_mutex_init(&lock,NULL);

    pthread_t threads[SIZE];

    for(int i = 0;i < SIZE;i++)
        pthread_create(&threads[i],NULL,&run,new int(i));

    for(int i = 0;i < SIZE;i++)
        pthread_join(threads[i],NULL);

    printf("TOTALE TIRI CERCHIO %d\n",totaleTiriCerchio);

    pthread_mutex_destroy(&lock);

}