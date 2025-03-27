#ifndef PARSE_FILE_H
#define PARSE_FILE_H

#include <fstream>
#include <sstream>
#include <string>
#include <Graph.h>
#include <algorithm>
#include <vector>

// ! Do note that method descriptions and names aren't final, only built as a demo for the stucture that might be best
class Parsefile
{
public:

    /**
     * @brief Parses a file to extract location data and populates the given graph.
     * 
     * This function reads the specified file and extracts location information,
     * which is then used to populate the provided graph structure. The graph
     * is expected to use integers as its node identifiers.
     * 
     * @param filename The path to the file containing location data.
     * @param g A pointer to the graph object where the parsed data will be stored.
     *          The graph must be initialized before calling this function.
     * 
     * @return An integer indicating the success or failure of the operation.
     *         0 indicates success, while non-zero values indicate errors.
     */
    int parseLocation(std::string filename, Graph<int>* g);

    /**
     * @brief Parses a file to extract distance data and populates the given graph.
     * 
     * This function reads a file specified by the filename parameter, extracts
     * distance-related information, and uses it to populate the provided graph
     * object. The graph is expected to use integers as its node identifiers.
     * 
     * @param filename The path to the file containing the distance data.
     * @param g A pointer to the graph object to be populated with the parsed data.
     *          The graph should be of type Graph<int>.
     * @return An integer indicating the success or failure of the parsing operation.
     *         0 for success and a non-zero value for failure.
     */
    int parseDistance(std::string filename, Graph<int>* g);


    int parseInput(std::string inputFileName, std::string outputFileName, Graph<int>* g);

};
#endif //PARSE_FILE_H
