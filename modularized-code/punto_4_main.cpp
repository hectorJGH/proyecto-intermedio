#include <iostream>
#include "coffee_entropy.h"
#include <fstream>
#include <vector>

int main(int argc, char *argv[])
{
    int Nmol = 0;
    int size = 0;
    int Nstep = 0;
    int seed = 0;
    int init_size = 2;
    int ratio = 0;

    //Lectura desde el archivo input.txt
    std::ifstream input;
    input.open("input4.txt");
    input >> Nmol >> size >> Nstep >> seed >> ratio;
    input.close();

    //Las componentes del vector contienen las posiciones
    //de cada particula
    std::vector<int> particles{0}; //inicializa el vector
    particles.resize(Nmol);

    //Ubica las particulas aleatoriamente en su distribucion inicial
    //cerca al centro de la taza
    cuatro_cuadros_centrados(Nmol, size, particles, seed);

    //Se realizan todos los pasos de la difusion y en cada uno se
    //imprime el paso, la entropia total y el radio de difusion
    with_hole(size, particles, seed, Nstep, ratio);

    return 0;
}

