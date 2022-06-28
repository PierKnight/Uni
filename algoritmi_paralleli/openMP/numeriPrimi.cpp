#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

bool isPrime(int number)
{
    if(number % 2 == 0)
        return false;

    for(int i = 3;i < number;i += 2)
        if(number % i == 0)
            return false;
    return true;
}

int main()
{
    double time = omp_get_wtime();

    int numeriPrimi = 0;

    omp_set_num_threads(1);
    printf("THREADS %d\n",omp_get_num_threads());
    
    #pragma omp parallel for schedule(guided) reduction(+:numeriPrimi)
    for(int i = 10000;i < 10000 + 1000;i++)
    {
         if(isPrime(i))
            numeriPrimi++;
    }
    
    printf("TIME: %f, totale: %d\n",omp_get_wtime() - time,numeriPrimi);

    return 0;
}