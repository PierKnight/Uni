#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>


pthread_mutex_t mutex;


class Test
{
    private: 

    int* valoreCondiviso;
    int incremento;

    public:

    Test(int* valore,int incremento)
    {
        this -> valoreCondiviso = valore;
        this -> incremento = incremento;
    }

    void incrementa()
    {
        pthread_mutex_lock(&mutex);
        this -> valoreCondiviso += 1;
        pthread_mutex_unlock(&mutex);
    }
};

void* run(void* arg)
{
    for(int i = 0;i < 1000000;i++)
    {
        pthread_mutex_lock(&mutex);
        *(int*)arg += 1;
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}




int main()
{

    pthread_mutex_init(&mutex,NULL);


    int num = 0;

    pthread_t thread_1;
    pthread_t thread_2;


    pthread_create(&thread_1,NULL, &run,&num);
    pthread_create(&thread_2,NULL, &run,&num);


    pthread_join(thread_1,NULL); // il main thread entra in wait fino a quando non finisce thread 1
    pthread_join(thread_2,NULL); // il main thread entra in wait fino a quando non finisce thread 2

    //il lock nel contesto posix si chiama MUTEX

    printf("Num: %d \n", num);

    pthread_mutex_destroy(&mutex);

    return 0;
}