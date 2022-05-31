#include <stdio.h>
#include <mpi.h>
#define ROWS 10
#define COLS 10
#define V(R,C) ((R) * ROWS + (C))


void init(int* matrix)
{
    for(int i = 0;i < ROWS;i++)
    {
        for(int j = 0;j < COLS;j++)
            matrix[V(i,j)] = 0;
    }

    int halfI = ROWS / 2;
    int halfJ = COLS / 2;


    //GLIDER
    /*
        - * -
        - * *
        * * *
    */

   matrix[V(halfI - 1,halfJ)] = 1;
   matrix[V(halfI,halfJ)] = 1;
   matrix[V(halfI,halfJ + 1)] = 1;
   matrix[V(halfI + 1,halfJ - 1)] = 1;
   matrix[V(halfI + 1,halfJ)] = 1;
   matrix[V(halfI + 1,halfJ + 1)] = 1;
}


int main(int argc, char *argv[])
{
    MPI_Init(&argc, &argv);


    int totalSteps = 100;

    int* matriceA = new int[ROWS*COLS];
    int* matriceB = new int[ROWS*COLS];

    //utlizzare inline per poter lasciare al compilatore il lavoro di scrivere
    init(matriceA);

    double time = MPI_Wtime();

    for(int s = 0;s < totalSteps;s++)
    {
        //TODO codice grafico per mostrare matrice



         //swap
        int* temp = matriceB;
        matriceB = matriceA;
        matriceA = temp;
    }


    printf("%d.5",6.0/5.0);

    delete [] matriceA;
    delete [] matriceB;

    MPI_Finalize();
    
    return 0;
}


//PARTE PARALLELA
/*



*/
