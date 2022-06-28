#include <pthread.h>
#include <stdio.h>
#define SIZE 8
#define RANGE 100000
#define FROM 100000
pthread_mutex_t lockValue;
pthread_mutex_t lockResult;
int value = FROM;
int result = 0;

int getCurrentValueAndIncrease()
{
    int calc = -1;
    pthread_mutex_lock(&lockValue);
    if(value < FROM + RANGE)
    {
        calc = value;
        value += 1;
    }
    pthread_mutex_unlock(&lockValue);
    return calc;
}

bool isPrime(int number)
{
    if(number % 2 == 0)
        return false;

    for(int i = 3;i < number;i += 2)
        if(number % i == 0)
            return false;
    return true;
}

void* run(void* args)
{
    int* array = (int*) args;

    int total = 0;
    int v = getCurrentValueAndIncrease();    
    while (v != -1)
    {
        if(isPrime(v))
        {
            total += 1;
        }
        v = getCurrentValueAndIncrease();
    } 

    pthread_mutex_lock(&lockResult);
    result += total;
    pthread_mutex_unlock(&lockResult);

    return NULL;
}

int main()
{

    pthread_t threads[SIZE];
    pthread_mutex_init(&lockValue,NULL);
    pthread_mutex_init(&lockResult,NULL);
    

    for(int i = 0;i < SIZE;i++)
    {
        int result = pthread_create(&threads[i],NULL,&run,NULL);
    }

    for(int i = 0;i < SIZE;i++)
        pthread_join(threads[i],NULL);

    printf("RESULT: %d\n",result);    
    pthread_mutex_destroy(&lockResult);
    pthread_mutex_destroy(&lockValue);
    return 0;
}