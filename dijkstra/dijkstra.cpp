#include <bits/stdc++.h>
#include <iostream>

using namespace std;

typedef pair<int, int> par;

int range[15000];
int processed[15000];

vector<par> nextDoor[15000];

void dijkstra(int x) {
    range[x] = 0;

    priority_queue<par, vector<par>, greater<par>> queue;
    queue.push(par(range[x], x));

    while (true) {
        int nCurrent = -1;

        while (!queue.empty()) {
            int current = queue.top().second;
            queue.pop();

            if (!processed[current]) {
                nCurrent = current;
                break;
            }
        }

        if (nCurrent == -1)
            return;

        for (int i = 0; i < (int) nextDoor[nCurrent].size(); i++) {
            int dist = nextDoor[nCurrent][i].first;
            int current = nextDoor[nCurrent][i].second;

            if (range[current] > range[nCurrent] + dist) {
                range[current] = range[nCurrent] + dist;
                queue.push(par(range[current], current));
            }
        }
    }
}

bool checkFileExistence(string fileName) {
    ifstream f(fileName);
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
    int t = 1, i;

    int src, dest, weight, V, E;
    ifstream file;
    if(!getFile(argc, argv, file)) {
        exit(0);
    }

    file >> V;
    file >> E;

    for (i = 0; i <= V + 5; i++) {
        range[i] = INT_MAX;
        processed[i] = 0;
    }

    while(file >> src && file >> dest && file >> weight) {
        nextDoor[src].push_back(par(weight, dest));
        nextDoor[dest].push_back(par(weight, src));
    }
  
    file.close();

    dijkstra(1);
    cout << range[V] << endl;

    return 0;
}