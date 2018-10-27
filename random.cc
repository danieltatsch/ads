#include <stdlib.h> 
#include <random>
#include <math.h>
#include "random.h"

#define a 1103515245
#define c 12345
#define m 2147483648

using namespace std;

Random::Random(int seed){
	this->seed = seed;
	engine = default_random_engine(this->seed);
}

double Random::rand_u(){
	//distribuição uniforme entre 0 e 1
	uniform_real_distribution<double> distribution (0.0,1.0);
	return(distribution(engine));
}

double Random::rand_exp(){
	//distribuição exponencial com número médio de ocorrências igual a 1
	exponential_distribution<double> distribution (1.0);
	return(distribution(engine));
}

double Random::rand_exp(float mean){
	return((-mean) * log(rand_u()));
}

int Random::rand_poisson(float mean){
	//distribuição exponencial com média igual a mean	
	poisson_distribution<int> distribution (mean);
	return(distribution(engine));
}


// valor de retorno servira de semente para a prox exec
double Random::congruente(){
	seed = (a * seed + c) % m;	
	engine = default_random_engine(seed);	
	return seed;
}
