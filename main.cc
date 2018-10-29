#include "random.h"
#include <iostream>
#include <queue>
#include <cmath>
#define _USE_MATH_DEFINES
#include "matplotlib-cpp-master/matplotlibcpp.h"

#define N 10000 // numero de tarefas que chegam no simulador de filas
#define mean_arrival 1
#define mean_processing 0.5

namespace plt = matplotlibcpp;
using namespace std;

int seed_A[4] = {23, 25, 167, 235};
int seed_B[4] = {17, 89, 11, 21};

enum states{
	IDLE,
	BUSY
};

struct task{
  double arrival_time = 0.0;
}t;

double sim_time;

int huge_val = 10000;
double next_arrival;
double next_departure; 

queue<task> fila;
std::vector<int> fila_c(N);
std::vector<int> fila_sim_time(N);
int queue_counter;
states server_state;

double waiting_time_total;
double last_event_time;
double cumulated_queue_length;
double busy_time_total;

double count_arrival;

void update_statistics(){
	double time_since_last_event = sim_time - last_event_time;
	cumulated_queue_length += fila.size() * time_since_last_event;

	if (server_state == BUSY) busy_time_total += time_since_last_event;
}

void mm1_simulator(Random r, Random r2){
	queue_counter = 0;
	fila = {};
	server_state = IDLE;
	next_arrival = (double)r.rand_poisson(mean_arrival);
	next_departure = huge_val;

	sim_time = 0.0;
	waiting_time_total = 0.0;
	last_event_time = 0.0;
	cumulated_queue_length = 0.0;
	busy_time_total = 0.0;
	count_arrival = 0.0;
	
	for (int nTask = 0; nTask < N; nTask++) {
	// while(sim_time < N){
		if(next_arrival < next_departure) sim_time = next_arrival;
		else sim_time = next_departure;
		fila_sim_time[nTask] = sim_time;
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
			queue_counter++;
			fila_c[nTask] = queue_counter;
	    	next_arrival = sim_time + r.rand_exp(mean_arrival);
	    }else{
			if(fila.empty()) {
	            server_state = IDLE;
	            next_departure = huge_val;
	        }else{
	        	t = fila.front();
	            fila.pop();
	            queue_counter--;
	            fila_c[nTask] = queue_counter;
	            next_departure = sim_time + r2.rand_exp(mean_processing);
	            waiting_time_total += sim_time - t.arrival_time;
	        }
	    }
	    last_event_time = sim_time;
	}
}

int main(){
	double avg_utilization  = 0.0;
	double avg_queue_length = 0.0;
	double avg_waiting_time = 0.0;

	cout << "Seed A \t| Seed B \t| AVG_UTILIZATION \t| AVG_QUEUE_LENGTH \t| AVG_WAITING_TIME" << endl;
	for (int i = 0; i < 4; i++){
		Random r(seed_A[i]);
		Random r2(seed_B[i]);
		cout << "------------------------------------------------------------------------------------------" << endl;
		mm1_simulator(r, r2);
		avg_utilization  = busy_time_total / sim_time;
		avg_queue_length = cumulated_queue_length / sim_time;
		avg_waiting_time = waiting_time_total / count_arrival;
		cout << seed_A[i] << " \t| " << seed_B[i] << " \t\t| " << avg_utilization << " \t\t| "<< avg_queue_length << " \t\t| " << avg_waiting_time << endl;
	}
	plt::figure_size(1200, 780);
	plt::plot(fila_sim_time, fila_c);
	plt::title("Estado da Fila para 1000 tarefas");
	plt::xlabel("Tempo de simulacao");
	plt::ylabel("Numero de tarefas na fila");
	// plt::hist(fila_sim_time, 10);
	const char* filename = "estado_fila";
	remove("estado_fila.png");
    cout << "Salvando plot da fila no arquivo: " << filename << ".png" << endl;;
    plt::save(filename);
}