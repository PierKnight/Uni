#include <cstdio>
#include <omp.h>
#include <random>




double getPi(int totalTries,int round)
{
    omp_set_num_threads(omp_get_num_procs());

    int totalCirclePoints = 0;

    double start_time = omp_get_wtime();
    #pragma omp parallel 
    {

        int threadID = omp_get_thread_num();
        //create seed on thread using current time
        //unsigned int seed = (unsigned) time(NULL);
        
        //munge the seed using our thread number so that each thread has its
        //own unique seed, therefore ensuring it will generate a different set of numbers
        //unsigned int finalSeed = (seed & 0xFFFFFFF0) | (threadID + 1);

        //printf("My seed %d\n",finalSeed);

        
        int localCirclePoints = 0;

        #pragma omp for
        for(int i = 0;i < totalTries;i++)
        {
            unsigned int seed1 = (unsigned)i;
            unsigned int seed2 = (unsigned)i*i;
            double x = ((rand_r(&seed1) % (round + 1)) / (double)round) - 0.5;
            double y = ((rand_r(&seed2) % (round + 1)) / (double)round) - 0.5;

            if(x * x + y * y <= 0.25)
            {
                localCirclePoints += 1;
                //printf("X: %f, Y: %f\n",x,y);
            }
        }

        #pragma omp critical
        {
            totalCirclePoints += localCirclePoints;
        }
        
    }

    printf("Time: %f\n",(omp_get_wtime() - start_time));

    return ((double)totalCirclePoints / (double)totalTries) * 4.0;

}

int main(int argc, char const *argv[])
{
    double e = getPi(999999999,10000);
    printf("%f\n",e);
    return 0;
}
