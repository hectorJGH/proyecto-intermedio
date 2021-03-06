//Queremos que dada una copa m*m la distribución inicial sea un cuadrado (m/10)*(m/10) centrado en la copa
//
#include <algorithm>
#include <random>
#include <iostream>
#include <vector>
#include <fstream>
#include <cmath>

void cuatro_cuadros_centrados (int Nmol, int size, int ratio, std::vector<int> & vector, int seed);//funciona copas con lado par
void with_hole(int size, std:: vector<int> & vector, int seed, int Nstep);
void initial_distribution_array (int Nmol, int size, int ratio, std::vector<int> & vector, int seed);// int * vector?
void step (int Nmol, int size, std::vector<int> & vector, int seed, int Nstep);
double entropia(int Nmol, std::vector<int> & vector);
double radius(int Nmol, std::vector<int> & vector, int size);

int main(int argc, char *argv[])
{
    int Nmol = 0;
    int size = 0;
    int Nstep = 0;
    int seed = 0;
    int ratio = 10;
    
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
    cuatro_cuadros_centrados(Nmol, size, ratio, particles, seed);
    //initial_distribution_array(Nmol, size, ratio, particles, seed);

    //Se realizan todos los pasos de la difusion y en cada uno se
    //imprime el paso, la entropia total y el radio de difusion
    step (Nmol,size,particles,seed,Nstep);
    //with_hole(size,particles,seed,Nstep);

    
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

void cuatro_cuadros_centrados (int Nmol, int size, int ratio, std::vector<int> & vector, int seed)
{
  std::mt19937 gen(seed); //OJO: de pronto se generan los numeros aleatorios 2 veces
  std::uniform_int_distribution<> dis{0,1};
  int esquina=(size-1)/2;
  for (int n=0; n<Nmol; n++){
	int i=0,j=0;
	i = esquina + dis(gen);
	j = esquina + dis(gen);
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
}

double radius(int Nmol, std::vector<int> & vector, int size)
{
  double r=0;
  for(int ii=0; ii<Nmol;++ii){
    int x=(vector[ii]/size)-((size-1)/2);
    int y=(vector[ii]%size)-((size-1)/2);
    r+= std::pow(x-0.5,2)+std::pow(y-0.5,2);
  }
  r=r/Nmol;
  return std::sqrt(r);
}


void step (int Nmol, int size, std::vector<int> & vector, int seed, int Nstep)
{
    std::mt19937 gen(seed); //OJO: de pronto se generan los numeros aleatorios 3 veces
    std::uniform_int_distribution<> dis_1{0, Nmol -1};
    int mol = 0;
    std::uniform_int_distribution<> dis_2{0, 4};
    int paso = 0;
    int rad=radius( Nmol, vector,size);
    std::cout << 0 << "\t" << entropia(Nmol, vector)<<"\t"<<radius( Nmol, vector,size) << "\n";
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
        std::cout << ii << "\t" << entropia(Nmol, vector) <<"\t"<<radius( Nmol, vector,size) << "\n";
    }
}

void with_hole(int size, std:: vector<int> & vector, int seed, int Nstep)
{
      std::mt19937 gen(seed); //OJO: de pronto se generan los numeros aleatorios 3 veces
      int numero = static_cast<int>(vector.size());
      std::uniform_int_distribution<> dis_1{0, numero -1};
    int mol = 0;
    std::uniform_int_distribution<> dis_2{0, 4};
    int paso = 0;
    for(int ii = 1; ii <= Nstep; ++ii)
    {
      if(numero==0)break;
        mol = dis_1(gen);
	while(mol>numero-1){
	  mol=dis_1(gen);
	}
        paso = dis_2(gen);
        if (paso==1) {
            if (vector[mol]/size != 0) vector[mol] += -size;//arriba
            else vector[mol] += size; // rebota hacia abajo
        }
        else if (paso==2) {
            if (vector[mol]/size != size-1) vector[mol] += size;//abajo
            else {
	      if((size-1-size/5)<=vector[mol]%size<=size-1){
		vector.erase(vector.begin()+mol); //sale por abajo
		numero=static_cast<int>(vector.size());
	      }
	      else vector[mol] = -size;//rebota hacia arriba
	    }
        }
        else if (paso==3) {
            if (vector[mol] % size != 0) vector[mol] += -1;//izquierda camarada
            else vector[mol] += 1;//rebota hacia la derecha
        }
        else if (paso==4) {
            if (vector[mol] % size != size-1)  vector[mol] += 1;//le voy a dar en la cara marica
            else {
	      if((size-1-size/5)<=vector[mol]/size<=size-1){
		vector.erase(vector.begin()+mol);//sale por la derecha
		numero=static_cast<int>(vector.size());
	      }
	       else vector[mol] += -1; //rebota a la izquierda
	    }
	}
        std::cout << ii <<"\t"<<numero<< "\n";
    }




}
