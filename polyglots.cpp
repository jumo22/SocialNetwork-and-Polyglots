#include <iostream>
#include <fstream>
#include <list>
#include <string>
//Iulia Moroti 1231A

using namespace std;

int compareTheWords(string word1, string word2){
    unsigned contor = 0;
    for (unsigned c = 0; c < word1.size(); c++)
        if (word1[c] != word2[c])
            contor++;
    return contor;
}

class Graph{
    int N;
    list<int> *neighbours;

public:
    Graph(int N);
    void addNodeS(int u);
    void addEdges(string* words, int N, list<int> *first);
    bool BFS(int s, int e, int N, int dist[]);
    int findShortestDistance(int start, int dest, int N, int dist[]);
};

Graph::Graph(int N){
    this->N = N;
    neighbours = new list<int>[N];
}

void Graph::addNodeS(int u){
    neighbours->push_back(u);
}

void Graph::addEdges(string* words, int N, list<int> *first){
     list<int>:: iterator i;
     for (i = first->begin(); i != first->end(); i++){
            int v = *i;
            for( int j = 0; j < N; j++)
                if (compareTheWords(words[v], words[j]) == 1)
                    neighbours[v].push_back(j);
    }
}

bool Graph::BFS(int start, int dest, int N, int dist[]) {
    list<int> queue;
    bool visited[N];
    for (int i = 0; i < N; i++) {
        visited[i] = false;
        dist[i] = 10000;
    }
    visited[start] = true;
    dist[start] = 0;
    queue.push_back(start);
    while (!queue.empty()) {
        int u = queue.front();
        queue.pop_front();
        list<int>::iterator i = neighbours->begin();
        for (i = neighbours[u].begin(); i != neighbours[u].end(); ++i) {
            int v = *i;
            if (visited[v] == false) {
                visited[v] = true;
                dist[v] = dist[u] + 1;
                queue.push_back(v);
                if (v == dest)
                   return true;
            }
        }
    }

    return false;
}

int Graph::findShortestDistance(int start, int dest, int N, int dist[]){
    if ( BFS(start, dest, N, dist) == false ){
        return 10000;
    }
    return dist[dest];
}

int main(){
    ifstream polin("polyglots.in");
    ofstream polout("polyglots.out");
    if (!polin){
        cerr << "No such file found.";
        return -1;
    }

    string startw, endw, line, word;
    int line_no = 1, N;
    int indexEndw;

    polin >> startw;
    polin >> endw;
    polin >> N;
    Graph graph(N + 1);
    string words[N + 1];
    words[0] = startw;
    graph.addNodeS(0);
    list<int> *first = new list<int>[N + 1];
    first->push_back(0);
    while(getline(polin, line) && (line_no <= N)){
        polin >> word;
        int res = compareTheWords(word, endw);
        if( res == 0){
            indexEndw = line_no;
            }
        words[line_no] = word;
        first->push_back(line_no);
        line_no++;
    }
    N += 1;
    graph.addEdges(words, N, first);
    int dist[N];
    int result = graph.findShortestDistance(0, indexEndw, N, dist);
    if(result == 10000)
        polout << "-1\n";
    else
        polout << result<<endl;
    polin.close();
    polout.close();
    return 0;
}
