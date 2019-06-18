#include "solver.h"

const double infinity = std::numeric_limits<double>::infinity();

double getDistance(Point p1, Point p2){
	double delta_x = p1.x - p2.x;
	double delta_y = p1.y - p2.y;

	return sqrt(delta_x * delta_x + delta_y * delta_y); 
}

double memorizedDistance(double ** store, Instance &instance, int i, int j) {
	if(store[i][j] != infinity) {
		return store[i][j];
	} else if(store[j][i] != infinity) {
		return store[j][i];
	} else {
		double distance = getDistance(instance.points[i], instance.points[j]);
		store[i][j] = distance;
		store[j][i] = distance;
		return distance;
	}
}

vector<int> solveBottomUp(Instance &instance, int timelimit, chrono::high_resolution_clock::time_point &started){
	vector<int> sol;
	
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



void recursiveTopDown(double ** store, Instance &instance, int size, vector<int> permutation, bool * used_flags, double * min_distance, vector<int> &solution) {
	if(size == instance.n-1) {
		permutation.push_back(instance.n-1);

		// cout << "Perm.: ";
		double distance = 0.0;
		for (int i = 0; i < instance.n-1; i++) {
			distance += memorizedDistance(store, instance, permutation[i], permutation[i+1]);
			// cout << permutation[i] << " ";
		}
		// cout << endl;

		if(distance < *min_distance) {
			*min_distance = distance;
			solution.erase(solution.begin(), solution.end());
			for (int i = 0; i < permutation.size(); i++) {
				solution.push_back(permutation[i]);
			}
		}
	} else if(size < instance.n) { 
		for (int i = 1; i < instance.n-1; i++) {
			if(used_flags[i]) {
				continue;
			} else {
				used_flags[i] = true;
				permutation.push_back(i);
				recursiveTopDown(store, instance, size+1, permutation, used_flags, min_distance, solution);
				permutation.pop_back();
				used_flags[i] = false;
			}
		}
	}
}

vector<int> solveTopDown(Instance &instance, int timelimit, chrono::high_resolution_clock::time_point &started){		
	// Creates memorization table
	double ** store = (double **) malloc(instance.n * sizeof(double *));
	for (int i = 0; i < instance.n; i++) {
		store[i] = (double *) malloc(instance.n * sizeof(double));
	}
	
	bool * used = (bool *) malloc(instance.n * sizeof(bool));

	for (int i = 0; i < instance.n; i++) {
		used[i] = false;

		for (int j = 0; j < instance.n; j++) {
			if(i == j) {
				store[i][j] = 0.0;
			} else {
				store[i][j] = infinity;
			}
		}
	}
	
	vector<int> permutation;
	vector<int> solution;
	permutation.push_back(0);

	double min_distance = infinity;

	recursiveTopDown(store, instance, 1, permutation, used, &min_distance, solution);

	return solution;
}