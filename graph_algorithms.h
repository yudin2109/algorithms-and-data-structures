#include <vector>
#include "binary_heap.h"

struct Edge {
    size_t from, to;
    long long weight;

    Edge(size_t _from, size_t _to, size_t _weight) {
        from = _from;
        to = _to;
        weight = _weight;
    }
};

long long INF = 1e18;

vector<long long> DijkstraShortestWays(const vector<vector<Edge>>& graph, size_t start) {
    size_t nNodes = graph.size();
    vector<long long> minDist(nNodes, INF);

    BinaryHeap<pair<long long, size_t>> heap;
    heap.insert({0, start});
    minDist[start] = 0;

    while (!heap.isEmpty()) {
        long long distance = heap.getMin().first;
        size_t v = heap.getMin().second;
        heap.extractMin();

        if (distance > minDist[v])
            continue;
        
        for (Edge edge : graph[v]) {
            if (minDist[edge.to] > minDist[v] + edge.weight) {
                minDist[edge.to] = minDist[v] + edge.weight;
                heap.insert({minDist[edge.to], edge.to});
        }
    }

    return minDist;
}