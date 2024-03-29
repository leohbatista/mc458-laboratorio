#ifndef SOLVER_H
#define SOLVER_H
#include <iostream>
#include <vector>
#include <map>
#include <cmath>
#include "point.h"
#include "instance.h"
#include <bits/stdc++.h> 
#include <algorithm>
#include <chrono>
#include <limits>

#define M 32

using namespace std;

double getDistance(Point p1, Point p2);
double memorizedDistance(double ** store, Instance &instance, int i, int j);
vector<int> solveBottomUp(Instance &instance, int timelimit, chrono::high_resolution_clock::time_point &started);

void recursiveTopDown(Instance &instance, int size, vector<int> permutation, double ** store, bool * used_flags, double * min_distance, vector<int> &solution, chrono::high_resolution_clock::time_point &started);
vector<int> solveTopDown(Instance &instance, int timelimit, chrono::high_resolution_clock::time_point &started);

#endif // SOLVER_H