#include "ShortestPathAlgorithms.h"
#include "ParseFile.h"

using namespace std;

extern Vertex<int>* must;

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
bool walkingRelax(Edge<T>* edge){
    if (edge->getOrig()->getDist() + edge->getWalkTime() < edge->getDest()->getDist()) { // we have found a better way to reach v
        edge->getDest()->setDist(edge->getOrig()->getDist() + edge->getWalkTime()); // d[v] = d[u] + w(u,v)
        edge->getDest()->setPath(edge); // set the predecessor of v to u; in this case the edge from u to v
        return true;
    }
    return false;
}

template <class T>
void drivingDijkstra(Graph<T>* g, Vertex<T>* origin) {
    // Initialize the vertices
    for (auto v : g->getVertexSet()) {
        v->setDist(INF);
        v->setPath(nullptr);
    }
    auto s = origin;
    s->setDist(0);

    MutablePriorityQueue<Vertex<T>> q;
    q.insert(s);
    while (!q.empty()) {
        auto v = q.extractMin();
        if (v->isVisited()) continue;
        for (auto e : v->getAdj()) {
            if (e->isSelected()) continue;
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
void restrictedDrivingDijkstra(Graph<T>* g, Vertex<T>* origin, vector<Vertex<T>*> nAvoid, vector<Edge<T>*> eAvoid, Vertex<T>* must) {
    resetGraph(g);
    prepareRestrictedGraph(nAvoid, eAvoid);
    if (must) {
        drivingDijkstra(g, must);
    }
    else {
        drivingDijkstra(g, origin);
    }
}

template <class T>
static double getPath(Graph<T>* g, Vertex<T>* origin, Vertex<T>* dest, std::vector<T>& res) {
    res.clear();
    auto v = dest;
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
    if (res.empty() || res[0] != origin->getInfo()) {
        std::cout << "No Path Found!!" << std::endl;
        return -1;
    }
    return dist;
}


/*template <class T>
static double getRestrictedPath(Graph<T>* g, const int& origin, const int& dest, const Vertex<T>* must, std::vector<T>& res) {
    res.clear();
    auto v = g->findVertex(dest);
    double dist = v->getDist();
    if (v == nullptr || v->getDist() == INF) { // missing or disconnected
        return -1;
    }
    if (must != nullptr)
    {
        v = g->findVertex(origin);
        res.push_back(v->getInfo());
        dist += v->getDist();
        while (v->getPath() != nullptr) {
            v->getPath()->setSelected(true);
            v->getPath()->getReverse()->setSelected(true);
            v = v->getPath()->getOrig();
            v->setVisited(true);
            res.push_back(v->getInfo());
            if (must == v)
            {
                break;
            }

        }

        v->setVisited(false);

        v = g->findVertex(dest);
        res.push_back(v->getInfo());
        while (v->getPath()->getOrig() != must) {
            v->getPath()->setSelected(true);
            v->getPath()->getReverse()->setSelected(true);
            v = v->getPath()->getOrig();
            v->setVisited(true);
            res.push_back(v->getInfo());
        }

        v->setVisited(false);

        if (res.empty() || res[0] != origin) {
            std::cout << "No Path Found!!" << std::endl;
            return -1;
        }
        return dist;
    }

    else
    {
        return getPath(g, origin, dest, res);
    }

}*/

template <class T>
static double getRestrictedPath(Graph<T>* g, Vertex<T>* origin, Vertex<T>* dest, Vertex<T>* must, std::vector<T>& res) {
    res.clear();
    auto v_dest = dest;
    if (!v_dest || v_dest->getDist() == INF) return -1;

    if (must) {
        auto v_origin = origin;
        auto v_must = must;
        if (!v_origin || !v_must) return -1;

        std::vector<T> res1, res2;

        double dist1 = getPath(g, must, origin, res1);
        double dist2 = getPath(g, must, dest, res2);

        if (dist1 == -1 || dist2 == -1) return -1;

        reverse(res1.begin(), res1.end());
        if (!res1.empty()) {
            res1.pop_back();
        }
        res.insert(res.end(), res1.begin(), res1.end());
        res.insert(res.end(), res2.begin(), res2.end());

        return dist1 + dist2;
    }

    return getPath(g, origin, dest, res);
}

template <class T>
static void resetGraph(Graph<T>* g) {
    for (Vertex<T>* v : g->getVertexSet()) {
        v->setVisited(false);
        for (Edge<T>* e : v->getAdj()) {
            e->setSelected(false);
        }
    }
}

template <class T>
static void prepareRestrictedGraph(vector<Vertex<T>*> nA, vector<Edge<T>*> nE) {
    for (Vertex<T>* v : nA) {
        v->setVisited(true);
        //* this is a suggestion so we can never get to the restricted vertex
        for (Edge<T>* e : v->getAdj()) {
            e->setSelected(true);
        }
    }
    for (Edge<T>* e : nE) {
        e->setSelected(true);
    }
}

enum Distance {
    walk,
    drive,
};

template <class T>
static void dijkstra(Graph<T>* g, Vertex<T>* origin, Distance d) {
    // Initialize the vertices
    for (auto v : g->getVertexSet()) {
        v->setDist(INF);
        v->setPath(nullptr);
    }
    auto s = origin;
    s->setDist(0);

    MutablePriorityQueue<Vertex<T>> q;
    q.insert(s);
    while (!q.empty()) {
        auto v = q.extractMin();
        if (v->isVisited()) continue; // Ignore vertices that are marked as visited
        for (auto e : v->getAdj()) {
            if (e->isSelected()) continue; // Ignore edges that are marked as selected
            auto oldDist = e->getDest()->getDist();
            switch (d) {
                case Distance::drive:
                    if (relax(e)) {
                        if (oldDist == INF) {
                            q.insert(e->getDest());
                        }
                        else {
                            q.decreaseKey(e->getDest());
                        }
                    }
                    break;
                case Distance::walk:
                    if (walkingRelax(e)) {
                        if (oldDist == INF) {
                            q.insert(e->getDest());
                        }
                        else {
                            q.decreaseKey(e->getDest());
                        }
                    }
                    break;
            }
        }
    }
}