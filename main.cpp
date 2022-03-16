#include <iostream>
#include <sstream>
#include <vector>
#include <cmath>
#include <limits>
#include <utility>

using namespace std;

const double INF = numeric_limits<double>::max();
int nodes;
pair<int,int> *graph;

double distance(int x, int y) {
	return sqrt((graph[x].first - graph[y].first) * (graph[x].first - graph[y].first) + 
				(graph[x].second - graph[y].second) * (graph[x].second - graph[y].second));
}

double greedy(vector<int>& path, int begin) {
	double dt = 0, at = begin, to = begin, best = INF, d;
	
	for(int i = 0; i < nodes;i++){
		d = distance(at, i);
		if(i != at and d < best) {
			to = i;
			best = d;
		}
	}
	while(at != to) {
		path[at] = to;
		at = to;
		dt += best;
		best = INF;
		for(int i = 0; i < nodes;i++){
			d = distance(at, i);
			if(i != at and path[i] == -1 and d < best and i != begin) {
				to = i;
				best = d;
			}
		}
	}
	path[at] = begin;
	return dt + distance(at, begin);
}

int dfs(vector<int> g, int begin, int at) {
	if(g[at] == begin) return 1;
	return dfs(g, begin, g[at])+1;
}

double optimization(vector<int>& path, double dt) {
	double best = dt, d;
	vector<int> test_change;
	vector<int> best_change;
	for(int i = 0; i < path.size();i++) {
		for(int j = i+1; j < path.size();j++) {
			d = dt;
			test_change = path;
			test_change[i] = path[path[i]];
			test_change[j] = path[i];
			test_change[path[i]] = path[j];
			if(dfs(test_change, 0, 0) == nodes) {
				d -= distance(i, path[i]);
				d -= distance(j, path[j]);
				d -= distance(path[i], path[path[i]]);
				d += distance(i, path[path[i]]);
				d += distance(j, path[i]);
				d += distance(path[i], path[j]);
				if(d < best) {
					best = d;
					best_change = test_change;
				}
			}
		}
	}
	
	if(best != dt) {
		path = best_change;
	}
	
	return best;
}
int main() {
	int g;
	double x, y;
	// input
	string in, buf;
	getline(cin, in);
	getline(cin, in);
	getline(cin, in);
	getline(cin, in); // Dimension Line
	stringstream read(in);
	read >> buf >> buf >> nodes;
	getline(cin, in);
	getline(cin, in);
	
	graph = new pair<int,int>[nodes];
	// read nodes coord
	getline(cin, in);
	while(in != "EOF") {
		stringstream read(in);
		read >> g >> x >> y;
		graph[g-1] = {x, y};
		getline(cin, in);
	}
	
	vector<int> path(nodes, -1);
	double dt = greedy(path, 0);
	cout << dt << endl;
	
	double opt = optimization(path, dt);
	while(opt < dt) {
		dt = opt;
		cout << dt << endl;
		opt = optimization(path, dt);
	}
	cout << dt << endl;
	
	return 0;
}