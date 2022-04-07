#include <omp.h>
#include <cstdio>

//il comando per compilare è g++ -fopenmp <nome file>
//thread safe rand_r

int main(int argc, char const *argv[])
{
    int tid = 0;
    int test = 5;
    //firstprivate vuol dire che ogni thread ha una privata variabile con il valore originario dato dal main thread
    //usare semplicemente private, lo resetta a 0
    #pragma omp parallel private(tid) firstprivate(test)
        {
            //i for dentro un programma ha un barrier implicito in seguito
            //per prendere il tempo si usa omp_get_wtime()
            tid = omp_get_thread_num(); //ottengo il thread id
            printf("Sono il thread numero: %d \n",tid);

            if(tid == 0) //solo il master thread entra in questo if
            {
                printf("Il MASTER: %d\n",test);
            }

            //SI PUO DEFINIRE UNA ZONA CRITICA CON
            //#pragma omp critical { <blocco di codice atomico>}

        }
        //barriera implicita
        //gcc permette opzioni di ottimizzare compilationi come con certi comandi come ad esempio -O3
        //O3 ottimizza l'esecuzione però riduce la precisione dei calcoli ed aumenta l'uso di RAM
    return 0;
}
