#ifndef SEQUENTIAL_WATOR
#define SEQUENTIAL_WATOR
#include <stdlib.h>
#include <time.h>
#include "creature.cpp"
#include <stdio.h>
#include "settings.cpp"
#define V(R,C) ((R) * COLS + (C))

//ottieni una posizione valida causale dato il tipo di creatura ricercata
inline void getValidPosition(creature* matrix,int i,int j,int type,int* result)
{
    int valid_pos[4];

    int curVal = 0;
    int size = 0;

    if(matrix[curVal = V((i + ROWS + 1) % ROWS,j)].type == type)
        valid_pos[size++] = curVal;
    if(matrix[curVal = V((i + ROWS - 1) % ROWS,j)].type == type)
        valid_pos[size++] = curVal;
    if(matrix[curVal = V(i,(j + COLS + 1) % COLS)].type == type)
        valid_pos[size++] = curVal;
    if(matrix[curVal = V(i,(j + COLS - 1) % COLS)].type == type)
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

    //pos = V((i + ROWS + 1) % ROWS,j);
    //pos = V(i,(j + COLS + 1) % COLS);
    
    int energy = matrix[V(i,j)].energy;

    if(energy <= FISH_TRESHHOLD)
        matrix[V(i,j)].type = WATER;
    else if(pos != V(i,j))
        energy = -1;


    matrix[V(i,j)].energy = 0;
    matrix[pos].energy = energy + 1;
    matrix[pos].type = FISH;


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
        matrix[currentPos].type = WATER;
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
        matrix[currentPos].type = WATER;
        matrix[currentPos].energy = 0;
        matrix[pos].energy = energy - 1;
        matrix[pos].type = SHARK;
        matrix[pos].moved = posRow >= fromRow && posRow < toRow ? pos > V(i,j) : isBorder;
        return;
    }
    int posRow = pos / COLS;

    //breed if shark has enough energy
    if(energy > SHARK_TRESHHOLD)
    {
        energy /= 2;
        matrix[currentPos].type = SHARK;
        matrix[currentPos].energy = energy;
    }
    else
    {
        matrix[currentPos].type = WATER;
        matrix[currentPos].energy = 0;
    }

    //move to fish cell and increase energy
    matrix[pos].energy = energy + EAT_ENERGY;
    matrix[pos].type = SHARK;
    matrix[pos].moved = posRow >= fromRow && posRow < toRow ? pos > V(i,j) : isBorder;
}

inline void initMatrix(creature* matrix,int offset,int rows,int cols)
{
    offset = 0;
    for(int i = offset;i < rows + offset;i++)
    {
        for(int j = 0;j < cols;j++)
        {
            matrix[V(i,j)].type = rand() % 3;
            if(matrix[V(i,j)].type == SHARK)
                matrix[V(i,j)].energy = START_ENERGY;
        }
    }
}

inline void updateWorld(creature* matrix,int fromRow,int rows,bool isBorder)
{
    srand(time(NULL));

    
    int toRow = fromRow + rows;
    for(int i = fromRow;i < toRow;i++)
    {
        for(int j = 0;j < COLS;j++)
        {
            if(!matrix[V(i,j)].moved)
            {
                creature c = matrix[V(i,j)];
                if(c.type == FISH)
                    fishUpdate(matrix,i,j,fromRow,toRow,isBorder);
                else if(c.type == SHARK)
                    sharkUpdate(matrix,i,j,fromRow,toRow,isBorder);
            }
            else
                matrix[V(i,j)].moved = false;
        }
    }
}

#endif