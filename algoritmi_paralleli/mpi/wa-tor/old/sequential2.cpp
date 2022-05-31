#ifndef SEQUENTIAL_WATOR
#define SEQUENTIAL_WATOR
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

void fishUpdate(int* matrix,bool* matrixB,int i,int j,int value)
{
    int pos = V((i + ROWS + 1) % ROWS,j);
    if(matrix[pos] != 0)
        return;

    
    matrix[V(i,j)] = 0;
    matrix[pos] = 1;
    matrixB[pos] = pos > V(i,j);
    
}

void updateWorld(int* matrixA,bool* matrixB)
{
    for(int i = 0;i < ROWS;i++)
    {
        for(int j = 0;j < COLS;j++)
        {
            if(!matrixB[V(i,j)])
            {
                int value = matrixA[V(i,j)];
                if(fish(value))
                    fishUpdate(matrixA,matrixB,i,j,value);
            }
            else
                matrixB[V(i,j)] = false;
        }
    }
}

#endif