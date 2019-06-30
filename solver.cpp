#include "solver.h"

const double infinity_const = std::numeric_limits<double>::infinity();

double getDistance(Point p1, Point p2){
	double delta_x = p1.x - p2.x;
	double delta_y = p1.y - p2.y;

	return sqrt(delta_x * delta_x + delta_y * delta_y); 
}

// Check if the distance was already saved on memorization table and calculate it if necessary
double getMemorizedDistance(double ** store, Instance &instance, int i, int j) {
	if(store[i][j] != infinity_const) {
		return store[i][j];
	} else if(store[j][i] != infinity_const) {
		return store[j][i];
	} else {
		double distance = getDistance(instance.points[i], instance.points[j]);
		store[i][j] = distance;
		store[j][i] = distance;
		return distance;
	}
}

vector<int> solveBottomUp(Instance &instance, int timelimit, chrono::high_resolution_clock::time_point &started){
	vector<int> temp_sol;
	temp_sol.push_back(0);
	
	double ** store_dist = (double **) malloc(instance.n * sizeof(double *));
	int ** store_sol = (int **) malloc(instance.n * sizeof(int *));
	for (int i = 0; i < instance.n; i++) {
		store_dist[i] = (double *) malloc(instance.n * sizeof(double));
		store_sol[i] = (int *) malloc(instance.n * sizeof(int));
	}
	for (int i = 0; i < instance.n; i++) {
		for (int j = i; j < instance.n; j++) {
			if(i == j) {
				store_dist[i][j] = 0.0;
				store_sol[i][j] = 0;
			} else {
				store_dist[i][j] = infinity_const;
				store_dist[j][i] = infinity_const;
			}
		}
	}

	// for (int i = 0; i < instance.n; i++) {
	// 	for (int j = 0; j < instance.n; j++) {
	// 		cout << store_dist[i][j] << " ";
	// 	}
	// 	cout << endl << endl;
	// }


	double dist = getMemorizedDistance(store_dist, instance, 0, instance.n - 1);
	temp_sol.push_back(instance.n - 1);
	for(int i = 1; i < instance.n - 1; i++){
		//sol.push_back(i);

		double temp_dist, min_dist = infinity_const;
		int pos = 1;
		for(int j = 0; j < i; j++) {
			temp_dist = dist - getMemorizedDistance(store_dist, instance, temp_sol[j], temp_sol[j+1]) 
			+ getMemorizedDistance(store_dist, instance, temp_sol[j], i)
			+ getMemorizedDistance(store_dist, instance, i, temp_sol[j+1]);
			if(temp_dist < min_dist) {
				min_dist = temp_dist;
				pos = j+1;
			}
		}

		temp_sol.insert( temp_sol.begin() + pos, i );
		dist = min_dist;

		// cout << i << ")   ";
		// for (int k = 0; k < temp_sol.size(); k++) {
		// 	cout << temp_sol[k] << " ";
		// }
		// cout << dist;
		// cout << endl << endl;

		// get the time that has passed in seconds and check the timelimit
		auto done = chrono::high_resolution_clock::now();
		auto time = chrono::duration_cast<chrono::seconds>(done-started).count();
		
		if(time > timelimit){
			break;
		}
	}

	vector<int> sol (temp_sol.begin() + 1, temp_sol.end() - 1);

	// for (int i = 0; i < instance.n; i++) {
	// 	for (int j = 0; j < instance.n; j++) {
	// 		cout << store_dist[i][j] << " ";
	// 	}
	// 	cout << endl << endl;
	// }
	
	return sol;
}

// ---------------------------------------------------------------------------------
// Top-Down Solution:

void recursiveTopDown(Instance &instance, int size, vector<int> permutation, double ** store, bool * used_flags, double * min_distance, vector<int> &solution) {
	if(size == 1) {
		// Adds the end point to the permutation
		permutation.push_back(instance.n - 1);

		// Calculates the distance of current permutation
		double distance = 0.0;
		for (int i = 0; i < instance.n - 1; i++) {
			distance +=  getMemorizedDistance(store, instance, permutation[i], permutation[i+1]);
		}

		// Checks if the current distance is better than that we already know ande replace it if yes
		if(distance < *min_distance) {
			*min_distance = distance;
			solution.erase(solution.begin(), solution.end());
			for (int i = 0; i < permutation.size(); i++) {
				solution.push_back(permutation[i]);
			}
		}
	} else { 
		for (int i = 1; i < instance.n - 1; i++) {
			// Checks if current point is already on permutation
			if(used_flags[i]) {				
				continue;
			} else {
				// If the point is not already on permutation, add it to permutation and call recursive function
				used_flags[i] = true;
				permutation.push_back(i);
				recursiveTopDown(instance, size - 1, permutation, store, used_flags, min_distance, solution);
				permutation.pop_back();
				used_flags[i] = false;
			}
		}
	}
}

vector<int> solveTopDown(Instance &instance, int timelimit, chrono::high_resolution_clock::time_point &started){		
	// Array of booleans used to indicate which point have been 
	// already used on actiual combination
	bool * used = (bool *) malloc(instance.n * sizeof(bool));

	// Creates and initializates memorization table
	double ** store = (double **) malloc(instance.n * sizeof(double *));
	for (int i = 0; i < instance.n; i++) {
		store[i] = (double *) malloc(instance.n * sizeof(double));
		for (int j = 0; j < instance.n; j++) {
			if(i == j) {
				store[i][j] = 0.0;
			} else {
				store[i][j] = infinity_const;
			}
		}
		used[i] = false;
	}
	
	// Initialization of recursion parameters
	std::vector<int> permutation;
	std::vector<int> solution;
	double min_distance = infinity_const;

	permutation.push_back(0);

	// Recursive resolution
	recursiveTopDown(instance, instance.n-1, permutation, store, used, &min_distance, solution);

	// Removes start and end points of final solution
	solution.pop_back();
	solution.erase(solution.begin());

	return solution;
}