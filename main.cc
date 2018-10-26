#include "random.h"
#include <iostream>
#include <queue>

#define N 1000 // numero de tarefas que chegam no simulador de filas
#define SEED_A 23
#define SEED_B 17

using namespace std;

enum states{
	IDLE,
	BUSY
};

struct task{
  double arrival_time = 0.0;
}tasks[N];

double sim_time = 0.0;
float mean_arrival = 1.0;
float mean_processing = 0.5;

Random r(SEED_A);
Random r2(SEED_B);

int huge_val = 100;
int next_arrival = r.rand_poisson(mean_arrival);
double next_departure = huge_val; 

queue<task> fila;

states server_state = IDLE;

double avg_waiting_time = 0.0;

int main(){
	for (int nTask = 0; nTask < N; nTask++) {
		if(next_arrival < next_departure) {
	    	sim_time = (double)next_arrival;
			if(server_state == IDLE) {
	            server_state = BUSY;
	            next_departure = sim_time + r2.rand_exp(mean_processing);
	        }else {
				tasks[nTask].arrival_time = sim_time;
				fila.push(tasks[nTask]);
			}
	    	next_arrival = (int)sim_time + (int)r.rand_exp(mean_arrival);
	    }else{
			sim_time = next_departure;
			if(fila.empty()) {
	            server_state = IDLE;
	            next_departure = huge_val;
	        }else{
	        	tasks[nTask] = fila.front();
	            fila.pop();
	            // printf("pop da fila:  %d\n", nTask);
	            next_departure = sim_time + r2.rand_exp(mean_processing);
	            avg_waiting_time = sim_time - tasks[nTask].arrival_time;
	        }
	    }
	}
	avg_waiting_time = avg_waiting_time/N;
	printf("AVG_WAITING_TIME: %f\n", avg_waiting_time);
}