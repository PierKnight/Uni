#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#define SIZE 10



//indica il numero di macchina in attesa sulla i-esima strada
int quadrivio[4];

pthread_mutex_t lock[4];
//condizione grazie alla quale solo una macchina passa per volta
pthread_cond_t condition[4];

pthread_mutex_t incrocioLock;

void destraLibera(int strada,bool& libera)
{
    pthread_mutex_lock(&lock[(strada + 1) % 4]);
    if(quadrivio[(strada + 1) % 4] == 0)
        libera = true;
    pthread_mutex_unlock(&lock[(strada + 1) % 4]);
}

void* macchina(void* arg)
{
    int id = rand() % 4;
    sleep(1 + rand() % 3);
    
    pthread_mutex_lock(&lock[id]);
    quadrivio[id]++;

    while(quadrivio[id] > 1)
        pthread_cond_wait(&condition[id],&lock[id]);

    pthread_mutex_lock(&incrocioLock);

    bool libera = false;

    do
    {
        destraLibera(id,libera);
        
    }
    while(!libera);
    
    printf("PASSATO MACCHINA %d\n",id);

    pthread_mutex_unlock(&incrocioLock);

    quadrivio[id]--;
    pthread_cond_signal(&condition[id]);
    
    pthread_mutex_unlock(&lock[id]);

    return NULL;
}

int main()
{
    pthread_t threads[SIZE];
    
    srand(time(NULL));
    
    for(int i = 0;i < 4;i++)
    {
        pthread_mutex_init(&lock[i],NULL);
        pthread_cond_init(&condition[i],NULL);
    }
    pthread_mutex_init(&incrocioLock,NULL);

    for(int i = 0;i < SIZE;i++)
    {
        pthread_create(&threads[i],NULL,&macchina,NULL);
    }

    for(int i = 0;i < SIZE;i++)
    {
        pthread_join(threads[i],NULL);
    }

    for(int i = 0;i < 4;i++)
    {
        pthread_mutex_destroy(&lock[i]);
        pthread_cond_destroy(&condition[i]);
    }
    pthread_mutex_destroy(&incrocioLock);

}