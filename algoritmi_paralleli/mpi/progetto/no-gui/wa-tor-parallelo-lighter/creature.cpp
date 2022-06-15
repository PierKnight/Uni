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

    creature():moved(false),energy(0){} 
    creature(int _type,int _energy):moved(false),energy(_energy){}

    inline int type()
    {
        return energy / 100;
    }

    inline void setType(int type)
    {
        energy = type * 100 + (energy % 100);
    }
    
};

#endif