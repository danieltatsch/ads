#ifndef Random_H
#define Random_H

#include <random>

class Random{
private:
	std::default_random_engine engine;
	int seed;
public:
	Random(int seed);
	double rand_u();
	double rand_exp();
	double rand_exp(float lambda);
	double congruente();
};

#endif