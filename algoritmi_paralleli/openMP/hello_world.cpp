#include <omp.h>
#include <cstdio>
#include <string>

int main(int argc, char const *argv[])
{


    int totalCores = omp_get_num_procs();

    printf("Total Cores %d\n",totalCores);

    omp_set_num_threads(totalCores);

    int numProc;

    std::string variabileCondivisa = "eee";
    
    #pragma omp parallel private(numProc)
    {
        numProc = omp_get_thread_num();

        printf("Io sono il thread numero: %d\n",numProc);

        #pragma omp critical //il blocco di codice è adesso atomico per thread, proprio come usare un mutex lock and unlock
        {
            variabileCondivisa += std::to_string(numProc);
        }
    
    }
    //implicit barrier

    printf("Tutti hanno finito %s!\n",variabileCondivisa.c_str());
    return 0;
}
