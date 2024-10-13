// The main function of the program, which implements Dijkstra's algorithm on a graph.
// You should run this program in the root directory of the project.
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <sys/time.h>
#include <string>
#include <algorithm>
#include "MinHeap.h"
#define INF 1000000000        // TODO: Probably need to modify

struct Edge {
    int pnt;
    Edge* nxt;
    dist_t wgt;
    Edge(int _pnt = -1, Edge *_nxt = nullptr, dist_t _wgt = INF) : pnt(_pnt), nxt(_nxt), wgt(_wgt) {}
};

class Graph {
private:
    int V, E;
    Edge **head;

public:
    Graph(int _V=0, int _E=0){
        V = _V;
        E = _E;
        head = new Edge*[V];
        std::fill(head, head + V, nullptr);
    }

    ~Graph() {
        delete[] head;
    }

    void addEdge(int u, int v, dist_t w) {
        Edge *newEdge = new Edge(v, head[u], w);
        head[u] = newEdge;
    }

    dist_t dijkstra(int src, int dst) {
        // TODO: Implement Dijkstra's algorithm
        // You can use PriorityQueue<dist_pair> as the priority queue
        
    }
};

int main(int argc, char *argv[]) {
    std::string graphFileName = std::string("data/processed/") + std::string(argv[1]) + std::string(".gr");
    FILE *graphFile = fopen(graphFileName.c_str(), "r");
    
    int V, E;
    fscanf(graphFile, "%d%d", &V, &E);

    Graph G(V, E);
    for (int i = 0; i < E; i++) {
        int u, v, w;
        fscanf(graphFile, "%d%d%d", &u, &v, &w);
        G.addEdge(u, v, w);
    }
    fclose(graphFile);

    int numEpochs = std::stoi(argv[2]);
    double totalTime = 0.0;
    for (int epoch = 0; epoch < numEpochs; epoch++) {
        std::string queryFileName = std::string("data/queries/") + std::string(argv[1]) + std::string("_") + std::to_string(epoch) + std::string(".qry");
        FILE *queryFile = fopen(queryFileName.c_str(), "r");
        
        int Q;
        fscanf(queryFile, "%d", &Q);
        
        int *src = new int[Q];
        int *dst = new int[Q];
        dist_t *result = new dist_t[Q];

        for (int i = 0; i < Q; i++) {
            fscanf(queryFile, "%d%d", &src[i], &dst[i]);
        }
        fclose(queryFile);

        START_TIMER;
        for (int i = 0; i < Q; i++) {
            result[i] = G.dijkstra(src[i], dst[i]);
        }
        STOP_TIMER(totalTime);

        std::string resultFileName = std::string("data/results/") + std::string(argv[1]) + std::string("_") + std::to_string(epoch) + std::string(".res");
        FILE *resultFile = fopen(resultFileName.c_str(), "w");
        for (int i = 0; i < Q; i++) {
            fprintf(resultFile, "%d\n", result[i]);
        }
        fclose(resultFile);

        delete[] src;
        delete[] dst;
        delete[] result;
    }
    return 0;
}
