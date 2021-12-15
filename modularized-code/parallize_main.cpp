#include <iostream>
#include "coffee_entropy.h"
#include <fstream>
#include <vector>

int main(int argc, char ** argv)
{
  int Nmol = 0;
  int size = 0;
    int Nstep = 0;
    int seed = 0;
    int init_size = 2;

    //Lectura desde el archivo input.txt
    std::ifstream input;
    input.open("input.txt");
    input >> Nmol >> size >> Nstep >> seed;
    input.close();

    //se cambia el size para ser leido
    size = std::atoi(argv[1]);

    //Las componentes del vector contienen las posiciones
    //de cada particula
    std::vector<int> particles{0}; //inicializa el vector
    particles.resize(Nmol);

    cuatro_cuadros_centrados(Nmol, size, particles, seed);   
    
    
    step (Nmol,size,particles,seed,Nstep);
    return 0;
}
