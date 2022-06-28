#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char const *argv[])
{

    int somma = 0;
    int TEST = 10;

    #pragma omp parallel firstprivate(TEST)
    {
        int id = omp_get_thread_num();
        #pragma omp for schedule(static,1)
        for(int sos = 0;sos < 15;sos++)
        {
            printf("THREAD stampa %d\n",id);
        }
    }

   #pragma omp parallel num_threads(2)
    {
        int id = omp_get_thread_num();

        printf("FORK %d\n",id);
    
        #pragma omp for
        for(int i = 0;i < 10;i++)
            if(id == 0 && i == 0)
                sleep(1);
        printf("JOIN %d\n",id);
    }


    printf("SOMMA %d\n",somma);

    return 0;
}
