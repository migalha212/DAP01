#include "ParseFile.h"
#include "CLInterface.h"
using namespace std;


int Parsefile::parseLocation(std::string filename, Graph<int>* graph) {
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

int Parsefile::parseDistance(std::string filename, Graph<int>* graph) {
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


enum Mode
{
    driving,
    drivingwalking,
};

bool parseArgument(string& line, string& argument, string& value) {
    if (count(line.begin(), line.end(), ':') != 1) return false;
    stringstream ss(line);
    getline(ss, argument, ':');
    getline(ss, value);
    return true;
}

void printLineError(ofstream& out, string line) {
    out << "Invalid line" << endl << "-> " << line << endl << "Was empty" << endl;
}

void printParseError(ofstream& out, string& value, const string& actual) {
    out << "Invalid Argument/Value" << endl << "Was: " << value << endl << "Should be: " << actual << endl;
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

int Parsefile::parseInput(std::string inputFileName, std::string outputFileName, Graph<int>* g) {
    fstream input(inputFileName);
    ofstream output(outputFileName);
    string line;
    string argument, value;
    CLInterface interface;
    if (!input.is_open()) {
        cerr << "Error occurred when opening Input file" << endl;
        return 1;
    }

    bool err = false, inQuery = false;
    vector<pair<int, int>> eIgnore = {};

    while (getline(input, line)) {
        //* Ignore all empty lines between tests, reset state of error from previous test if needed
        if (line.empty()) {
            err = false;
            inQuery = false;
            continue;
        }

        //* First look for Query name, queries should begin with a # and are marked as finished by an empty line
        string queryName;
        if (!inQuery && !err) {
            if (line[0] == '#') {
                queryName = line;
            }
            else {
                err = true;
                output << "Unexpected Input in begining of Query" << endl
                    << "All queries should begin with '#' followed by the test name" << endl;
                continue;
            }
        }
        //* if a mistake has occurred it should keep going until it finds an empty line
        else if (err) continue;

        //! Start argument search, all arguments should be composed of a string with exactly 1 ':' and can be split by it
        //* Look for mode, first half of string should be exactly "Mode", second half should be either driving or driving-walking
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
                    printParseError(output, value, "Mode:<driving>/<driving - walking>");
                    continue;
                }
            }
        }

        //* Look for source, first half of string should be exactly "Source", seconde half should be either a valid id or a valid code
        Vertex<int>* source;
        {
            getline(input, line);
            if (!parseArgument(line, argument, value)) {
                err = true;
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
                err = true;
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
                    inQuery = false;
                    interface.outPutIndependentResult(queryName,source,destination,g,output);
                }
                //* if not then there is an error, because the formating for the mode was not completed
                else {
                    err = true;
                    output << "Unexpected Empty line found, Missing multiple Arguments" << endl;
                    continue;
                }
            }
        }
        //* The line was already read last time, so we can proceed without reading more
        //* The argument "max walking distance" will only show up in the case of Drive-Walk
        vector<int> nIgnore = {};
        if (mode == Mode::drivingwalking) {
            //TODO
            continue;
        }
    }

    output.close();
    input.close();
    return 0;
}