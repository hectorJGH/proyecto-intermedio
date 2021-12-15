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
    input >> Nmol >> size >> Nstep >> seed;//40 20 1000000 0
    input.close();
    size -= 16;
    //Las componentes del vector contienen las posiciones
    //de cada particula
    std::vector<int> particles{0}; //inicializa el vector
    particles.resize(Nmol);
    initial_distribution_array(Nmol, size, init_size, particles, seed);
  std::string base = "entropy";
  int  index_int = 1;
  std::cout << "set xlabel 'Time'; " << "set ylabel 'Entropy'; " << "unset key; " << "set term png; " << "\n";
  for(int ii = 1; ii<12; ++ii)
  {
    std::cout << "set out '" << base + std::to_string(index_int) << ".png'\n";
    std::cout << "plot '-' w l\n";
    step (Nmol,size,particles,seed,Nstep);
    std::cout << "e\n";
    size += 1;
    index_int += 1;
    particles = {0};
    particles.resize(size);
    initial_distribution_array(Nmol, size, init_size, particles, seed);
  }
  return 0;
}
