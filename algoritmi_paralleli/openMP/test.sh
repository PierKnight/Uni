#/usr/bin/bash


echo "---------------------------" >> output.txt;
g++ -fopenmp $1;
./a.out >> output.txt;

echo \# O3 >> output.txt;
g++ -O3 -fopenmp $1;
./a.out >> output.txt;

echo \# O2 >> output.txt;
g++ -O2 -fopenmp $1;
./a.out >> output.txt;

echo \# O1 >> output.txt;
g++ -O1 -fopenmp $1;
./a.out >> output.txt;

rm ./a.out;