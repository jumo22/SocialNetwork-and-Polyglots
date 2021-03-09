#include <iostream>
#include <fstream>
#include <list>
#include <stack>
//Iulia Moroti 1231A

using namespace std;
class Graph{
    int N;
    list<int> *neighbours;
    void TarjanDFS(int node, int disc[], int low[], stack<int> *stackdfs, bool isInStack[]);

public:
    Graph(int N);
    void addEdge(int u, int v);
    void TarjanPrep(int* low, int *disc);
};

Graph::Graph(int N){
    this->N = N;
    neighbours = new list<int>[N];
}

void Graph::addEdge(int u, int v){
    neighbours[u].push_back(v);
}

void Graph::TarjanDFS(int node, int disc[], int low[], stack<int> *stackdfs, bool isInStack[]){
    static int time = 1;
    low[node] = disc[node] = time++;
    stackdfs->push(node);
    isInStack[node] = true;

    list<int>:: iterator i=neighbours->begin();
    for (i = neighbours[node].begin(); i != neighbours[node].end(); ++i){
        int v = *i;
        if (disc[v] == -1){
            TarjanDFS(v, disc, low, stackdfs, isInStack);
            low[node] = min( low[node], low[v]);
        }
        else if (isInStack[v] == true){
                low[node] = min( low[node], disc[v]);
        }
    }
    if (low[node] == disc[node]){
        int temp;
        while(stackdfs->top() != node){
            temp = stackdfs->top();
            isInStack[temp] = false;
            low[temp] = disc[node];
            stackdfs->pop();
        }
        isInStack[stackdfs->top()] = false;
        stackdfs->pop();
    }
}

void Graph::TarjanPrep(int *low, int *disc){
    bool isInStack[N];
    stack<int> *stackdfs = new stack<int>();

    for (int i = 0; i <= N; i++){
        low[i] = -1;
        disc[i] = -1;
        isInStack[i] = false;
    }

    for (int i = 0; i < N; i++){
        if (disc[i] == -1)
            TarjanDFS(i, disc, low, stackdfs, isInStack);
    }
}

int main(){

    ifstream graphin("socialnetwork.in");
    ofstream graphout("socialnetwork.out");
    if (!graphin){
        cerr << "No such file found.";
        return -1;
    }

    int N, M, T, line_no = 1, u, v;
    string line;

    graphin >> N >> M >> T;
    line_no++;
    Graph graph(N);
    int low[N];
    int disc[N];

    while ((line_no <= ( M + 1)) && getline(graphin, line)){
        line_no++;
        graphin >> u >> v;
        graph.addEdge(u-1, v-1);
    }

    graph.TarjanPrep(low, disc);

    while ((line_no < (M + T + 2)) && getline(graphin, line)){
        graphin >> u >> v;
        if ( low[u-1] == low[v-1] )
            graphout<<"true\n";
        else
            graphout<<"false\n";
        line_no++;
    }
    graphin.close();
    graphout.close();

    return 0;
}
