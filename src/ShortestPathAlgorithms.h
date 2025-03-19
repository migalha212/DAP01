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
void dijkstra(Graph<T>* g, const int& origin);

template <class T>
//* Auxiliary method from the TP03 exercises
static std::vector<T> getPath(Graph<T>* g, const int& origin, const int& dest);

#endif //SHORTESTPATHALGORITHMS_H
