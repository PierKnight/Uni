#include "wator/big/wator.cpp"

int main(int argc, char *argv[])
{

    creature* matrix = new creature[ROWS * COLS];
    double startTime;

    matrix[V(2,0)].type = FISH;
    startTime = clock();

    for(int t = 0;t < CYCLES;t++)
    {
        //aggiorna l'interno della matrice
        updateWorld(matrix,0,ROWS,true);
    }
    printf("TOTAL TIME %f\n",(clock() - startTime) / CLOCKS_PER_SEC);

    delete [] matrix;

    return 0;
}
