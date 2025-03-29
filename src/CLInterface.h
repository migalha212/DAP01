#ifndef CLMENU_H
#define CLMENU_H

#include <iostream>
#include <fstream>
#include <Graph.h>
#include "ParseFile.h"
#include "ShortestPathAlgorithms.h"

// ! Do note that method descriptions and names aren't final, only built as a demo for the stucture that might be best
class CLInterface
{
public:
    /**
     * Main method for presenting the command line interface to the user
     *
     * Responsible for calling other "Present" methods depending on user input
     */
    void presentUI(const std::string& locations, const std::string& distances, std::ofstream& outFile);


    /**
     * @brief Executes the default run sequence for the application.
     *
     * This function is responsible for initiating and managing the
     * standard execution flow of the program. It may include tasks
     * such as initializing resources, processing data, and handling
     * the main logic of the application.
     */
    void defaultRun();


    /**
     * @brief Outputs the result of an independent query operation to a file.
     *
     * This function processes the query result and writes it to the specified output file.
     * It takes the query name, source and destination nodes, the graph, and the output file stream as input.
     *
     * @param sNode A pointer to the source node involved in the query.
     * @param dNode A pointer to the destination node involved in the query.
     * @param g A pointer to the graph object containing the nodes and edges.
     * @param outFile A reference to the output file stream where the result will be written.
     */
    void outPutIndependentResult(Vertex<int>* sNode, Vertex<int>* dNode, Graph<int>* g, std::ostream& outFile);

    /**
     * @brief Outputs the result of a restricted query operation to a file.
     *
     * This function processes the query result and writes it to the specified output file.
     * It takes the query name, source and destination nodes, the graph, and the output file stream as input.
     *
     * @param sNode A pointer to the source node involved in the query.
     * @param dNode A pointer to the destination node involved in the query.
     * @param nAvoid A vector of pointers to nodes that should be avoided in the path.
     * @param eAvoid A vector of pointers to edges that should be avoided in the path.
     * @param must A pointer to a node that must be included in the path.
     * @param g A pointer to the graph object containing the nodes and edges.
     * @param outFile A reference to the output file stream where the result will be written.
     */
    void outPutRestrictedResult(Vertex<int>* sNode, Vertex<int>* dNode, std::vector<Vertex<int>*>& nAvoid, std::vector<Edge<int>*>& eAvoid, Vertex<int>* must, Graph<int>* g, std::ostream& outFile);

    void outPutEcoResult(Vertex<int>* sNode, Vertex<int>* dNode, std::vector<Vertex<int>*>& nAvoid, std::vector<Edge<int>*>& eAvoid, const double& maxWalkTime, const bool& aprox, Graph<int>* g, std::ostream& outFile);
    /**
     *  temp method meant to aid in writing for now
     */
    void outputPath(std::vector<int>& v, std::ostream& out);

private:
    /* Methods Meant for use in the interactive Menu */

    void independantRoute(Graph<int>* g, std::ofstream& outFile);
    void restrictedRoute(Graph<int>* g, std::ofstream& outFile);
    void ecoFriendlyRoute(Graph<int>* g, std::ofstream& outFile);
};

#endif //CLMENU_H
