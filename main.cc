#include "random.h"
#include <iostream>
#include <queue>

#define N 1000 // numero de tarefas que chegam no simulador de filas
#define SEED_A 23
#define SEED_B 17
#define mean_arrival 1
#define mean_processing 0.5

using namespace std;

enum states{
	IDLE,
	BUSY
};

struct task{
  double arrival_time = 0.0;
}t;

double sim_time;

Random r(SEED_A);
Random r2(SEED_B);

int huge_val = 10000;
double next_arrival;
double next_departure; 

queue<task> fila;

states server_state;

double waiting_time_total;
double last_event_time;
double cumulated_queue_length;
double busy_time_total;

double count_arrival = 0.0;

void update_statistics(){
	double time_since_last_event = sim_time - last_event_time;
	cumulated_queue_length += fila.size() * time_since_last_event;

	if (server_state == BUSY) busy_time_total += time_since_last_event;
}

int main(){
	server_state = IDLE;
	sim_time = 0.0;
	next_arrival = (double)r.rand_poisson(mean_arrival);
	next_departure = huge_val;

	waiting_time_total = 0.0;
	last_event_time = 0.0;
	cumulated_queue_length = 0.0;
	busy_time_total = 0.0;

	// for (int nTask = 0; nTask < N; nTask++) {
	while(sim_time < N){
		if(next_arrival < next_departure) sim_time = next_arrival;
		else sim_time = next_departure;
		update_statistics();
		if(next_arrival < next_departure) {
			if(server_state == IDLE) {
	            server_state = BUSY;
	            next_departure = sim_time + r2.rand_exp(mean_processing);
	        }else {
				t.arrival_time = sim_time;
				fila.push(t);
			}
			count_arrival++;
	    	next_arrival = sim_time + r.rand_exp(mean_arrival);
	    }else{
			if(fila.empty()) {
	            server_state = IDLE;
	            next_departure = huge_val;
	        }else{
	        	t = fila.front();
	            fila.pop();
	            next_departure = sim_time + r2.rand_exp(mean_processing);
	            waiting_time_total += sim_time - t.arrival_time;
	        }
	    }
	    last_event_time = sim_time;
	}

	cout << "sim_time: " << sim_time << endl;
	double avg_utilization  = busy_time_total / sim_time;
	double avg_queue_length = cumulated_queue_length / sim_time;
	double avg_waiting_time = waiting_time_total / count_arrival;

	cout << "AVG_UTILIZATION: " << avg_utilization << endl;
	cout << "AVG_QUEUE_LENGTH: " << avg_queue_length << endl;
	cout << "AVG_WAITING_TIME: " << avg_waiting_time << endl;
}