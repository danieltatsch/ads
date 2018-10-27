#include "random.h"
#include <iostream>
#define randmax 10000000

using namespace std;

int main(){
	Random r(0);
	double aux = 0;
	for (int i = 0; i < randmax; i++) aux += (double)r.rand_poisson(12.00);
	cout << "Media do rand_u: " << (aux/randmax) << endl;
}