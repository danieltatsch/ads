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

double waiting_time_total = 0.0;
double last_event_time = 0.0;
double cumulated_queue_length = 0.0;
double busy_time_total = 0.0;

void update_statistics(){
	double time_since_last_event = sim_time - last_event_time;
	cumulated_queue_length += fila.size() * time_since_last_event;

	if (server_state == BUSY) busy_time_total += time_since_last_event;
}

int main(){
	for (int nTask = 0; nTask < N; nTask++) {
		if(next_arrival < next_departure) sim_time = (double)next_arrival;
		else sim_time = next_departure;
		update_statistics();
		if(next_arrival < next_departure) {
			if(server_state == IDLE) {
	            server_state = BUSY;
	            next_departure = sim_time + r2.rand_exp(mean_processing);
	        }else {
				tasks[nTask].arrival_time = sim_time;
				fila.push(tasks[nTask]);
			}
	    	next_arrival = (int)sim_time + r.rand_exp(mean_arrival);
	    }else{
			if(fila.empty()) {
	            server_state = IDLE;
	            next_departure = huge_val;
	        }else{
	        	tasks[nTask] = fila.front();
	            fila.pop();
	            // printf("pop da fila:  %d\n", nTask);
	            next_departure = sim_time + r2.rand_exp(mean_processing);
	            waiting_time_total = sim_time - tasks[nTask].arrival_time;
	        }
	    }
	    last_event_time = sim_time;
	}
	double avg_waiting_time = waiting_time_total / sim_time;
	double avg_queue_length = cumulated_queue_length / sim_time;
	double avg_utilization = busy_time_total / sim_time;

	cout << "AVG_UTILIZATION: " << avg_utilization << endl;
	cout << "AVG_QUEUE_LENGTH: " << avg_queue_length << endl;
	cout << "AVG_WAITING_TIME: " << avg_waiting_time << endl;
}