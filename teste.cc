#include "random.h"
#include <iostream>
#include <cstdlib>

using namespace std;

int main(){
	int seed = 0;
	float mean = 2.0;
	Random random(seed);

	cout << "Poisson: " << random.rand_poisson(mean) << endl;
	cout << "Poisson: " << random.rand_poisson(mean) << endl;
	cout << "Poisson: " << random.rand_poisson(mean) << endl;
	cout << "Poisson: " << random.rand_poisson(mean) << endl;
	cout << "Poisson: " << random.rand_poisson(mean) << endl;
	cout << "Poisson: " << random.rand_poisson(mean) << endl;
}
