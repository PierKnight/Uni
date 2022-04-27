#include <cstdio>
#include <omp.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{   
    int NUM_STEPS = 1000000000;

    if(argc > 1)
    {
        char* w;
        NUM_STEPS = strtol(argv[1],&w,10);
    }

    const double step = 1.0 / (double)NUM_STEPS;

    double pi = 0;

    omp_set_num_threads(8);

    long beforeTime = omp_get_wtime();
    #pragma omp parallel
    {
        double sum = 0;

        #pragma omp for schedule (static)
        for(int i = 0;i < NUM_STEPS;i++)
        {
            double x = step * i;
            sum += 4.0 / (1.0 + x * x);
        }

        #pragma omp reduction(+:pi)
        {
            pi += sum * step;
        }
    }

    printf("IL PI è %.10f\n",pi);
    printf("NEL TEMPO %f\n",omp_get_wtime() - beforeTime);


    return 0;
}




