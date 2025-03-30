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
/**
 * @brief Relaxes the edge if a shorter path is found. Modified to work with driving time
 * 
 * @param edge Pointer to the edge to be relaxed.
 * @return true if the edge was relaxed, false otherwise.
 * 
 * O(1) time complexity, O(1) space complexity.
 */
bool relax(Edge<T>* edge);

template <class T>
/**
 * @brief Relaxes the edge if a shorter path is found. Modified to work with walking time
 * 
 * @param edge Pointer to the edge to be relaxed.
 * @return true if the edge was relaxed, false otherwise.
 * 
 * O(1) time complexity, O(1) space complexity.
 */
bool walkingRelax(Edge<T>* edge);

template <class T>
/**
 * @brief Computes the shortest paths from a given origin vertex to all other vertices in the graph using Dijkstra's algorithm.
 * 
 * @param g Pointer to the graph on which the algorithm will be executed.
 * @param origin Pointer to the origin vertex from which the shortest paths will be calculated.
 * @param distance Decides between using Driving edges or Walking edges.
 * 
 * O((E + V) log |V|) time complexity, O(|V|) space complexity.
 * 
 * @note The graph should not contain negative weight edges, as Dijkstra's algorithm does not handle them correctly.
 */
void dijkstra(Graph<T>* g, Vertex<T>* origin, Distance distance);

template <class T>
/**
 * @brief Computes the shortest paths from a given origin vertex to all other vertices in the graph using Dijkstra's algorithm.
 * Along with following restrictions such as avoid Edges and Nodes. 
 * If a must vertex is provided, the algorithm will ensure that the path includes this vertex.
 * 
 * @param g Pointer to the graph on which the algorithm will be executed.
 * @param origin Pointer to the origin vertex from which the shortest paths will be calculated.
 * @param distance Decides between using Driving edges or Walking edges.
 *
 * O((E + V) log |V|) time complexity, O(|V|) space complexity.
 *
 * @note The graph should not contain negative weight edges, as Dijkstra's algorithm does not handle them correctly.
 */
void restrictedDrivingDijkstra(Graph<T>* g, Vertex<T>* origin, std::vector<Vertex<T>*> nAvoid, std::vector<Edge<T>*> eAvoid, Vertex<T>* must);

template <class T>
/**
 * @brief Returns the distance from origin to dest, along with the path taken, stored in res.
 * 
 * @param g Pointer to the graph on which the algorithm will be executed.
 * @param origin Pointer to the origin vertex.
 * @param dest Pointer to the destination vertex.
 * @param res A vector to store the vertices in the path from origin to dest.
 * @param rev A boolean indicating whether to reverse the path at the end.
 * @return The total distance of the path. Returns -1 if no valid path exists.
 * 
 * @warning The method assumes that the graph and vertices are properly initialized and valid.
 *          If any of the vertices are null or unreachable, the function returns -1.
 * 
 * O(|V|) where V is the ammount of vertices in the graph.
 * 
 */
static double getPath(Graph<T>* g, Vertex<T>* origin, Vertex<T>* dest, std::vector<T>& res, const bool& rev);

template <class T>
/**
 * @brief Returns the distance from origin to dest, along with the path taken, stored in res, this time following restrictions.
 * if Must is valid the path is guaranteed to pass through it. If no valid path exists, the function returns -1.
 *
 * @tparam T The type of the elements in the graph.
 * @param g Pointer to the graph object.
 * @param origin Pointer to the starting vertex.
 * @param dest Pointer to the destination vertex.
 * @param must Pointer to the vertex that the path must pass through (optional, can be nullptr).
 * @param res Reference to a vector where the resulting path will be stored.
 * @return The total distance of the path. Returns -1 if no valid path exists.
 *
 * @note If the "must-pass" vertex is not specified simply works as a normal getPath.
 * 
 * @warning The method assumes that the graph and vertices are properly initialized and valid.
 *          If any of the vertices are null or unreachable, the function returns -1.
 *
 * O(|V|) where V is the ammount of vertices in the graph.
 */
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
 *
 * @param nA A vector of pointers to the vertices that should be avoided.
 * @param nE A vector of pointers to the edges that should be avoided.
 * 
 * O(|E| + |V|) time complexity, O(1) space complexity the method itself does not alocate extra space.
 * where V is the amount of vertices and E the amount of edges in the vectors, which worst case are the same as the graph.
 */
static void prepareRestrictedGraph(std::vector<Vertex<T>*> nA, std::vector<Edge<T>*> nE);

#endif //SHORTESTPATHALGORITHMS_H
