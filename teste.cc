#include "random.h"
#include <iostream>
#include <cstdlib>

using namespace std;

int main(){
	int seed = 0;
	int seed2 = 21;
	Random random(seed);
	Random random2(seed2);

	cout << "congruente: " << random.congruente() << endl;
	cout << "congruente: " << random.congruente() << endl;
	cout << "congruente: " << random.congruente() << endl;
	cout << "congruente: " << random.congruente() << endl;
	cout << "congruente: " << random.congruente() << endl;
	cout << "congruente: " << random.congruente() << endl;
	cout << "congruente: " << random.congruente() << endl;
	cout << "congruente: " << random.congruente() << endl;
	cout << "----------------" << endl;
	cout << "rand_exp: " << random.rand_exp() << endl;
	cout << "rand_exp: " << random.rand_exp() << endl;
	cout << "rand_exp: " << random.rand_exp() << endl;
	cout << "rand_exp: " << random.rand_exp() << endl;
	cout << "----------------" << endl;
}