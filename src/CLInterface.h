#ifndef CLMENU_H
#define CLMENU_H

#include <iostream>
#include <fstream>
#include <Graph.h>
#include "ParseFile.h"
#include "ShortestPathAlgorithms.h"

class CLInterface
{
public:

    /**
     * @brief Presents a user interface for selecting different planning modes.
     *
     * This method initializes a graph and parses location and distance data from the provided file paths.
     * If the file paths are empty, it defaults to parsing data from predefined data files. The user
     * is then presented with a menu to choose between three planning modes: Independent Planning, Restricted
     * Planning, and Eco-Friendly Planning.
     *
     * @param locations The file path to the locations data. If empty, default file is used.
     * @param distances The file path to the distances data. If empty, default file is used.
     * @param outFile The output stream where results will be written.
     *  If empty, defaults to standard console out(std::cout).
     *
     * @returns 0 upon success, non-zero otherwise.
     */
    int presentUI(const std::string& locations, const std::string& distances, std::ostream& outFile);


    /**
     * @brief Executes the default run of the program, parsing location, distance,
     *        and input files to populate a graph and process the input.
     *
     * @param locations Path to the locations file. If empty, a default file is used.
     * @param distances Path to the distances file. If empty, a default file is used.
     * @param inputFile Path to the input file. Used only if locations and distances are provided.
     * @param outputFile Path to the output file. Used only if locations and distances are provided.
     *
     * This method initializes a graph and uses a parser to read data from the specified
     * files. If any of the file paths are empty, it defaults to using
     * predefined file paths for small data and input/output files.
     */
    void defaultRun(const std::string& locations, const std::string& distances, const std::string& inputFile, const std::string& outputFile);


    /**
     * @brief Outputs the independent route planning results based on the given parameters..
     *
     * This method processes the query result and writes it to the specified output file.
     * It takes the query name, source and destination nodes, the graph, and the output file stream as input.
     *
     * @param sNode A pointer to the source node involved in the query.
     * @param dNode A pointer to the destination node involved in the query.
     * @param g A pointer to the graph object containing the nodes and edges.
     * @param outFile A reference to the output file stream where the result will be written.
     *
     * Dijkstra's shortest path algorithm dominates the time complexity of this method.
     * The overall time complexity is O((V + E) log V), where V is the number of vertices and E
     * is the number of edges in the graph.
     */
    void outPutIndependentResult(Vertex<int>* sNode, Vertex<int>* dNode, Graph<int>* g, std::ostream& outFile);

    /**
     * @brief Outputs the result of a restricted path query operation to a file or standard cout.
     *
     * This method calculates and outputs the best eco-friendly route from a source node
     * to a destination node and some restrictions like nodes and edges to avoid,
     * and a node that must be included.
     * It uses Dijkstra's algorithm to compute the shortest path.
     *
     * @param sNode A pointer to the source node involved in the query.
     * @param dNode A pointer to the destination node involved in the query.
     * @param nAvoid A vector of pointers to nodes that should be avoided in the path.
     * @param eAvoid A vector of pointers to edges that should be avoided in the path.
     * @param must A pointer to a node that must be included in the path.
     * @param g A pointer to the graph object containing the nodes and edges.
     * @param outFile A reference to the output file stream where the result will be written.
     *
     * Dijkstra's shortest path algorithm dominates the time complexity of this method.
     * The overall time complexity is O((V + E) log V), where V is the number of vertices and E
     * is the number of edges in the graph.
     */
    void outPutRestrictedResult(Vertex<int>* sNode, Vertex<int>* dNode, std::vector<Vertex<int>*>& nAvoid, std::vector<Edge<int>*>& eAvoid, Vertex<int>* must, Graph<int>* g, std::ostream& outFile);

    /**
     * @brief Outputs the eco-friendly route planning results based on the given parameters.
     *
     * This method calculates and outputs the best eco-friendly route from a source node
     * to a destination node, considering parking nodes, walking time, and driving time.
     * It uses Dijkstra's algorithm to compute the shortest paths.
     *
     * @param sNode Pointer to the source node.
     * @param dNode Pointer to the destination node.
     * @param nAvoid Vector of nodes to avoid during the route calculation.
     * @param eAvoid Vector of edges to avoid during the route calculation.
     * @param maxWalkTime Maximum allowed walking time in minutes.
     * @param aprox Boolean flag indicating whether to allow approximate routes if none exist in the given maxWalkTime.
     * @param g Pointer to the graph object representing the network.
     * @param outFile Output stream to write the results.
     *
     * Dijkstra's shortest path algorithm dominates the time complexity of this method.
     * The overall time complexity is O(V^2), where V is the number of vertices in the graph.
     */
    void outPutEcoResult(Vertex<int>* sNode, Vertex<int>* dNode, std::vector<Vertex<int>*>& nAvoid, std::vector<Edge<int>*>& eAvoid, const double& maxWalkTime, const bool& aprox, Graph<int>* g, std::ostream& outFile);


private:
    /* Methods Meant for use in the interactive Menu */

    /**
     *  Method to aid in writing the path to the output stream.
     *
     *  @param v The vector of node IDs representing the path.
     *  @param out The output stream to write the path to.
     */
    void outputPath(std::vector<int>& v, std::ostream& out);

    /**
     * @brief Handles the independent route planning functionality in the command-line interface.
     *
     * This method prompts the user to input a source and destination node, validates the input,
     * and computes the shortest route between the 2 without restrictions, and, if possible, a second completely disjoint
     * route as an alternative. The results can go to either a file or standard console out.
     * After execution, the user is returned to the main menu.
     *
     * @param g Reference to the graph that represents map.
     * @param outFile Place where the results will be writen, can be a file or just standard console out.
     * @param locations A string representing the file path for a formated .csv file containing Location/Node data.
     * @param distances A string representing the file path for a formated .csv file containing Distance/Edge data.
     */
    void independantRoute(Graph<int>* g, std::ostream& outFile, const std::string& locations, const std::string& distances);

    /**
     * @brief Handles the restricted route planning functionality in the command-line interface.
     *
     * This method allows the user to specify a source node, a destination node, nodes to avoid,
     * edges to avoid, and an optional node that must be included in the route. It then calculates
     * and outputs the shortest path between the source and destination nodes following all the restrictions.
     * The results can go to either a file or standard console out.
     * After execution, the user is returned to the main menu.
     *
     * @param g Reference to the graph that represents map.
     * @param outFile Place where the results will be writen, can be a file or just standard console out.
     * @param locations A string representing the file path for a formated .csv file containing Location/Node data.
     * @param distances A string representing the file path for a formated .csv file containing Distance/Edge data.
     */
    void restrictedRoute(Graph<int>* g, std::ostream& outFile, const std::string& locations, const std::string& distances);

    /**
     * @brief Handles the Eco-friendly route planning functionality in the command-line interface.
     *
     * This method allows the user to specify a source and destination node, nodes and edges to avoid,
     * a maximum walking time, and whether to compute an approximate path or not. The results are
     * output to the provided output stream. The results can go to either a file or standard console out.
     * After execution, the user is returned to the main menu.
     *
     * @param g Reference to the graph that represents map.
     * @param outFile Place where the results will be writen, can be a file or just standard console out.
     * @param locations A string representing the file path for a formated .csv file containing Location/Node data.
     * @param distances A string representing the file path for a formated .csv file containing Distance/Edge data.
     */
    void ecoFriendlyRoute(Graph<int>* g, std::ostream& outFile, const std::string& locations, const std::string& distances);
};

#endif //CLMENU_H
