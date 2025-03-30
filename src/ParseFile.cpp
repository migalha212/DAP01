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

int Parsefile::parseLocation(const string& filename, Graph<int>* graph) {
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
        int idInt = parseInt(id);
        if (idInt == -1) {
            cerr << "Invalid id: " << id << endl;
            return 1;
        }
        int parkingInt = parseInt(parking);
        if (parkingInt == -1) {
            cerr << "Invalid parking: " << parking << endl;
            return 1;
        }
        graph->addVertex(name, idInt, code, parkingInt);
    }
    file.close();
    return 0;
}

int Parsefile::parseDistance(const string& filename, Graph<int>* graph) {
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
        else dt = parseInt(driveTime);
        if (dt == -1) {
            cerr << "Invalid drive time: " << driveTime << endl;
            return 1;
        }
        double walkTimeInt = parseInt(walkTime);
        if (walkTimeInt == -1) {
            cerr << "Invalid walk time: " << walkTime << endl;
            return 1;
        }
        graph->addBidirectionalEdge(code1, code2, walkTimeInt, dt);
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

Edge<int>* parseEdge(string& value, Graph<int>* g) {
    istringstream ss(value);
    string id1, id2;
    Vertex<int>* v1, * v2;
    Edge<int>* e = nullptr;
    getline(ss, id1, ',');
    getline(ss, id2);
    v1 = parseVertex(id1, g);
    v2 = parseVertex(id2, g);
    if (v1 == nullptr || v2 == nullptr) return nullptr;
    for (Edge<int>* s : v1->getAdj()) {
        if (s->getDest() == v2) {
            e = s;
            break;
        }
    }
    return e;
}

int parseInt(string& value) {
    try {
        return stoi(value);
    }
    catch (invalid_argument) {
        return -1;
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
    if(value.back() != ')' && !value.empty()) return false; // remove trailing comma if present
    istringstream ss(value);
    string id1, id2;
    char fodder;
    Vertex<int>* v1, * v2;
    Edge<int>* e;
    while (ss >> fodder) {
        if (fodder != '(') return false;
        getline(ss, id1, ',');
        getline(ss, id2, ')');
        
        e = nullptr;

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
        if (ss.peek() == ',') ss.ignore();
        else if(ss.peek() == EOF) break;
        else return false;
    }
    return true;
}

int Parsefile::parseInput(const string& inputFileName, const string& outputFileName, Graph<int>* g) {
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

        //* if a mistake has occurred it should keep going until it finds an empty line
        if (err) continue;

        //* First look for Query name, queries should begin with a # and are marked as finished by an empty line
        
        if (line[0] == '#') {
            output << line << endl;
            //getline(input, line);
        }
        else {
            err = true;
            output << "Unexpected Input in begining or end of Query" << endl
            << "All queries should begin with '#' followed by the test name" << endl;
            continue;
            }

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
                    interface.outputIndependentResult(source, destination, g, output);
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
                output << "Avoid Nodes had one or more invalid <id>/>code> or invalid syntax" << endl;
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
            interface.outputRestrictedResult(source, destination, nAvoid, eAvoid, must, g, output);
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
            interface.outputEcoResult(source, destination, nAvoid, eAvoid, maxWalkingTime, aproximate, g, output);
            if (line.empty()) output << endl;
            break;
        }
    }

    output.close();
    input.close();
    return 0;
}