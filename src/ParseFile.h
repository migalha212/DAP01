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
    enum Mode
    {
        driving,
        drivingwalking,
    };
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
    int parseLocation(const std::string& filename, Graph<int>* g);

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
    int parseDistance(const std::string& filename, Graph<int>* g);

    /**
     * @brief Parses input from a file to execute queries on a graph and writes the results to an output file.
     *
     * This function reads a structured input file containing queries and their parameters, processes the queries,
     * and writes the results to an output file. It supports two modes of operation: "driving" and "driving-walking".
     *
     * @param inputFileName The name of the input file containing the queries.
     * @param outputFileName The name of the output file where results will be written.
     * @param g A pointer to the graph object on which the queries will be executed.
     * @return int Returns 0 on successful execution, or 1 if an error occurs while opening the input file.
     *
     * @details
     * The input file should follow a specific format:
     * - Each query starts with a line beginning with `#` followed by the query name.
     * - Queries are separated by empty lines.
     * - Each query contains the following parameters:
     *   - `Mode:<driving>/<driving-walking>`: Specifies the mode of operation.
     *   - `Source:<id>/<code>`: Specifies the source vertex.
     *   - `Destination:<id>/<code>`: Specifies the destination vertex.
     *   - For "driving-walking" mode, an additional parameter:
     *     - `MaxWalkTime:<int>`: Specifies the maximum walking time.
     *   - `AvoidNodes:<id>/<code>,...`: Specifies nodes to avoid.
     *   - `AvoidSegments:(<id>/<code>,<id>/<code>),...`: Specifies edges to avoid.
     *   - For "driving" mode, an additional parameter:
     *     - `IncludeNode:<id>/<code>`: Specifies a node that must be included in the path.
     *   - For "driving-walking" mode, an optional parameter:
     *     - `Aproximate`: Indicates whether to use approximate results.
     *
     * The function validates the input format and parameters. If an error occurs during parsing, it writes an
     * appropriate error message to the output file and skips to the next query.
     *
     * The function supports the following operations:
     * - For "driving" mode:
     *   - Outputs results for restricted paths considering avoid nodes, avoid edges, and must-include nodes.
     * - For "driving-walking" mode:
     *   - Outputs results for eco-friendly paths considering avoid nodes, avoid edges, maximum walking time,
     *     and optional approximation.
     */
    int parseInput(const std::string& inputFileName, const std::string& outputFileName, Graph<int>* g);

};
/* Auxiliary Methods */

    /**
     * @brief Parses a string value to retrieve a vertex in the graph.
     *
     * This function takes a string representation of a vertex id or code, searches for
     * the corresponding vertex in the provided graph, and retrieves the
     * vertex if it exists. If the vertex does not exist, nullpointer is returned.
     *
     * @param value A reference to the string containing the vertex id or code to parse.
     * @param g A pointer to the graph where the vertex will be searched.
     * @return A pointer to the vertex corresponding to the parsed value or nullpointer if nonexistant.
    */
Vertex<int>* parseVertex(std::string& value, Graph<int>* g);
    
        /**
        * @brief Parses a string value to retrieve an edge from the graph.
        *
        * This function takes a string representation of 2 vertex ids or codes separated by a comma(','), searches for
        * the corresponding vertexs in the provided graph, and retrieves the
        * edge if it exists. If the edge does not exist, nullpointer is returned.
        *
        * @param value A reference to the string containing 2 vertex ids or codes separated by a comma(',') to parse.
        * @param g A pointer to the graph where the edge will be searched.
        * @return A pointer to the edge corresponding to the parsed values or nullpointer if nonexistant.
        */
Edge<int>* parseEdge(std::string& value, Graph<int>* g);

#endif //PARSE_FILE_H
