#include "ShortestPathAlgorithms.h"
using namespace std;

template <class T>
bool relax(Edge<T>* edge) { // d[u] + w(u,v) < d[v]
    if (edge->getOrig()->getDist() + edge->getDriveTime() < edge->getDest()->getDist()) { // we have found a better way to reach v
        edge->getDest()->setDist(edge->getOrig()->getDist() + edge->getDriveTime()); // d[v] = d[u] + w(u,v)
        edge->getDest()->setPath(edge); // set the predecessor of v to u; in this case the edge from u to v
        return true;
    }
    return false;
}

template <class T>
void drivingDijkstra(Graph<T>* g, const int& origin) {
    // Initialize the vertices
    for (auto v : g->getVertexSet()) {
        v->setDist(INF);
        v->setPath(nullptr);
    }
    auto s = g->findVertex(origin);
    s->setDist(0);

    MutablePriorityQueue<Vertex<T>> q;
    q.insert(s);
    while (!q.empty()) {
        auto v = q.extractMin();
        if(v->isVisited()) continue;
        for (auto e : v->getAdj()) {
            if(e->isSelected()) continue;
            auto oldDist = e->getDest()->getDist();
            if (relax(e)) {
                if (oldDist == INF) {
                    q.insert(e->getDest());
                }
                else {
                    q.decreaseKey(e->getDest());
                }
            }
        }
    }
}

template <class T>
static double getPath(Graph<T>* g, const int& origin, const int& dest, std::vector<T>& res) {
    res.clear();
    auto v = g->findVertex(dest);
    double dist = v->getDist();
    if (v == nullptr || v->getDist() == INF) { // missing or disconnected
        return -1;
    }
    res.push_back(v->getInfo());
    while (v->getPath() != nullptr) {
        v->getPath()->setSelected(true);
        v->getPath()->getReverse()->setSelected(true);
        v = v->getPath()->getOrig();
        v->setVisited(true);
        res.push_back(v->getInfo());
    }
    v->setVisited(false);
    reverse(res.begin(), res.end());
    if (res.empty() || res[0] != origin) {
        std::cout << "No Path Found!!" << std::endl;
        return -1;
    }
    return dist;
}

template <class T>
static void resetGraph(Graph<T>* g){
    for(Vertex<T>* v : g->getVertexSet()){
        v->setVisited(false);
        for(Edge<T>* e : v->getAdj()){
            e->setSelected(false);
        }
    }
}