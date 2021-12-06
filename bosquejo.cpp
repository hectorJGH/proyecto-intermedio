//Queremos que dada una copa m*m la distribución inicial sea un cuadrado (m/10)*(m/10) centrado en la copa
//
#include <algorithm>
#include <random>
#include <iostream>
#include <vector>
#include <fstream>

void initial_distribution_array (int Nmol, int size, int ratio, std::vector<int> & vector, int seed);// int * vector?
void step (int Nmol, int size, std::vector<int> & vector, int seed, int Nstep);
double entropia(int Nmol, std::vector<int> & vector);

int main(int argc, char *argv[])
{
    int Nmol = 0;
    int size = 0;
    int Nstep = 0;
    int seed = 0;
    int ratio = 10;
    std::ifstream input;
    input.open("input.txt");
    input >> Nmol >> size >> Nstep >> seed;
    input.close();

    std::vector<int> particles{0}; //inicializa el vector
    particles.resize(Nmol);

    initial_distribution_array(Nmol, size, ratio, particles, seed);

    step (Nmol,size,particles,seed,Nstep);

    return 0;
}

void initial_distribution_array (int Nmol, int size, int ratio, std::vector<int> & vector, int seed)
{
    int init_size = size/ratio;

    std::mt19937 gen(seed); //OJO: de pronto se generan los numeros aleatorios 2 veces
    std::uniform_int_distribution<> dis{0, init_size};

    for (int n=0; n<Nmol; n++){
	int i=0,j=0;
	i = size/2 -init_size/2 + dis(gen);
	j = size/2 -init_size/2 + dis(gen);
        vector[n] = i*size + j;
    }
}

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
    //    double A_Nmol = Nmol;
    //double sum = 0;
    //int aux = 0;
    //int counter = 0;
    //int counter2 = 0;
    //aux = vector[counter2];
    //while(counter2 < Nmol)
    //{
    //    while(counter2 < Nmol && aux == vector[counter2])
    //    {
    //        counter += 1;
    //        counter2 += 1;
    //    }
    //    sum += (counter/A_Nmol)*std::log(counter/A_Nmol);
    //    counter = 0;
    //    if(counter2 < Nmol)
    //    {
    //        aux = vector[counter2];
    //    }
    //}
    //return -sum;
}


void step (int Nmol, int size, std::vector<int> & vector, int seed, int Nstep)
{
    std::mt19937 gen(seed); //OJO: de pronto se generan los numeros aleatorios 3 veces
    std::uniform_int_distribution<> dis_1{0, Nmol -1};
    int mol = 0;
    std::uniform_int_distribution<> dis_2{0, 4};
    int paso = 0;
    int aqui = 0;
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
            if (aqui % size != size-1)  vector[mol] += 1;//le voy a dar en la cara marica
            else vector[mol] = aqui/size; //se teletransporta hacia la pared izquierda
        }
        std::cout << ii << "\t" << entropia(Nmol, vector) << "\n";
    }
}
