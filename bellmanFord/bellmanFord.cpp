#include <bits/stdc++.h>
#include <iostream>

#define lli long long int
using namespace std;

const int MAX_N = 99999; 
int n, m;
vector<pair<int, int>> graph[MAX_N];
int source = 0, dist[MAX_N], prv[MAX_N];

bool bellmanFord() {
	for (int i = 0; i < n; i ++) {
		dist[i] = MAX_N;
	} 

  	dist[source] = 0;
  
	for (int i = 0; i < n - 1; i ++) {
		for (int u = 0; u < n; u ++) {
			for (auto &v: graph[u]) {
				if (dist[u] + v.second < dist[v.first]){
					dist[v.first] = dist[u] + v.second, prv[v.first] = u;
				}
			}
		}
	}

	for (int u = 0; u < n; u ++) {
		for (auto &v: graph[u]) {
			if (dist[u] + v.second < dist[v.first]) {
				cout << "Negative cycle." << endl;
				return true;
			}
		}
	}

	cout << "To \t Dist" << endl;
	for (int i = 0; i < n; ++i) 
		cout << i << "\t" << dist[i] << endl;
	
	return false;
}

bool checkFileExistence(string filename) {
    ifstream f(filename);
    return f.is_open();
}

bool getFile(int argc, char *argv[], ifstream& file) {   
    
    if (argc <= 1) {
        cout << "Incorrect arguments." << endl;
        return false;
    } else if (!checkFileExistence(argv[1])) {
        cout << "File " << argv[1] << " not found." << endl;
        return false;
    }

    file.open(argv[1]);

    return true;
}

int main(int argc, char *argv[]) {
	int src, dest, weight;
  
	ifstream file;
	if(!getFile(argc, argv, file)) {
        exit(0);
    }

    file >> n;
    file >> m;

    while(file >> src && file >> dest && file >> weight) {
    	graph[src].push_back({dest, weight});
    }
    file.close();

  	bellmanFord();

  	return 0;
}