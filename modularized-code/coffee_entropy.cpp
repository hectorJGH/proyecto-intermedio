#include <iostream>
#include "coffee_entropy.h"

//Ubica las particulas aleatoriamente en su distribucion inicial
//cerca al centro de la taza en un cuadrado de lado init_size
void initial_distribution_array (int Nmol, int size, int init_size, std::vector<int> & vector, int seed)
{
    //int init_size = size/ratio;

    std::mt19937 gen(seed); //OJO: de pronto se generan los numeros aleatorios 2 veces
    std::uniform_int_distribution<> dis{0, init_size-1};

    for (int n=0; n<Nmol; n++){
        int i=0,j=0;
        i = size/2 -init_size/2 + dis(gen);
        j = size/2 -init_size/2 + dis(gen);
        vector[n] = i*size + j;
    }
}

//Se realizan todos los pasos de la difusion y en cada uno se
//imprime el paso, la entropia total y el radio de difusion
void step (int Nmol, int size, std::vector<int> & vector, int seed, int Nstep)
{
    std::mt19937 gen(seed); //OJO: de pronto se generan los numeros aleatorios 3 veces
    std::uniform_int_distribution<> dis_1{0, Nmol -1};
    int mol = 0;
    std::uniform_int_distribution<> dis_2{0, 4};
    int paso = 0;
    std::cout.precision(6);
    std::cout << 0 << "\t" << entropia(Nmol, vector) << "\n";
    for(int ii = 1; ii <= Nstep; ++ii)
    {
        mol = dis_1(gen);
        paso = dis_2(gen);
        if (paso==1) {
            if (vector[mol]/size != 0) vector[mol] += -size;//arriba
            else vector[mol] += (size-1)*size; //se teletransporta hacia la pared de abajo
        }
        else if (paso==2) {
            if (vector[mol]/size != size-1) vector[mol] += size;//abajo
            else vector[mol] = vector[mol] % size;//se teletransporta hacia la pared de arriba
        }
        else if (paso==3) {
            if (vector[mol] % size != 0) vector[mol] += -1;//izquierda camarada
            else vector[mol] += size -1;//se teletransporta hacia la pared derecha
        }
        else if (paso==4) {
            if (vector[mol] % size != size-1)  vector[mol] += 1;//le voy a dar en la cara marica
            else vector[mol] = vector[mol]/size; //se teletransporta hacia la pared izquierda
        }
        std::cout << ii << "\t" << entropia(Nmol, vector) <<"\t" <<radius( Nmol, vector,size) << "\n";
    }
}

//Calcula la entropia de cierta configuracion de las particulas
double entropia(int Nmol, std::vector<int> & vector)
{
    std::sort(vector.begin(), vector.end());//ordena los valores del vector para que los que son iguales queden contiguos
    double sum=0;
    double aux=1;
    for(int ii=0; ii<Nmol-1;++ ii){
      if(vector[ii] != vector[ii+1]){
        aux= aux/Nmol;
        sum -= aux*(std::log(aux));
        aux=1;
      }
      else{
        aux+=1;
      }
    }
    aux= aux/Nmol;
    sum-= aux*(std::log(aux));
    return sum;
}

//Calcula el radio de difusion de la crema de cafe
double radius(int Nmol, std::vector<int> & vector, int size)
{
  double r=0;
  for(int ii=0; ii<Nmol;++ii){
    r+= std::pow((vector[ii]/size)-(size/2),2)+std::pow((vector[ii]%size)-(size/2),2);
  }
  r=r/Nmol;
  return std::sqrt(r);
}
