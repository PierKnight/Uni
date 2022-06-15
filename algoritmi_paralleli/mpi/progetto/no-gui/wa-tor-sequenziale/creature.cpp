#ifndef CREATURE
#define CREATURE
#define WATER 0
#define FISH 1
#define SHARK 2

class creature
{
    public:

    bool moved;
    int energy;
    int type;

    creature():type(WATER),moved(false),energy(0){} 
    creature(int _type,int _energy):type(_type),moved(false),energy(_energy){}
};

#endif