#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
vector<vector<int>> component;
vector<bool> visited;
//Depth first search
void dfs(int v, vector<vector<int>> g, int c) {
	if(!visited[v]) {
		visited[v] = true;
		component[c].push_back(v);
		for(vector<int>::iterator i = g[v].begin();i != g[v].end();i++) {
			dfs(*i, g, c);
		}
	}
}

int main() {
	int n;
	int input1, input2;
	cin >> n;
	vector<vector<int>> g(n, vector<int>());
	visited = vector<bool>(n, false);
	component = {};
	for(int i = 0; i < n;i++) {
		cin >> input1 >> input2;
		g[input1].push_back(input2);
		g[input2].push_back(input1);
	}
		
	int c = 0;
	for(int i = 0; i < n;i++) {
		if(not visited[i]){
			component.push_back({});
			dfs(i, g, c);
			c++;
		}
	}
		
	for(int i = 0;i < component.size();i++) {
		for(int j = 0;j < component[i].size();j++) {
			cout << component[i][j] << ",";
		}
		cout << endl;
	}
	cout << c << " connected components\n\n";
	return 0;
}