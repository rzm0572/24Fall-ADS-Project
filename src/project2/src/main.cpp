// The main function of the program, which implements Dijkstra's algorithm on a graph.
// You should run this program in the root directory of the project.
#include <sys/time.h>

#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <string>

#include "MinHeap.h"
#define INF 1000000000  // TODO: Probably need to modify

std::string get_timestamp() {
    time_t now = time(0);
    tm *ltm = localtime(&now);
    return std::to_string(1900 + ltm->tm_year) + "-" + std::to_string(1 + ltm->tm_mon) + "-" + std::to_string(ltm->tm_mday) + " " + std::to_string(ltm->tm_hour) + ":" + std::to_string(ltm->tm_min) + ":" + std::to_string(ltm->tm_sec);
}

struct Edge {
    int pnt;
    Edge *nxt;
    dist_t wgt;
    Edge(int _pnt = -1, Edge *_nxt = nullptr, dist_t _wgt = INF) : pnt(_pnt), nxt(_nxt), wgt(_wgt) {}
};
/*
包含了使用迪杰斯特拉算法求解图中最短路径的类 Graph
*/
class Graph {
   private:
    int V, E;     // 顶点数和边数
    Edge **head;  // 链式前向星邻接表头指针

   public:
    Graph(int _V = 0, int _E = 0) {  // 初始化图，确定顶点数和边数
        V = _V;
        E = _E;
        head = new Edge *[V];
        std::fill(head, head + V, nullptr);
    }

    ~Graph() {
        delete[] head;
    }
    /*
        添加边
    */
    void addEdge(int u, int v, dist_t w) {
        Edge *newEdge = new Edge(v, head[u], w);
        head[u] = newEdge;
    }
    /*
        迪杰斯特拉算法求解图中最短路径
        返回从源点 src 到目的点 dst 的最短路径长度
    */
    dist_t dijkstra(int src, int dst) {
        // TODO: Implement Dijkstra's algorithm
        // You can use PriorityQueue<dist_t> as the priority queue
        int *vis = (int *)malloc((V + 10) * sizeof(int));            // 记录是否访问过
        dist_t *dist = (dist_t *)malloc((V + 10) * sizeof(dist_t));  // 记录最短路径长度
        std::fill(dist, dist + V + 10, INF);                         // 初始化为无穷大
        std::fill(vis, vis + V + 10, 0);                             // 初始化为未访问
        PriorityQueue<dist_t> heap(V);                               // 优先队列
        dist[src] = 0;                                               // 起点到起点的距离为 0
        heap.insert(distPair(src, 0));                               // 入队
        while (heap.getSize() > 0) {                                 // 队列非空即有元素可能更新最短路
            distPair x = heap.findMin();                             // 取出队首元素
            heap.deleteMin();                                        // 删除队首元素
            if (vis[x.key]) {                                        // 已经访问过
                continue;                                            // 跳过
            }
            vis[x.key] = true;                            // 标记为已访问
            for (Edge *i = head[x.key]; i; i = i->nxt) {  // 遍历 x 相连的节点
                int v = i->pnt;                           // 相连节点
                if (dist[v] > dist[x.key] + i->wgt) {     // 更新距离
                    dist[v] = dist[x.key] + i->wgt;
                    if (!heap.insert(distPair(v, dist[v]))) {  // 如果 v 在队列中，更新其距离，否则入队
                        heap.decreaseKey(distPair(v, dist[v]));
                    }
                    // heap.insert(distPair(v,dist[v]));
                }
            }
        }
        return (vis[dst]) ? dist[dst] : INF;  // 若目的点未访问，则返回无穷大，否则返回目的点到源点的最短路径长度
    }
};

int main(int argc, char *argv[]) {
    std::string logFileName = std::string("log/") + "[" + get_timestamp() + "] " + std::string(tostr(HEAPTYPE)) + "_" + std::string(argv[1]) + ".log";
    FILE *logFile = fopen(logFileName.c_str(), "w");

    std::string graphFileName = std::string("data/processed/") + std::string(argv[1]) + ".gr";
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
    logger(logFile, "Graph loaded.\n")

        int numEpochs = argc > 2 ? std::stoi(argv[2]) : 3;
    double totalTime = 0.0;
    for (int epoch = 0; epoch < numEpochs; epoch++) {
        std::string queryFileName = std::string("data/queries/") + std::string(argv[1]) + "_" + std::to_string(epoch) + ".qry";
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
        logger(logFile, "Query set %d loaded.\n", epoch);

        START_TIMER;
        for (int i = 0; i < Q; i++) {
            result[i] = G.dijkstra(src[i], dst[i]);
        }
        STOP_TIMER(totalTime);

        std::string resultFileName = std::string("data/results/") + std::string(tostr(HEAPTYPE)) + "_" + std::string(argv[1]) + "_" + std::to_string(epoch) + ".res";
        FILE *resultFile = fopen(resultFileName.c_str(), "w");
        for (int i = 0; i < Q; i++) {
            fprintf(resultFile, "%d\n", result[i]);
        }
        fclose(resultFile);

        logger(logFile, "Result set %d saved.\n", epoch);

        delete[] src;
        delete[] dst;
        delete[] result;
    }

    logger(logFile, "Total time: %.6f s\n", totalTime);
    fclose(logFile);
    return 0;
}
