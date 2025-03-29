#ifndef SHORTESTPATHALGORITHMS_H
#define SHORTESTPATHALGORITHMS_H

#include <Graph.h>
#include <MutablePriorityQueue.h>

// ! Do note that method descriptions and names aren't final, only built as a demo for the stucture that might be best
enum Distance
{
    walk,
    drive,
};

template <class T>
//* Basic Edge relaxation from the TP03 exercises
bool relax(Edge<T>* edge);


template <class T>
//* Simple dijkstra's Single Source Shortest Path Algorithm from the TP03 exercises
void dijkstra(Graph<T>* g, Vertex<T>* origin, Distance distance);

template <class T>
void restrictedDrivingDijkstra(Graph<T>* g, Vertex<T>* origin, std::vector<Vertex<T>*> nAvoid, std::vector<Edge<T>*> eAvoid, Vertex<T>* must);

template <class T>
//* Auxiliary method from the TP03 exercises
static double getPath(Graph<T>* g, Vertex<T>* origin, Vertex<T>* dest, std::vector<T>& res,const bool &rev);

template <class T>
static double getRestrictedPath(Graph<T>* g, Vertex<T>* origin, Vertex<T>* dest, Vertex<T>* must, std::vector<T>& res);

template <class T>
static void resetGraph(Graph<T>* g);

template <class T>
static void prepareRestrictedGraph(std::vector<Vertex<T>*> nA, std::vector<Edge<T>*> nE);

#endif //SHORTESTPATHALGORITHMS_H
