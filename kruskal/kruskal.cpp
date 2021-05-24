#include <iostream>
#include <vector>
#include <algorithm>
#include <string.h>
#include <stdio.h>
#include <fstream>

using namespace std;

class GraphEdge{
    int firstVertex, secondVertex, weightValue;

public:
    GraphEdge(int firstV, int secondV, int weightValue){
        firstVertex = firstV;
        secondVertex = secondV;
        this->weightValue = weightValue;
    }

    int takeFirstVertex(){
        return firstVertex;
    }

    int takeSecondVertex(){
        return secondVertex;
    }

    int takeWeightValue(){
        return weightValue;
    }

    bool operator < (const GraphEdge& graphEdge2) const{
        return (weightValue < graphEdge2.weightValue);
    }
};

class Graph{
    int x;

public:
    vector<GraphEdge> graphEdges;
    Graph(int x){
        this->x = x;
    }

    void addArestaGrafo(int firstV, int secondV, int weightValue){
        GraphEdge graphEdge(firstV, secondV, weightValue);
        graphEdges.push_back(graphEdge);
    }

    int search(int setI[], int a){
        if(setI[a] == -1)
            return a;
        return search(setI, setI[a]);
    }

    void join(int setI[], int firstV, int secondV){
        int firstV_set = search(setI, firstV);
        int secondV_set = search(setI, secondV);
        setI[firstV_set] = secondV_set;
    }

    void algorithmOfKruskal(){
        vector<GraphEdge> tree;
        int size_graphEdges = graphEdges.size();

        sort(graphEdges.begin(), graphEdges.end());

        int * setI = new int[graphEdges.size()];

        memset(setI, -1, sizeof(int) * graphEdges.size());

        for(int i = 0; i < size_graphEdges; i++){
            int firstV = search(setI, graphEdges[i].takeFirstVertex());
            int secondV = search(setI, graphEdges[i].takeSecondVertex());

            if(firstV != secondV){
                tree.push_back(graphEdges[i]);
                join(setI, firstV, secondV);
            }
        }

        int size_tree = tree.size();
        int res = 0;

        for(int i = 0; i < size_tree; i++){
            res += tree[i].takeWeightValue();
            int firstV = tree[i].takeFirstVertex();
            int secondV = tree[i].takeSecondVertex();
            cout << "(" << firstV << ", " << secondV << ") = " << tree[i].takeWeightValue() << endl;
        }
        cout << "peso: "<< res << endl;
    }
};

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

int main(int argc, char *argv[]){
    
    int V,E,src,dest,weight; 
    ifstream file;
        if(!getFile(argc, argv, file)) {
            exit(0);
        }

        file >> V;
        file >> E;

        Graph z(V);

        while(file >> src && file >> dest && file >> weight) {
            z.addArestaGrafo(src, dest, weight);
        }
        file.close();

    z.algorithmOfKruskal();

    return 0;
}