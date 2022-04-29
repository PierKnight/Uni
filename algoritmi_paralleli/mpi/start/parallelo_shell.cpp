#include <stdio.h>
#include <unistd.h>
#include <iostream>

int main(int argc, char const *argv[])
{

    int test = std::atoi(argv[1]);

    sleep(3);
    printf("Sono %d\n",test);


    return 0;
}
