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

    void simpleDist();
};

#endif //CLMENU_H
