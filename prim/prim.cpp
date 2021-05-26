#include<bits/stdc++.h>

using namespace std;

typedef long long int lli;

typedef vector<lli> vi;
typedef vector<pair<lli,lli>> v;
typedef vector<v> vv;
vv graph;
vi visited;

lli prim(lli qnt_vertices, lli begin) {

    priority_queue<pair<lli,lli>, v, greater<pair<lli,lli>>> pq;
    pq.push(make_pair(0,begin));
    lli cost = 0;
    while(!pq.empty()) {

        lli head = pq.top().second;
        if (!visited[head]) {
            cost += pq.top().first;
        }
        pq.pop();
        
        visited[head] = 1;

        for(auto x: graph[head]) {

            if(!visited[x.first]) {
                pq.push(make_pair(x.second,x.first));
            }
        }
    }
    return cost;
}

int main () {   
    lli qnt_vertices, qnt_arestas;
    cin >> qnt_vertices >> qnt_arestas;
    graph.resize(qnt_vertices+1);
    visited.resize(qnt_vertices+1,0);
    lli u, v, c;
    for(lli i = 0; i < qnt_arestas; ++i) {
        cin >> u >> v >> c;
        graph[u].push_back(make_pair(v,c));
        graph[v].push_back(make_pair(u,c));
    }
    lli cost = prim(qnt_vertices,1);
    cout << cost << endl;
    return 0;
}
