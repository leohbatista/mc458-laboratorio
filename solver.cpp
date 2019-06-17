#include "solver.h"

double getDistance(Point p1, Point p2){
	double delta_x = p1.x - p2.x;
	double delta_y = p1.y - p2.y;

	return sqrt(delta_x * delta_x + delta_y * delta_y); 
}

vector<int> solveBottomUp(Instance &instance, int timelimit, chrono::high_resolution_clock::time_point &started){
	vector<int> sol;
	
	vector<double><double> store; 
	
	for(int i = 1; i < instance.n - 1; i++){
		sol.push_back(i);
		
		// get the time that has passed in seconds and check the timelimit
		auto done = chrono::high_resolution_clock::now();
		auto time = chrono::duration_cast<chrono::seconds>(done-started).count();
		
		if(time > timelimit){
			break;
		}
	}
	
	return sol;
}

vector<int> solveTopDown(Instance &instance, int timelimit, chrono::high_resolution_clock::time_point &started){
	vector<int> sol;
	int vector_solution = INFINITY;
	
	// Creates memorization table
	double ** store = (double **) malloc(instance.n * sizeof(double *));
	for (int i = 0; i < instance.n; i++) {
		store[i] = (double *) malloc(instance.n * sizeof(double));
	}

	for (int i = 0; i < instance.n; i++) {
		for (int j = 0; j < instance.n; j++) {
			if(i == j) {
				store[i][j] = 0;
			} else {
				store[i][j] = INFINITY;
			}
		}
	}

	int solution_distance = INFINITY; 

	for (int i = 0; i < instance.n; i++) {
		
		double distance;
		for (int j = 0; i < instance.n; i++) {
			if(i == j) {
				break;
			}
			
			if(store[i][j] != INFINITY) {
				distance = store[i][j];
			} else if(store[j][i] != INFINITY) {
				distance = store[j][i];
			} else {
				distance = getDistance(instance.points[i], instance.points[j]);
				store[i][j] = distance;
				store[j][i] = distance;
			}	
		}
		
	}

	return sol;
}

int recursiveTopDown(double ** store, vector<int> instance, int start, int end) {
	if(start == end) {
		return 0;
	} else {
		
	}
}