#ifndef PARSE_FILE_H
#define PARSE_FILE_H

#include <fstream>
#include <sstream>
#include <string>
#include <Graph.h>

// ! Do note that method descriptions and names aren't final, only built as a demo for the stucture that might be best
class Parsefile
{
public:
    /**
     * Parse formated information from a csv file into Nodes to be used in a graph
     * @param filename file to parse
     */
    void parseLocation(std::string filename, Graph<int> *Graph);

    /**
     * Parse formated information from a csv file into Edges to be used in a graph
     * @param filename file to parse
     */
    void parseDistance(std::string filename, Graph<int> *Graph);
};
#endif //PARSE_FILE_H
