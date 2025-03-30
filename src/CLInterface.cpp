#include "CLInterface.h"
#include "ShortestPathAlgorithms.cpp"
#include "ParseFile.h"
using namespace std;


int CLInterface::presentUI(const string& locations, const string& distances, ostream& outFile) {
    Graph<int> g;
    Parsefile parser;
    if (locations.empty() || distances.empty()) {
        if(parser.parseLocation("../data_files/Locations.csv", &g)) return 1;
        if(parser.parseDistance("../data_files/Distances.csv", &g)) return 1;
    }
    else {
        if(parser.parseLocation(locations, &g)) return 1;
        if(parser.parseDistance(distances, &g)) return 1;
    }


    while (true) {

        system("cls"); // clears the terminal
        cout << endl;
        cout << "Choose Desired Mode:" << endl;
        cout << "1: Independent Planning" << endl;
        cout << "2: Restricted Planning" << endl;
        cout << "3: Eco-Friendly Planning" << endl;
        cout << "Press q to exit" << endl;
        string choice;
        cin >> choice;
        if (choice == "q") {
            //outFile.close(); 
            exit(0);
        }
        int choiceInt = parseInt(choice);
        while (choiceInt == -1 || (choiceInt > 3 || choiceInt < 1)) {
            cout << "Invalid choice, please try again." << endl;
            cin >> choice;
            choiceInt = parseInt(choice);
        }


        switch (choiceInt) {
        case 1:
            independantRoute(&g, outFile, locations, distances);
            break;
        case 2:
            restrictedRoute(&g, outFile, locations, distances);
            break;
        case 3:
            ecoFriendlyRoute(&g, outFile, locations, distances);
            break;
        default:
            return 1;
        }
        return 0;
    }
}

void CLInterface::independantRoute(Graph<int>* g, ostream& outFile, const std::string& locations, const std::string& distances) {
    system("cls"); // clear screen
    cout << endl;
    cout << "Independent Route Planning" << endl;

    Vertex<int>* sNodePtr = nullptr;
    Vertex<int>* dNodePtr = nullptr;
    string source, destination;

    do {
        cout << "Please enter the source node: ";
        cin >> source;
        sNodePtr = parseVertex(source, g);
        if (sNodePtr == nullptr) {
            cout << "Invalid source node input. Please try again." << endl;
        }
    } while (sNodePtr == nullptr);

    do {
        cout << "Please enter the destination node: ";
        cin >> destination;
        dNodePtr = parseVertex(destination, g);
        if (dNodePtr == nullptr) {
            cout << "Invalid destination node input. Please try again." << endl;
        }
    } while (dNodePtr == nullptr);

    cout << endl;
    outPutIndependentResult(sNodePtr, dNodePtr, g, outFile);

    cout << "Press any key to continue..." << endl;
    cin.ignore(); // clear the newline character from the input buffer
    cin.get(); // wait for user input
    system("cls"); // clear screen
    cout << endl;
    CLInterface::presentUI(locations, distances, outFile); // return to the main menu
}

void CLInterface::restrictedRoute(Graph<int>* g, ostream& outFile, const std::string& locations, const std::string& distances) {
    system("cls");
    cout << endl;
    cout << "Restricted Route Planning" << endl;

    string source, destination;
    Vertex<int>* sNodePtr = nullptr;
    Vertex<int>* dNodePtr = nullptr;

    do {
        cout << "Please enter the source node: ";
        cin >> source;
        sNodePtr = parseVertex(source, g);
        if (sNodePtr == nullptr) {
            cout << "Invalid source node input. Please try again." << endl;
        }
    } while (sNodePtr == nullptr);

    do {
        cout << "Please enter the destination node: ";
        cin >> destination;
        dNodePtr = parseVertex(destination, g);
        if (dNodePtr == nullptr) {
            cout << "Invalid destination node input. Please try again." << endl;
        }
    } while (dNodePtr == nullptr);

    string avoidNodes;
    int numNodes;
    do {
        cout << "Please enter how many nodes you wish to avoid: ";
        cin >> avoidNodes;
        numNodes = parseInt(avoidNodes);
        if (numNodes < 0) {
            cout << "Invalid number of nodes to avoid. Please try again." << endl;
        }
    } while (numNodes < 0);

    vector<Vertex<int>*> nAvoid;
    for (int i = 0; i < numNodes; i++) {
        string node;
        Vertex<int>* v = nullptr;
        do {
            cout << "Please enter the node to avoid: ";
            cin >> node;
            v = parseVertex(node, g);
            if (v == nullptr) {
                cout << "Invalid node input. Please try again." << endl;
            }
        } while (v == nullptr);
        nAvoid.push_back(v);
    }

    string avoidEdges;
    int numEdges;
    do {
        cout << "Please enter how many edges you wish to avoid: ";
        cin >> avoidEdges;
        numEdges = parseInt(avoidEdges);
        if (numEdges < 0) {
            cout << "Invalid number of edges to avoid. Please try again." << endl;
        }
    } while (numEdges < 0);

    vector<Edge<int>*> eAvoid;
    for (int i = 0; i < numEdges; i++) {
        string edge;
        Edge<int>* e = nullptr;
        do {
            cout << "Please enter the edges to avoid in the format v1,v2 one by one: ";
            cin >> edge;
            e = parseEdge(edge, g);
            if (e == nullptr) {
                cout << "Invalid edge input. Please try again." << endl;
            }
        } while (e == nullptr);
        eAvoid.push_back(e);
    }

    string mustNode;
    Vertex<int>* must = nullptr;
    do {
        cout << "Please enter the node that must be included (enter 0 if not desired): ";
        cin >> mustNode;
        if (mustNode != "0") {
            must = parseVertex(mustNode, g);
            if (must == nullptr) {
                cout << "Invalid node input. Please try again." << endl;
            }
        } else {
            break;
        }
    } while (must == nullptr);

    cout << endl;
    outPutRestrictedResult(sNodePtr, dNodePtr, nAvoid, eAvoid, must, g, outFile);
    cout << "Press any key to continue..." << endl;
    cin.ignore(); // clear the newline character from the input buffer
    cin.get(); // wait for user input
    system("cls"); // clear screen
    cout << endl;
    CLInterface::presentUI(locations, distances, outFile); // return to the main menu
}

void CLInterface::ecoFriendlyRoute(Graph<int>* g, ostream& outFile, const std::string& locations, const std::string& distances) {
    system("cls");
    cout << endl;
    cout << "Eco-Friendly Route Planning" << endl;

    string source, destination;
    Vertex<int>* sNodePtr = nullptr;
    Vertex<int>* dNodePtr = nullptr;

    do {
        cout << "Please enter the source node: ";
        cin >> source;
        sNodePtr = parseVertex(source, g);
        if (sNodePtr == nullptr) {
            cout << "Invalid source node input. Please try again." << endl;
        }
    } while (sNodePtr == nullptr);

    do {
        cout << "Please enter the destination node: ";
        cin >> destination;
        dNodePtr = parseVertex(destination, g);
        if (dNodePtr == nullptr) {
            cout << "Invalid destination node input. Please try again." << endl;
        }
    } while (dNodePtr == nullptr);

    string avoidNodes;
    int numNodes;
    do {
        cout << "Please enter how many nodes to avoid: ";
        cin >> avoidNodes;
        numNodes = parseInt(avoidNodes);
        if (numNodes < 0) {
            cout << "Invalid number of nodes to avoid. Please try again." << endl;
        }
    } while (numNodes < 0);

    vector<Vertex<int>*> nAvoid;
    for (int i = 0; i < numNodes; i++) {
        string node;
        Vertex<int>* v = nullptr;
        do {
            cout << "Please enter the node to avoid: ";
            cin >> node;
            v = parseVertex(node, g);
            if (v == nullptr) {
                cout << "Invalid node input. Please try again." << endl;
            }
        } while (v == nullptr);
        nAvoid.push_back(v);
    }

    string avoidEdges;
    int numEdges;
    do {
        cout << "Please enter how many edges to avoid: ";
        cin >> avoidEdges;
        numEdges = parseInt(avoidEdges);
        if (numEdges < 0) {
            cout << "Invalid number of edges to avoid. Please try again." << endl;
        }
    } while (numEdges < 0);

    vector<Edge<int>*> eAvoid;
    for (int i = 0; i < numEdges; i++) {
        string edge;
        Edge<int>* e = nullptr;
        do {
            cout << "Please enter the edge to avoid in the format v1,v2: ";
            cin >> edge;
            e = parseEdge(edge, g);
            if (e == nullptr) {
                cout << "Invalid edge input. Please try again." << endl;
            }
        } while (e == nullptr);
        eAvoid.push_back(e);
    }

    string maxWalkTimeStr;
    double maxWalkTime;
    do {
        cout << "Please enter the maximum walking time: ";
        cin >> maxWalkTimeStr;
        maxWalkTime = parseInt(maxWalkTimeStr);
        if (maxWalkTime < 0) {
            cout << "Invalid maximum walking time. Please try again." << endl;
        }
    } while (maxWalkTime < 0);

    string aproxStr;
    bool aprox = false;
    do {
        cout << "Please enter if you want the approximate path (y/n): ";
        cin >> aproxStr;
        if (aproxStr == "y" || aproxStr == "Y") {
            aprox = true;
        } else if (aproxStr == "n" || aproxStr == "N") {
            aprox = false;
        } else {
            cout << "Invalid input. Please enter 'y' or 'n'." << endl;
        }
    } while (aproxStr != "y" && aproxStr != "Y" && aproxStr != "n" && aproxStr != "N");

    cout << endl;
    outPutEcoResult(sNodePtr, dNodePtr, nAvoid, eAvoid, maxWalkTime, aprox, g, outFile);
    cout << "Press any key to continue..." << endl;
    cin.ignore(); // clear the newline character from the input buffer
    cin.get(); // wait for user input
    system("cls"); // clear screen
    cout << endl;
    CLInterface::presentUI(locations, distances, outFile); // return to the main menu
}

void CLInterface::defaultRun(const std::string& locations, const std::string& distances, const std::string& inputFile, const std::string& outputFile) {
    Graph<int> g;
    Parsefile parser;
    if (locations.empty() || distances.empty()) {
        parser.parseLocation("../data_files/Locations.csv", &g);
        parser.parseDistance("../data_files/Distances.csv", &g);
        parser.parseInput("../input.txt", "../output.txt", &g);
    }
    else {
        parser.parseLocation(locations, &g);
        parser.parseDistance(distances, &g);
        parser.parseInput(inputFile, outputFile, &g);
    }
}

void CLInterface::outPutIndependentResult(Vertex<int>* sNode, Vertex<int>* dNode, Graph<int>* g, ostream& outFile) {

    outFile << "Source:" << sNode->getInfo() << endl;
    outFile << "Destination:" << dNode->getInfo() << endl;

    //* A first drivingDijsktra's is called for the first shortest path
    resetGraph(g);
    dijkstra(g, sNode, Distance::drive);

    vector<int> v;
    double dist = getPath(g, sNode, dNode, v, true);
    outFile << "BestDrivingRoute:";
    if (dist > 0) {
        outputPath(v, outFile);
        outFile << '(' << dist << ')' << endl;
    }
    else {
        outFile << "none" << endl;
    }

    dijkstra(g, sNode, Distance::drive);
    dist = getPath(g, sNode, dNode, v, true);
    outFile << "AlternativeDrivingRoute:";
    if (dist > 0) {
        outputPath(v, outFile);
        outFile << '(' << dist << ')' << endl;
    }
    else {
        outFile << "none" << endl;
    }

    outFile << endl;
}

void CLInterface::outPutRestrictedResult(Vertex<int>* sNode, Vertex<int>* dNode, vector<Vertex<int>*>& nAvoid, vector<Edge<int>*>& eAvoid, Vertex<int>* must, Graph<int>* g, ostream& outFile) {

    outFile << "Source:" << sNode->getInfo() << endl;
    outFile << "Destination:" << dNode->getInfo() << endl;

    //* A first drivingDijsktra's is called for the first shortest path
    resetGraph(g);
    restrictedDrivingDijkstra(g, sNode, nAvoid, eAvoid, must);

    vector<int> v;
    double dist = getRestrictedPath(g, sNode, dNode, must, v);
    outFile << "RestrictedDrivingRoute:";
    if (dist > 0) {
        outputPath(v, outFile);
        outFile << '(' << dist << ')' << endl;
    }
    else {
        outFile << "none" << endl;
    }

    outFile << endl;
}

struct parkingNode
{
    Vertex<int>* node;
    double dist;
    vector<int> path;
};
bool parkingSort(const parkingNode& a, const parkingNode& b) {
    if (a.node->getDist() + a.dist < b.node->getDist() + b.dist) return true;
    else if (a.node->getDist() + a.dist == b.node->getDist() + b.dist) return a.dist > b.dist;
    return false;
}

void CLInterface::outPutEcoResult(Vertex<int>* sNode, Vertex<int>* dNode, vector<Vertex<int>*>& nAvoid, vector<Edge<int>*>& eAvoid, const double& maxWalkTime, const bool& aprox, Graph<int>* g, ostream& outFile) {

    outFile << "Source:" << sNode->getInfo() << endl;
    outFile << "Destination:" << dNode->getInfo() << endl;

    //* First the graph is reset and then set up for the eco-friendly route
    resetGraph(g);
    prepareRestrictedGraph(nAvoid, eAvoid);

    //* First dijkstra's from the destination node to each of the parking nodes
    dijkstra(g, dNode, Distance::walk);
    vector<parkingNode> parkingNodes;
    for (auto v : g->getVertexSet()) {
        if (v->getParking() == 1) {
            parkingNode pNode;
            pNode.node = v;
            pNode.dist = v->getDist();
            double dist = getPath(g, dNode, v, pNode.path, false);
            if (dist > 0) {
                parkingNodes.push_back(pNode);
            }
        }
    }


    resetGraph(g);
    prepareRestrictedGraph(nAvoid, eAvoid);
    //* Then dijkstra's from the source node to each of the parking nodes
    dijkstra(g, sNode, Distance::drive);
    //* After this one happens: dist holds the walkTime, pNode.node.getDist() holds the drive time
    //* The Nodes should be sorted using this info
    sort(parkingNodes.begin(), parkingNodes.end(), parkingSort);
    for (auto& pNode : parkingNodes) {
        if (pNode.dist > maxWalkTime) continue;
        vector<int> drive;
        if (pNode.dist == INF) continue; // no path to parking node
        double dist = getPath(g, sNode, pNode.node, drive, true);
        if (dist <= 0) continue;
        outFile << "DrivingRoute:";
        outputPath(drive, outFile);
        outFile << '(' << pNode.node->getDist() << ')' << endl;

        outFile << "ParkingNode:" << pNode.node->getInfo() << endl;
        outFile << "WalkingRoute:";
        outputPath(pNode.path, outFile);
        outFile << '(' << pNode.dist << ')' << endl;
        outFile << "TotalTime:" << pNode.dist + pNode.node->getDist() << endl;
        drive.clear();
        return;
    }
    if (!aprox) {
        //* if method gets to this point it means no paths were printed so we can check if the user wants the aproximate path
        outFile << "DrivingRoute:" << endl;
        outFile << "ParkingNode:" << endl;
        outFile << "TotalTime:" << endl;
        outFile << "Message: no possible route with max. walking time of " << maxWalkTime << " minutes." << endl;
        return;
    }
    else {
        int i = 0;
        for (auto& pNode : parkingNodes) {
            i++;
            vector<int> drive;
            if (pNode.dist == INF) continue; // no path to parking node
            double dist = getPath(g, sNode, pNode.node, drive, true);
            if (dist == -1) continue;

            outFile << "DrivingRoute" << i << ":";
            outputPath(drive, outFile);
            outFile << '(' << pNode.node->getDist() << ')' << endl;
            outFile << "ParkingNode" << i << ":" << pNode.node->getInfo() << endl;
            outFile << "WalkingRoute" << i << ":";
            outputPath(pNode.path, outFile);
            outFile << '(' << pNode.dist << ')' << endl;
            outFile << "TotalTime" << i << ":" << pNode.dist + pNode.node->getDist() << endl;
            drive.clear();
            if (i == 2) break;
        }
        while (i < 2) {
            i++;
            outFile << "DrivingRoute" << i << ":" << endl;
            outFile << "ParkingNode" << i << ":" << endl;
            outFile << "WalkingRoute" << i << ":" << endl;
            outFile << "TotalTime" << i << ":" << endl;
        }

        outFile << endl;

        return;
    }
}

void CLInterface::outputPath(vector<int>& v, ostream& out) {
    if (v.empty()) return;
    for (int i = 0; i < v.size() - 1; i++) {
        out << v[i] << ',';
    }
    out << v[v.size() - 1];
}
