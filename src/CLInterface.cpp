#include "CLInterface.h"
#include "ShortestPathAlgorithms.cpp"
#include "ParseFile.h"
using namespace std;


void CLInterface::presentUI(const string& locations, const string& distances, ofstream& outFile) {
    Graph<int> g;
    Parsefile parser;
    if (locations.empty() || distances.empty()) {
        parser.parseLocation("../small_data/Locations.csv", &g);
        parser.parseDistance("../small_data/Distances.csv", &g);
    }
    else {
        parser.parseLocation(locations, &g);
        parser.parseDistance(distances, &g);
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
        if(choice == "q"){
            outFile.close(); 
            exit(0);}
        int choiceInt = parseInt(choice);
        while (choiceInt == -1 || (choiceInt > 3 || choiceInt < 1)) {
            cout << "Invalid choice, please try again." << endl;
            cin >> choice;
            choiceInt = parseInt(choice);
        }
        
        // TODO build logic for all 3 routes
        switch (choiceInt) {
        case 1:
            independantRoute(&g, outFile);
            break;
        case 2:
            restrictedRoute(&g, outFile);
            break;
        case 3:
            ecoFriendlyRoute(&g, outFile);
            break;
        default:
            return;
        }
        return;
    }
}

void CLInterface::independantRoute(Graph<int>* g, ofstream& outFile) {
    system("cls"); // clear screen
    cout << endl;
    cout << "Independent Route Planning" << endl;
    cout << "Please enter the source node: ";
    string source;
    cin >> source;
    cout << "Please enter the destination node: ";
    string destination;
    cin >> destination;
    
    
    if (!outFile.is_open()) {
        cout << "Error opening output file." << endl;
        return;
    }
    int sNode = stoi(source);
    int dNode = stoi(destination);
    if (sNode == -1 || dNode == -1) {
        cout << "Invalid node input." << endl;
        return;
    }
    Vertex<int>* sNodePtr = g->findVertex(sNode);
    Vertex<int>* dNodePtr = g->findVertex(dNode);
    if (sNodePtr == nullptr || dNodePtr == nullptr) {
        cout << "Invalid node input." << endl;
        return;
    }
    cout << endl;
    outPutIndependentResult(sNodePtr, dNodePtr, g, cout);
    
    cout << "Press any key to continue..." << endl;
    cin.ignore(); // clear the newline character from the input buffer
    cin.get(); // wait for user input
    system("cls"); // clear screen
    cout << endl;
    CLInterface::presentUI("", "", outFile); // return to the main menu
}

void CLInterface::restrictedRoute(Graph<int>* g, ofstream& outFile){
    system("cls");
    cout << endl;
    cout << "Restricted Route Planning" << endl;
    cout << "Please enter the source node: ";
    string source;
    cin >> source;
    cout << "Please enter the destination node: ";
    string destination;
    cin >> destination;
    cout << "Please enter how many nodes to avoid: ";
    string avoidNodes;
    cin >> avoidNodes;
    int numNodes = parseInt(avoidNodes);
    if(numNodes < 0){
        cout << "Invalid number of nodes to avoid." << endl;
        return;
    }
    vector<Vertex<int>*> nAvoid;
    for(int i = 0; i < numNodes; i++) {
        cout << "Please enter the node to avoid: ";
        string node;
        cin >> node;
        Vertex<int>* v = parseVertex(node, g);
        if (v == nullptr) {
            cout << "Invalid node input." << endl;
            return;
        }
        nAvoid.push_back(v);
    }
    cout << "Please enter how many edges to avoid: ";
    string avoidEdges;
    cin >> avoidEdges;
    int numEdges = parseInt(avoidEdges);
    if(numEdges < 0){
        cout << "Invalid number of edges to avoid." << endl;
        return;
    }
    vector<Edge<int>*> eAvoid;
    for(int i = 0; i < numEdges; i++) {
        cout << "Please enter the edge to avoid in the format v1,v2 : ";
        string edge;
        cin >> edge;
        Edge<int>* e = parseEdge(edge, g);
        if (e == nullptr) {
            cout << "Invalid edge input." << endl;
            return;
        }
        eAvoid.push_back(e);
    }
    cout << "Please enter the node that must be included (enter 0 if not desired): ";
    string mustNode;
    cin >> mustNode;
    if(mustNode != "0"){
        Vertex<int>* must = parseVertex(mustNode, g);
        if (must == nullptr) {
            cout << "Invalid node input." << endl;
            return;
        }
    }
    int sNode = stoi(source);
    int dNode = stoi(destination);
    if (sNode == -1 || dNode == -1) {
        cout << "Invalid node input." << endl;
        return;
    }
    Vertex<int>* sNodePtr = g->findVertex(sNode);
    Vertex<int>* dNodePtr = g->findVertex(dNode);
    if (sNodePtr == nullptr || dNodePtr == nullptr) {
        cout << "Invalid node input." << endl;
        return;
    }
    cout << endl;
    outPutRestrictedResult(sNodePtr, dNodePtr, nAvoid, eAvoid, must, g, cout);
    cout << "Press any key to continue..." << endl;
    cin.ignore(); // clear the newline character from the input buffer
    cin.get(); // wait for user input
    system("cls"); // clear screen
    cout << endl;
    CLInterface::presentUI("", "", outFile); // return to the main menu
}

void CLInterface::ecoFriendlyRoute(Graph<int>* g, ofstream& outFile){
    system("cls");
    cout << endl;
    cout << "Eco-Friendly Route Planning" << endl;
    cout << "Please enter the source node: ";
    string source;
    cin >> source;
    cout << "Please enter the destination node: ";
    string destination;
    cin >> destination;
    cout << "Please enter how many nodes to avoid: ";
    string avoidNodes;
    cin >> avoidNodes;
    int numNodes = parseInt(avoidNodes);
    if(numNodes < 0){
        cout << "Invalid number of nodes to avoid." << endl;
        return;
    }
    vector<Vertex<int>*> nAvoid;
    for(int i = 0; i < numNodes; i++) {
        cout << "Please enter the node to avoid: ";
        string node;
        cin >> node;
        Vertex<int>* v = parseVertex(node, g);
        if( v == nullptr) {
            cout << "Invalid node input." << endl;
            return;
        }
        nAvoid.push_back(v);
    }
    cout << "Please enter how many edges to avoid: ";
    string avoidEdges;
    cin >> avoidEdges;
    int numEdges = parseInt(avoidEdges);
    if(numEdges < 0){
        cout << "Invalid number of edges to avoid." << endl;
        return;
    }
    vector<Edge<int>*> eAvoid;
    for(int i = 0; i < numEdges; i++) {
        cout << "Please enter the edge to avoid in the format v1,v2 : ";
        string edge;
        cin >> edge;
        Edge<int>* e = parseEdge(edge, g);
        if (e == nullptr) {
            cout << "Invalid edge input." << endl;
            return;
        }
        eAvoid.push_back(e);
    }
    cout << "Please enter the maximum walking time: ";
    string maxWalkTimeStr;
    cin >> maxWalkTimeStr;
    double maxWalkTime = parseInt(maxWalkTimeStr);
    if(maxWalkTime < 0){
        cout << "Invalid maximum walking time." << endl;
        return;
    }
    cout << "Please enter if you want the approximate path (y/n): ";
    string aproxStr;
    cin >> aproxStr;
    bool aprox = false;
    if (aproxStr == "y" || aproxStr == "Y") {
        aprox = true;
    }
    else if (aproxStr == "n" || aproxStr == "N") {
        aprox = false;
    }
    else {
        cout << "Invalid input, defaulting to no approximate path." << endl;
        aprox = false;
    }
    
    int sNode = stoi(source);
    int dNode = stoi(destination);
    if (sNode == -1 || dNode == -1) {
        cout << "Invalid node input." << endl;
        return;
    }
    Vertex<int>* sNodePtr = g->findVertex(sNode);
    Vertex<int>* dNodePtr = g->findVertex(dNode);
    if (sNodePtr == nullptr || dNodePtr == nullptr) {
        cout << "Invalid node input." << endl;
        return;
    }

    cout << endl;
    outPutEcoResult(sNodePtr, dNodePtr, nAvoid, eAvoid, maxWalkTime, aprox, g, cout);
    cout << "Press any key to continue..." << endl;
    cin.ignore(); // clear the newline character from the input buffer
    cin.get(); // wait for user input
    system("cls"); // clear screen
    cout << endl;
    CLInterface::presentUI("", "", outFile); // return to the main menu
}

void CLInterface::defaultRun() {
    Parsefile parser;
    // Build Graph
    Graph<int> g;
    parser.parseLocation("../small_data/Locations.csv", &g);
    parser.parseDistance("../small_data/Distances.csv", &g);

    // Parser will parse and Output through another method
    parser.parseInput("../input.txt", "../output.txt", &g);
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
    if (dist != -1) {
        outputPath(v, outFile);
        outFile << '(' << dist << ')' << endl;
    }
    else {
        outFile << "none" << endl;
    }

    dijkstra(g, sNode, Distance::drive);
    dist = getPath(g, sNode, dNode, v, true);
    outFile << "AlternativeDrivingRoute:";
    if (dist != -1) {
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
    if (dist != -1) {
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
            if (dist != -1) {
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
    // Todo: complete the paths that meet the requirement and present the best
    for (auto& pNode : parkingNodes) {
        if (pNode.dist > maxWalkTime) continue;
        vector<int> drive;
        if (pNode.dist == INF) continue; // no path to parking node
        double dist = getPath(g, sNode, pNode.node, drive, true);
        if (dist == -1) continue;
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
