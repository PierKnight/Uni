#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <thread>


class VectorWorker
{
    private:
    int from;
    int to;
    int* vector;

    public:
    VectorWorker(int f,int t,int vec[]): from(f),to(t),vector(vec){}


    int getFrom() const { return from; }
    int getTo() const { return to; }
    int* getVec() { return vector; }
};


void* launchWorker(void* arg)
{
    VectorWorker worker = *(VectorWorker*)arg;


    printf("----from %d, to %d\n",worker.getFrom(),worker.getTo());

    int* total = new int(0);

    for(int i = worker.getFrom();i < worker.getTo(); i++)
    {
        (*total) += worker.getVec()[i];
    }


    delete (VectorWorker*)arg;

    

    return total;
}


int sum(int vector[],int size)
{

    printf("START\n");



    int numProcessors = std::thread::hardware_concurrency();

    
    int step = size / numProcessors;
    

    while(step == 0)
    {
        numProcessors -= 1;
        step = size / numProcessors;
    }

    
    pthread_t threads[numProcessors];
    
    for(int i = 0;i < numProcessors - 1;i++)
    {
        VectorWorker* worker = new VectorWorker(i * step,(i + 1) * step,vector);
        pthread_create(&threads[i],NULL,&launchWorker,worker);
    }

    VectorWorker* worker = new VectorWorker((numProcessors - 1) * step,size,vector);
    pthread_create(&threads[numProcessors - 1],NULL,&launchWorker,worker);
    
    
    int result = 0;

    
    for(int i = 0;i < numProcessors;i++)
    {
        void* value;
        pthread_join(threads[i],&value); //continua solo sopo la conclusione di tutti gli altri,è come una BARRIER!
        result += *(int*)value;
        delete (int*) value;
    }
    
    return result;
}


int main(int argc, char *argv[])
{
 
    int vector[] = {1,2,3,4,5,6,7,8,9,10};
    int total = sum(vector, 10);
    printf("Total sum of the vector is %d\n",total);

    return 0;
}

