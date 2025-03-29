#include "ParseFile.h"
#include "CLInterface.h"
using namespace std;

vector<Vertex<int>*> nAvoid = {};
vector<Edge<int>*> eAvoid = {};
Vertex<int>* must;

/* Auxiliary Methods*/
bool parseArgument(string& line, string& argument, string& value);
bool parseAvoidVertex(string& value, Graph<int>* g, vector<Vertex<int>*>& nAvoid);
bool parseAvoidEdge(string& value, Graph<int>* g, vector<Edge<int>*>& eAvoid);
/* Error Methods */
void printParseError(ofstream& out, string& value, const string& actual);
void printLineError(ofstream& out, string line);

int Parsefile::parseLocation(std::string& filename, Graph<int>* graph) {
    fstream file(filename);
    string line;
    getline(file, line); // first line is ignored, header

    if (!file.is_open()) {
        cerr << "Error occurred when opening Locations file" << endl;
        return 1;
    }
    while (getline(file, line)) {
        istringstream iss(line);
        string name, id, code, parking;
        getline(iss, name, ',');
        getline(iss, id, ',');
        getline(iss, code, ',');
        getline(iss, parking, '\r');
        graph->addVertex(name, stoi(id), code, stoi(parking));
    }
    file.close();
    return 0;
}

int Parsefile::parseDistance(std::string& filename, Graph<int>* graph) {
    fstream file(filename);
    string line;
    getline(file, line); // first line is ignored, header

    if (!file.is_open()) {
        cerr << "Error occurred when opening Distances file" << endl;
        return 1;
    }
    while (getline(file, line)) {
        istringstream iss(line);
        string code1, code2, walkTime, driveTime;
        getline(iss, code1, ',');
        getline(iss, code2, ',');
        getline(iss, driveTime, ',');
        getline(iss, walkTime, '\r');
        double dt;
        if (driveTime == "X") dt = INF;
        else dt = stod(driveTime);
        graph->addBidirectionalEdge(code1, code2, stod(walkTime), dt);
    }
    file.close();
    return 0;
}

Vertex<int>* parseVertex(string& value, Graph<int>* g) {
    try {
        int id = stoi(value);
        return g->findVertex(id);
    }
    catch (invalid_argument) {
        return g->findVertex(value);
    }
}

bool parseArgument(string& line, string& argument, string& value) {
    if (count(line.begin(), line.end(), ':') != 1) return false;
    stringstream ss(line);
    getline(ss, argument, ':');
    getline(ss, value);
    return true;
}

void printLineError(ofstream& out, string line) {
    out << "Invalid line" << endl << "-> " << line << endl << "Was empty" << endl;
    out << endl;
}

void printParseError(ofstream& out, string& value, const string& actual) {
    out << "Invalid Argument/Value" << endl << "Was: " << value << endl << "Should be: " << actual << endl;
}

bool parseAvoidVertex(string& value, Graph<int>* g, vector<Vertex<int>*>& nAvoid) {
    istringstream ss(value);
    string id;
    Vertex<int>* v;
    while (getline(ss, id, ',')) {
        v = parseVertex(id, g);
        if (v == nullptr) return false;
        nAvoid.push_back(v);
    }
    return true;
}

bool parseAvoidEdge(string& value, Graph<int>* g, vector<Edge<int>*>& eAvoid) {
    istringstream ss(value);
    string id1, id2, fodder;
    Vertex<int>* v1, * v2;
    Edge<int>* e;
    while (getline(ss, fodder, '(')) {
        e = nullptr;
        getline(ss, id1, ',');
        getline(ss, id2, ')');
        v1 = parseVertex(id1, g);
        v2 = parseVertex(id2, g);
        if (v1 == nullptr || v2 == nullptr) return false;
        for (Edge<int>* s : v1->getAdj()) {
            if (s->getDest() == v2) {
                e = s;
                break;
            }
        }
        if (e == nullptr) {
            return false;
        }
        eAvoid.push_back(e);
    }
    return true;
}

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
 * 
 * @note The function assumes that the input file is well-formed and adheres to the specified format.
 *       Any deviation from the format will result in error messages being written to the output file.
 */
int Parsefile::parseInput(std::string& inputFileName, std::string& outputFileName, Graph<int>* g) {
    fstream input(inputFileName);
    ofstream output(outputFileName);
    string line;
    string argument, value;
    CLInterface interface;
    if (!input.is_open()) {
        cerr << "Error occurred when opening Input file" << endl;
        return 1;
    }

    bool err = false;

    while (getline(input, line)) {
        //* Ignore all empty lines between tests, reset state of error from previous test if needed
        if (line.empty()) {
            err = false;
            nAvoid.clear();
            eAvoid.clear();
            must = nullptr;
            output << endl;
            continue;
        }

        //* First look for Query name, queries should begin with a # and are marked as finished by an empty line
        if (!err) {
            if (line[0] == '#') {
                output << line << endl;
            }
            else {
                err = true;
                output << "Unexpected Input in begining or end of Query" << endl
                    << "All queries should begin with '#' followed by the test name" << endl;
                continue;
            }
        }
        //* if a mistake has occurred it should keep going until it finds an empty line
        else if (err) continue;

        //! Start argument search, all arguments should be composed of a string with exactly 1 ':' and can be split by it
        //* Look for Mode, first half of string should be exactly "Mode", second half should be either driving or driving-walking
        Mode mode;
        {
            getline(input, line);
            if (!parseArgument(line, argument, value)) {
                err = true;
                printLineError(output, line);
                continue;
            }
            else {
                if (argument != "Mode") {
                    err = true;
                    printParseError(output, argument, "Mode:<driving>/<driving-walking>");
                    continue;
                }
                if (value == "driving") mode = Mode::driving;
                else if (value == "driving-walking") mode = Mode::drivingwalking;
                else {
                    err = true;
                    printParseError(output, value, "Mode:<driving>/<driving-walking>");
                    continue;
                }
            }
        }

        //* Look for Source, first half of string should be exactly "Source", seconde half should be either a valid id or a valid code
        Vertex<int>* source;
        {
            getline(input, line);
            if (!parseArgument(line, argument, value)) {
                printLineError(output, line);
                continue;
            }
            else {
                if (argument != "Source") {
                    err = true;
                    printParseError(output, argument, "Source:<id>/<code>");
                    continue;
                }
                source = parseVertex(value, g);
                if (source == nullptr) {
                    err = true;
                    printParseError(output, value, "Invalid Id/Code");
                    continue;
                }
            }
        }

        //* Look for Destination, first half of string should be exactly "Source", seconde half should be either a valid id or a valid code
        Vertex<int>* destination;
        {
            getline(input, line);
            if (!parseArgument(line, argument, value)) {
                printLineError(output, line);
                continue;
            }
            else {
                if (argument != "Destination") {
                    err = true;
                    printParseError(output, argument, "Destination:<id>/<code>");
                    continue;
                }
                destination = parseVertex(value, g);
                if (destination == nullptr) {
                    err = true;
                    printParseError(output, value, "Invalid Id/Code");
                    continue;
                }
            }
        }

        //* Checking if the next line is empty to know if we can end our query here or not
        {
            getline(input, line);
            if (line.empty()) {
                //* upon finding an emptyline with the driving mode we can end the query here
                if (mode == Mode::driving) {
                    interface.outPutIndependentResult(source, destination, g, output);
                    continue;
                }
                //* if not then there is an error, because the formating for the mode was not completed
                else {
                    output << "Unexpected Empty line found, Missing multiple Arguments" << endl;
                    output << endl;
                    continue;
                }
            }
        }

        //* The line was already read last time, so we can proceed without reading more
        //* The argument "max walking distance" will only show up in the case of Driving-Walking
        double maxWalkingTime = INF;
        if (mode == Mode::drivingwalking) {
            if (!parseArgument(line, argument, value)) {
                printLineError(output, line);
                continue;
            }
            if (argument != "MaxWalkTime") {
                err = true;
                printParseError(output, argument, "MaxWalkTime:<int>");
                continue;
            }
            try {
                maxWalkingTime = stoi(value);
            }
            catch (invalid_argument) {
                err = true;
                printParseError(output, argument, "MaxWalkTime:<int>");
                continue;
            }
            getline(input, line);
        }

        //! from this point onward no line can be empty until all arguments/restrictions have been satisfied
        //* Look for nodes to avoid, first half of string should be exactly AvoidNodes

        {
            if (!parseArgument(line, argument, value)) {
                printLineError(output, line);
                continue;
            }
            if (argument != "AvoidNodes") {
                err = true;
                printParseError(output, argument, "AvoidNodes:<id>/<code,<id>/<code>,...");
                continue;
            }
            if (!parseAvoidVertex(value, g, nAvoid)) {
                err = true;
                output << "Avoid Nodes had one or more invalid <id>/>code>" << endl;
                continue;
            }
        }

        //* Look for edges to avoid, first half of string should be exactly AvoidSegments

        {
            getline(input, line);
            if (!parseArgument(line, argument, value)) {
                printLineError(output, line);
                continue;
            }
            if (argument != "AvoidSegments") {
                err = true;
                printParseError(output, argument, "AvoidSegments:(<id>/<code,<id>/<code>),...");
                continue;
            }
            if (!parseAvoidEdge(value, g, eAvoid)) {
                err = true;
                output << "Avoid Segments had one or more invalid <id>/>code>" << endl;
                continue;
            }
        }

        //* Look for Node include, first half of string should be exactly IncludeNode

        if (mode == Mode::driving) {
            getline(input, line);
            if (!parseArgument(line, argument, value)) {
                printLineError(output, line);
                continue;
            }
            else {
                if (argument != "IncludeNode") {
                    err = true;
                    printParseError(output, argument, "IncludeNode:<id>/<code>");
                    continue;
                }
                if (!value.empty()) {
                    must = parseVertex(value, g);
                    if (must == nullptr) {
                        err = true;
                        printParseError(output, value, "Invalid Id/Code");
                        continue;
                    }
                }
            }
        }

        if (err) continue;
        //* Final Step is to call the according algorithm
        switch (mode) {
        case Mode::driving:
            interface.outPutRestrictedResult(source, destination, nAvoid, eAvoid, must, g, output);
            break;

        case Mode::drivingwalking:

            getline(input, line);
            bool aproximate = false;
            if (!line.empty())
                if (line != "Aproximate") {
                    err = true;
                    printParseError(output, line, "Aproximate");
                    continue;
                }
                else
                    aproximate = true;
            interface.outPutEcoResult(source, destination, nAvoid, eAvoid, maxWalkingTime, aproximate, g, output);
            if(line.empty()) output << endl;
            break;
        }
    }

    output.close();
    input.close();
    return 0;
}