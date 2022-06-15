#/usr/bin/shell
echo "COMPILAZIONE...."
mpiCC parallel.cpp $(pkg-config --libs allegro-5 allegro_main-5 allegro_primitives-5 )
echo "RUNNING..."
mpirun -np 8 a.out
