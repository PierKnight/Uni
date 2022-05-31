#ifndef SEQUENTIAL_WATOR
#define SEQUENTIAL_WATOR
#include <stdio.h>
#define ROWS 30
#define COLS 30
#define V(R,C) ((R) * COLS + (C))
#define fish(F) F > 0 && F < 10000 
#define shark(F) F >= 10000 
//fish stats
#define FISH_TRESHHOLD 3
//shark stats
#define START_ENERGY 1
#define SHARK_TRESHHOLD 10
#define EAT_ENERGY 1


int mod(int a, int b) { return a >= 0 ? a % b : ( b - abs ( a%b ) ) % b; }

int* getNewMatrix(bool r)
{
    int* matrix = new int[ROWS * COLS];    
    for(int i = 0;i < ROWS * COLS;i++)
    {
        if(!r)
        {
            matrix[i] = 0;
            continue;
        }

        int val = rand() % 3;

        if(val == 0)
            matrix[i] = 1;
        else if(val == 1)
            matrix[i] = 10000 + START_ENERGY;
        else matrix[i] = 0;
    }

    return matrix;
}

void swapArray( int **a, int **b )
{
    int *tmp = *a;
    *a = *b;
    *b = tmp;
}



void fishUpdate(int* matrixA,int* matrixB,int i,int j,int energy)
{
    if(shark(matrixB[V(i,j)]))
        return;



    
    int* validPositions = new int[4];
    int results = 0;

    if(matrixA[V(mod(i - 1,ROWS),j)] == 0 && matrixB[V(mod(i - 1,ROWS),j)] == 0)
        validPositions[results++] = V(mod(i - 1,ROWS),j);
    if(matrixA[V(mod(i + 1,ROWS),j)] == 0 && matrixB[V(mod(i + 1,ROWS),j)] == 0)
        validPositions[results++] = V(mod(i + 1,ROWS),j);
    if(matrixA[V(i,mod(j - 1,COLS))] == 0 && matrixB[V(i,mod(j - 1,COLS))] == 0)
        validPositions[results++] = V(i,mod(j - 1,COLS));
    if(matrixA[V(i,mod(j + 1,COLS))] == 0 && matrixB[V(i,mod(j + 1,COLS))] == 0)
        validPositions[results++] = V(i,mod(j + 1,COLS));

    matrixA[V(i,j)] = 0;

    //results = 0;

    //se non c'è nessun spazio disponibile non muoverti ma aumenta comunque l'energia
    if(results == 0)
    {
        matrixB[V(i,j)] = energy + 1;
        delete [] validPositions;
        return;
    }
    int pos = validPositions[rand() % results];

    //se l'energia del pesce è sufficente allora nella vecchia casella nasce un nuovo pesce
    if(energy > FISH_TRESHHOLD)
    {
        matrixB[V(i,j)] = 1;
        energy = 0;
    }

    matrixB[pos] = energy + 1; //incremento sempre di uno il suo valore (che si un pesce o uno squalo)
    delete [] validPositions;
    
}

void sharkUpdate(int* matrixA,int* matrixB,int i,int j,int value)
{
    matrixA[V(i,j)] = 0;
        
    //muore se non ha energie
    if(value - 10000 <= 0)
        return;


    int* validPositions = new int[4];
    int results = 0;

    if(fish(matrixA[V(mod(i - 1,ROWS),j)]) || fish(matrixB[V(mod(i - 1,ROWS),j)]))
        validPositions[results++] = V(mod(i - 1,ROWS),j);
    if(fish(matrixA[V(mod(i + 1,ROWS),j)]) || fish(matrixB[V(mod(i + 1,ROWS),j)]))
        validPositions[results++] = V(mod(i + 1,ROWS),j);
    if(fish(matrixA[V(i,mod(j - 1,COLS))]) || fish(matrixB[V(i,mod(j - 1,COLS))]))
        validPositions[results++] = V(i,mod(j - 1,COLS));
    if(fish(matrixA[V(i,mod(j + 1,COLS))]) || fish(matrixB[V(i,mod(j + 1,COLS))]))
        validPositions[results++] = V(i,mod(j + 1,COLS));

    if(results == 0)
    {
        //matrixB[V(i,j)] = value - 1;




        if(matrixA[V(mod(i - 1,ROWS),j)] == 0 && matrixB[V(mod(i - 1,ROWS),j)] == 0)
            validPositions[results++] = V(mod(i - 1,ROWS),j);
        if(matrixA[V(mod(i + 1,ROWS),j)] == 0 && matrixB[V(mod(i + 1,ROWS),j)] == 0)
            validPositions[results++] = V(mod(i + 1,ROWS),j);
        if(matrixA[V(i,mod(j - 1,COLS))] == 0 && matrixB[V(i,mod(j - 1,COLS))] == 0)
            validPositions[results++] = V(i,mod(j - 1,COLS));
        if(matrixA[V(i,mod(j + 1,COLS))] == 0 && matrixB[V(i,mod(j + 1,COLS))] == 0)
            validPositions[results++] = V(i,mod(j + 1,COLS));

        if(results == 0)
        {
            matrixB[V(i,j)] = value - 1;
            delete [] validPositions;
            return;
        }

        int pos = validPositions[rand() % results];
        matrixB[pos] = value - 1;
        delete [] validPositions;
        return;
    }

    int* pos = new int(validPositions[rand() % results]);

    int energyShark = value + EAT_ENERGY - 10000;
    if(energyShark > SHARK_TRESHHOLD)
    {
        results = 0;
        if(matrixA[V(mod(i - 1,ROWS),j)] == 0 && matrixB[V(mod(i - 1,ROWS),j)] == 0)
            validPositions[results++] = V(mod(i - 1,ROWS),j);
        if(matrixA[V(mod(i + 1,ROWS),j)] == 0 && matrixB[V(mod(i + 1,ROWS),j)] == 0)
            validPositions[results++] = V(mod(i + 1,ROWS),j);
        if(matrixA[V(i,mod(j - 1,COLS))] == 0 && matrixB[V(i,mod(j - 1,COLS))] == 0)
            validPositions[results++] = V(i,mod(j - 1,COLS));
        if(matrixA[V(i,mod(j + 1,COLS))] == 0 && matrixB[V(i,mod(j + 1,COLS))] == 0)
            validPositions[results++] = V(i,mod(j + 1,COLS));

        if(results > 0)
        {
            int posSon = validPositions[rand() % results];
            matrixB[posSon] = 10000 + energyShark / 2;
            energyShark = energyShark / 2;
        }
    }

    matrixB[*pos] = 10000 + energyShark;

    delete pos;
    delete [] validPositions;

}



void updateWorld(int* matrixA,int* matrixB)
{

    for(int i = 0;i < ROWS;i++)
    {
        for(int j = 0;j < COLS;j++)
        {
            int value = matrixA[V(i,j)];
            if(fish(value))
                fishUpdate(matrixA,matrixB,i,j,value);
            else if(shark(value))
                sharkUpdate(matrixA,matrixB,i,j,value);
        }
    }
}


#endif