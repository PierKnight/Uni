#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

//embarassegly parallelism 
class Worker
{

    public:
    pthread_t id;
    int workerID;
    int lenght;

    int* vectorA;
    int* vectorB;

    Worker(int workerID,int vectorA[],int vectorB[],int size);
    void start();
};

void* run(void* arg)
{
    Worker worker = *(Worker*)arg;


    
    int slice = worker.lenght / 
    int start = worker.id * 

    for(int i = )


    return NULL;
}

Worker::Worker(int id,int va[],int vb[],int size):workerID(id),vectorA(va),vectorB(vb),lenght(size){}

void Worker::start()
{
    pthread_create(&id,NULL,&run,this);
}



int main(int argc, char const *argv[])
{





    int vectorA[] = {1,2,3};
    int vectorB[] = {1,2,3};


    Worker test(1,vectorA,vectorB,3);
    test.start();


    pthread_join(test.id,NULL);

    return 0;
}



