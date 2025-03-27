#ifndef SHORTESTPATHALGORITHMS_H
#define SHORTESTPATHALGORITHMS_H

#include <Graph.h>
#include <MutablePriorityQueue.h>

// ! Do note that method descriptions and names aren't final, only built as a demo for the stucture that might be best

template <class T>
//* Basic Edge relaxation from the TP03 exercises
bool relax(Edge<T>* edge);


template <class T>
//* Simple dijkstra's Single Source Shortest Path Algorithm from the TP03 exercises
void drivingDijkstra(Graph<T>* g, const int& origin);

template <class T>
void restrictedDrivingDijkstra(Graph<T>* g, const int& origin, std::vector<Vertex<T>*> nAvoid, std::vector<Edge<T>*> eAvoid, const Vertex<T>* must);

template <class T>
//* Auxiliary method from the TP03 exercises
static double getPath(Graph<T>* g, const int& origin, const int& dest, std::vector<T>* res);

template <class T>
static double getRestrictedPath(Graph<T>* g, const int& origin, const int& dest, const int& must, std::vector<T>& res);

template <class T>
static void resetGraph(Graph<T>* g);

template <class T>
static void prepareRestrictedGraph(std::vector<Vertex<T>*> nA, std::vector<Edge<T>*> nE);

#endif //SHORTESTPATHALGORITHMS_H
