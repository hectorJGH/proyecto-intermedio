#include "coffee_entropy.h"
#include <iostream>
#include <fstream>

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
    input >> Nmol >> size >> Nstep >> seed;//40 20 1000000 0
    input.close();

    //Las componentes del vector contienen las posiciones
    //de cada particula
    std::vector<int> particles{0}; //inicializa el vector
    particles.resize(Nmol);

    //Ubica las particulas aleatoriamente en su distribucion inicial
    //cerca al centro de la taza
    initial_distribution_array(Nmol, size, init_size, particles, seed);

    std::cout << "Para una copa de arista par, el radio de la distribución inicial debe ser raíz de 2 sobre 2, a continuación se imprimen aristas pares con el error de su radio respecto al valor esperado\n";

    for(int ii = 0; ii < 20; ++ii)
    {
        size += ii*2;
        std::cout << size << "\t" << std::fabs(std::sqrt(2)*radius(Nmol, particles, size) - 1) << "\n";
        particles = {0};
        particles.resize(Nmol);
        initial_distribution_array(Nmol, size, init_size, particles, seed);
    }

    return 0;
}
