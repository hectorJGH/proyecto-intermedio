#ifndef COFFEE_ENTROPY_H
#define COFFEE_ENTROPY_H
#include <algorithm>
#include <random>
#include <iostream>
#include <vector>
#include <fstream>
#include <cmath>

//Ubica las particulas aleatoriamente en su distribucion inicial
//cerca al centro de la taza en un espacio size/ratio
void initial_distribution_array (int Nmol, int size, int init_size, std::vector<int> & vector, int seed);

//Se realizan todos los pasos de la difusion y en cada uno se
//imprime el paso, la entropia total y el radio de difusion
void step (int Nmol, int size, std::vector<int> & vector, int seed, int Nstep);

//Calcula la entropia de cierta configuracion de las particulas
double entropia(int Nmol, std::vector<int> & vector);

//Calcula el radio de difusion de la crema de cafe
double radius(int Nmol, std::vector<int> & vector, int size);

//Se realizan todos los pasos de la difusion con un agujero en la taza
// y en cada uno se imprime el paso, y el numero de moleculas dentro
void with_hole(int size, std:: vector<int> & vector, int seed, int Nstep, int ratio);

#endif
