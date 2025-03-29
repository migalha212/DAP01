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
/**
 * @brief Computes the shortest paths from a given origin vertex to all other vertices in the graph using Dijkstra's algorithm.
 * 
 * @param g Pointer to the graph on which the algorithm will be executed.
 * @param origin Pointer to the origin vertex from which the shortest paths will be calculated.
 * @param distance Decides between using Driving edges or Walking edges.
 * 
 * O(|E| log |V|) time complexity, O(|V|) space complexity.
 * 
 * @note The graph should not contain negative weight edges, as Dijkstra's algorithm does not handle them correctly.
 */
void dijkstra(Graph<T>* g, Vertex<T>* origin, Distance distance);

template <class T>
void restrictedDrivingDijkstra(Graph<T>* g, Vertex<T>* origin, std::vector<Vertex<T>*> nAvoid, std::vector<Edge<T>*> eAvoid, Vertex<T>* must);

template <class T>
//* Auxiliary method from the TP03 exercises
static double getPath(Graph<T>* g, Vertex<T>* origin, Vertex<T>* dest, std::vector<T>& res, const bool& rev);

template <class T>
static double getRestrictedPath(Graph<T>* g, Vertex<T>* origin, Vertex<T>* dest, Vertex<T>* must, std::vector<T>& res);

template <class T>
/**
 * @brief Resets the graph to close to its initial state, having all vertex and nodes be unselected.
 * 
 * O(|V| + |E|) time complexity, O(1) space complexity the method itself does not alocate extra space.
 */
static void resetGraph(Graph<T>* g);


template <class T>
/**
 * @brief Prepares a restricted graph by marking specified vertices and edges as visited or selected so they are ignored in the algorithm.
 *
 * O(|E|) time complexity, O(1) space complexity the method itself does not alocate extra space.
 *
 * @param nA A vector of pointers to the vertices that should be avoided.
 * @param nE A vector of pointers to the edges that should be avoided.
 */
static void prepareRestrictedGraph(std::vector<Vertex<T>*> nA, std::vector<Edge<T>*> nE);

#endif //SHORTESTPATHALGORITHMS_H
