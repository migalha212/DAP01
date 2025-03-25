#ifndef CLMENU_H
#define CLMENU_H

#include <iostream>
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
    void presentUI();

    /**
     *
     */
    void presentInteractiveMenu();

    /**
     * Triggers the parsing of default Input.txt, Locations.csv and Distances.csv
     * Executes every query in Input.txt and outputs each of them to Output.txt in order
     */
    void defaultRun();

    void outPutIndependentResult(std::string& queryName, Vertex<int>* sNode, Vertex<int>* dNode, Graph<int>* g, std::ofstream& outFile);

    /**
     *  temp method meant to aid in writing for now
     */
    void outputPath(std::vector<int>& v, std::ofstream& out);

private:
    /* Methods Meant for use in the interactive Menu */

    void independantRoute(int sID, int dID, Graph<int>* g);
    void restrictedRoute(int sID, int dID, Graph<int>* g);
    void ecoFriendlyRoute(int sID, int dID, Graph<int>* g);
};

#endif //CLMENU_H
