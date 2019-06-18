#include "solver.h"

double getDistance(Point p1, Point p2){
	double delta_x = p1.x - p2.x;
	double delta_y = p1.y - p2.y;

	return sqrt(delta_x * delta_x + delta_y * delta_y); 
}

double memorizedDistance(double ** store, Instance &instance, int i, int j) {
	if(store[i][j] != INFINITY) {
		return store[i][j];
	} else if(store[j][i] != INFINITY) {
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



void recursiveTopDown(double ** store, Instance &instance, int size, vector<int> res, bool * used) {
	// cout << "(" << size << "," << instance.n-1 <<") Used: ";
	// for (int i = 0; i < instance.n; i++){
	// 	cout << used[i] << " ";
	// }
	// cout << endl;

	if(size == instance.n) {
		cout << "Sequence: ";
		for (int i = 0; i < instance.n; i++){
			cout << res[i] << " ";
		}
		cout << endl;
	} else if(size < instance.n) { 
		for (int i = 0; i < instance.n; i++) {
			if(used[i]) {
				// cout << " break " << endl;
				continue;
			} else {
				used[i] = true;
				res.push_back(i);
				recursiveTopDown(store, instance, size+1, res, used);
				res.pop_back();
				used[i] = false;
			}
		}
	}
}

vector<int> solveTopDown(Instance &instance, int timelimit, chrono::high_resolution_clock::time_point &started){
	vector<int> sol;
	
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
				store[i][j] = 0;
			} else {
				store[i][j] = INFINITY;
			}
		}
	}
	
	vector<int> res;

	recursiveTopDown(store,instance,0,res,used);

	return sol;
}