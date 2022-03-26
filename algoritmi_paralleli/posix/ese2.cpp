#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>


struct Container
{
    int* num0;
    int* num1;

    Container()
    {
        num0 = new int(0);
        num1 = new int(0);
    }

    ~Container()
    {
        delete num0;
        delete num1;
    }
};

pthread_mutex_t mutex0;

void* run0(void* arg)
{
    Container cont = *(Container*)arg;
    for(int i = 0;i < 10000;i++)
    {
        pthread_mutex_lock(&mutex0);
        *cont.num0 += 1;
        *cont.num1 -= 1;
        pthread_mutex_unlock(&mutex0);
    }
    return NULL;
}





int main()
{

    pthread_mutex_init(&mutex0,NULL);



    Container container = Container();

    pthread_t thread_1;
    pthread_t thread_2;


    pthread_create(&thread_1,NULL, &run0,&container);
    pthread_create(&thread_2,NULL, &run0,&container);


    pthread_join(thread_1,NULL); // il main thread entra in wait fino a quando non finisce thread 1
    pthread_join(thread_2,NULL); // il main thread entra in wait fino a quando non finisce thread 2

    //il lock nel contesto posix si chiama MUTEX

    printf("Num 0: %d \n", *container.num0);
    printf("Num 1: %d \n", *container.num1);


    pthread_mutex_destroy(&mutex0);

    return 0;
}