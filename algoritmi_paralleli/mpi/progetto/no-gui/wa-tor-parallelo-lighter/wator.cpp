#ifndef SEQUENTIAL_WATOR
#define SEQUENTIAL_WATOR
#include "creature.cpp"
#include <stdio.h>
#define ROWS 3000
#define COLS 1000
#define V(R,C) ((R) * COLS + (C))
//fish stats
#define FISH_TRESHHOLD 1
//shark stats
#define START_ENERGY 50
#define SHARK_TRESHHOLD 10
#define EAT_ENERGY 1

inline void getValidPosition(creature* matrix,int i,int j,int type,int* result)
{
    int valid_pos[4];

    int curVal = 0;
    int size = 0;

    if(matrix[curVal = V((i + ROWS + 1) % ROWS,j)].type() == type)
        valid_pos[size++] = curVal;
    if(matrix[curVal = V((i + ROWS - 1) % ROWS,j)].type() == type)
        valid_pos[size++] = curVal;
    if(matrix[curVal = V(i,(j + COLS + 1) % COLS)].type() == type)
        valid_pos[size++] = curVal;
    if(matrix[curVal = V(i,(j + COLS - 1) % COLS)].type() == type)
        valid_pos[size++] = curVal;
    if(size == 0)
    {
        (*result) = V(i,j);
        return;
    }
    (*result) = valid_pos[rand() % size];
}

inline void fishUpdate(creature* matrix,int i,int j,int fromRow,int toRow,bool isBorder)
{
    int pos;
    getValidPosition(matrix,i,j,WATER,&pos);

    //pos = V((i + ROWS - 1) % ROWS,j);
    //pos = V(i,(j + COLS + 1) % COLS);


    int energy = matrix[V(i,j)].energy;

    if(energy <= FISH_TRESHHOLD)
        matrix[V(i,j)].setType(WATER);
    else if(pos != V(i,j))
        energy = -1;


    matrix[V(i,j)].energy = 0;
    matrix[pos].energy = energy + 1;
    matrix[pos].setType(FISH);


    int posRow = pos / COLS;
    matrix[pos].moved = posRow >= fromRow && posRow < toRow ? pos > V(i,j) : isBorder;
}

inline void sharkUpdate(creature* matrix,int i,int j,int fromRow,int toRow,bool isBorder)
{
    int currentPos = V(i,j);
    int energy = matrix[currentPos].energy;
    //if not enough energy the shark dies
    if(energy < 0)
    {
        matrix[currentPos].setType(WATER);
        matrix[currentPos].energy = 0;
        return;
    }

    int pos;
    getValidPosition(matrix,i,j,FISH,&pos);

    //if fish is not found move to a random available water cell
    if(pos == currentPos)
    {
        getValidPosition(matrix,i,j,WATER,&pos);
        int posRow = pos / COLS;
        matrix[currentPos].setType(WATER);
        matrix[currentPos].energy = 0;
        matrix[pos].energy = energy - 1;
        matrix[pos].setType(SHARK);
        matrix[pos].moved = posRow >= fromRow && posRow < toRow ? pos > V(i,j) : isBorder;
        return;
    }
    int posRow = pos / COLS;

    //breed if shark has enough energy
    if(energy > SHARK_TRESHHOLD)
    {
        energy /= 2;
        matrix[currentPos].setType(SHARK);
        matrix[currentPos].energy = energy;
    }
    else
    {
        matrix[currentPos].setType(WATER);
        matrix[currentPos].energy = 0;
    }

    //move to fish cell and increase energy
    matrix[pos].energy = energy + EAT_ENERGY;
    matrix[pos].setType(SHARK);
    matrix[pos].moved = posRow >= fromRow && posRow < toRow ? pos > V(i,j) : isBorder;
}

inline void updateWorld(creature* matrix,int fromRow,int rows,bool isBorder)
{
    srand (time(NULL));

    
    int toRow = fromRow + rows;
    for(int i = fromRow;i < toRow;i++)
    {
        for(int j = 0;j < COLS;j++)
        {
            if(!matrix[V(i,j)].moved)
            {
                creature c = matrix[V(i,j)];
                if(c.type() == FISH)
                    fishUpdate(matrix,i,j,fromRow,toRow,isBorder);
                else if(c.type() == SHARK)
                    sharkUpdate(matrix,i,j,fromRow,toRow,isBorder);
            }
            else
                matrix[V(i,j)].moved = false;
        }
    }
}

#endif