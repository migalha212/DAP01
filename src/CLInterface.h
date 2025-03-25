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
     * @brief Prints the correct formating for running the program
     *
     * @brief if the user missuses when running it from the terminal this method is responsible for showing them how to do it
     */
    void printArgumentError();
    
    /**
     *  temp method meant to aid in writing for now
     */ 
    void presentPath(std::vector<int>& v);
private:
    /* Methods Meant for use in the interactive Menu */

    void independantRoute(int sID, int dID, Graph<int>* g);
    void restrictedRoute(int sID, int dID, Graph<int>* g);
    void ecoFriendlyRoute(int sID, int dID, Graph<int>* g);
};

#endif //CLMENU_H
