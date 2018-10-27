#ifndef Random_H
#define Random_H

#include <random>

class Random{
private:
	std::default_random_engine engine;
	unsigned int seed;
public:
	Random(int seed);
	double rand_u();
	double rand_exp();
	double rand_exp(float mean);
	int rand_poisson(float mean);
	double congruente();
};

#endif
