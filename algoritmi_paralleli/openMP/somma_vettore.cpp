#include <omp.h>
#include <cstdio>


int sumVector(int vec[],const int size)
{
    //ogni utilizzo i core della macchina
    //attenzione aggiungere più thread non vuol dire che si ha un costante miglioramento
    //infatti potrebbe generare più overhead intaccando l'efficenza 
    omp_set_num_threads(6);

    int totalSum = 0;

    double startTime = omp_get_wtime();

    //inizializzo gli n thread, è come create_thread di posix
    #pragma omp parallel
    {
        int threadID = omp_get_thread_num();




        int localSum = 0;

        //in questo punto il for viene diviso fra tutti i thread correnti
        //quindi possiamo vedere questo blocco di codice come se ogni thread esegue la sua parte di for per poi
        //aggiungere il tutto nel suo localSum.
        #pragma omp for
        for(int i = 0;i < size;i++)
        {
            localSum += vec[i];
        }
        #pragma omp nowait
        //ad ogni for è presente un barrier implicito ma con no wait il thread continua lo stesso


        //è importante pochè la variabile totalSum è condivisa fra tutti i thread
        #pragma omp critical
        {
            totalSum += localSum;
        }

        printf("FINITO!!!: %d\n",threadID);

    }
    //barrier implicito


    double timeTaken = omp_get_wtime() - startTime;
    printf("Total TIme Taken: %f\n",timeTaken); 
    return totalSum;
}


int main(int argc, char const *argv[])
{
    const int SIZE = 10000;

    int vector[SIZE];

    for(int i = 0;i < SIZE;i++)
    {
        vector[i] = i;
    }

    int sum = sumVector(vector,SIZE);

    printf("SOMMA TOTALE: %d\n",sum);


    return 0;
}
