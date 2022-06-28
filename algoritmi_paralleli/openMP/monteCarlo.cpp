#include <omp.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc,const char** args)
{
    if(argc < 2)
    {
        printf("Sono necessari almeno un argomento\n");
        exit(0);
    }

    int lanciTotali = atoi(args[1]);
    int totaleCerchi = 0;
    double r = 0.5;

    #pragma omp parallel shared(lanciTotali,r)
    {
        unsigned id = omp_get_thread_num();

        #pragma for schedule(guided,3) reduction(+:totaleCerchi)
        for(int i = 0;i < lanciTotali;i++)
        {
            unsigned seed = i * id;
            double x = (double)rand_r(&seed) / (double)RAND_MAX - 0.5;
            double y = (double)rand_r(&seed) / (double)RAND_MAX - 0.5;

            if((x*x + y*y) <= r*r)
                totaleCerchi += 1;
        }
    }

    printf("PI %f\n",((double)totaleCerchi / (double)lanciTotali) * 4.0);

    return 0;
}