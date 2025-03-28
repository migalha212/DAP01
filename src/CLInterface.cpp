#include "CLInterface.h"
#include "ShortestPathAlgorithms.cpp"
using namespace std;

void CLInterface::presentUI() {
    Graph<int> g;
    Parsefile parser;
    parser.parseLocation("../small_data/Locations.csv", &g);
    parser.parseDistance("../small_data/Distances.csv", &g);
    while (true) {
        system("cls"); // clears the terminal
        cout << endl;
        cout << "Choose Desired Mode:" << endl;
        cout << "1: Independent Planning" << endl;
        cout << "2: Restricted Planning" << endl; //* this functionality is never metioned in the guide, not a priority
        cout << "3: Eco-Friendly Planning" << endl;
        int choice;
        cin >> choice;
        while (choice < 1 || choice > 3) {
            cout << "Choose a valid option" << endl;
            cin >> choice;
        }

        int sID, dID; // Source ID and Destination ID
        cout << endl << "Input the Starting Location ID followed by Destination ID" << endl;
        cin >> sID >> dID;

        switch (choice) {
        case 1:
            independantRoute(sID, dID, &g);
            break;
        case 2:
            //restrictedRoute(sID, dID, &g);
            break;
        case 3:
            //ecoFriendlyRoute(sID, dID, &g);
            break;
        default:
            return;
        }
        cin >> choice; // only here so the program doesn't immediatly close
        return;
    }
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

void CLInterface::outPutIndependentResult(std::string& queryName, Vertex<int>* sNode, Vertex<int>* dNode, Graph<int>* g, ofstream& outFile) {
    outFile << queryName << endl;

    outFile << "Source:" << sNode->getInfo() << endl;
    outFile << "Destination:" << dNode->getInfo() << endl;

    //* A first drivingDijsktra's is called for the first shortest path
    resetGraph(g);
    drivingDijkstra(g, sNode);

    vector<int> v;
    double dist = getPath(g,sNode,dNode,v);
    outFile << "BestDrivingRoute:";
    if(dist != -1){
        outputPath(v, outFile);
        outFile << '(' << dist << ')' << endl;
    }
    else{
        outFile << "none" << endl;
    }

    drivingDijkstra(g, sNode);
    dist = getPath(g, sNode, dNode, v);
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

void CLInterface::outPutRestrictedResult(std::string& queryName, Vertex<int>* sNode, Vertex<int>* dNode, vector<Vertex<int>*> nAvoid, vector<Edge<int>*> eAvoid, Vertex<int>* must, Graph<int>* g, std::ofstream& outFile) {
    outFile << queryName << endl;

    outFile << "Source:" << sNode->getInfo() << endl;
    outFile << "Destination:" << dNode->getInfo() << endl;

    //* A first drivingDijsktra's is called for the first shortest path
    resetGraph(g);
    restrictedDrivingDijkstra(g, sNode, nAvoid, eAvoid, must);

    vector<int> v;
    double dist = getRestrictedPath(g,sNode,dNode,must,v);
    outFile << "RestrictedDrivingRoute:";
    if (dist != -1){
        outputPath(v, outFile);
        outFile << '(' << dist << ')' << endl;
    }
    else{
        outFile << "none" << endl;
    }
}


void CLInterface::outputPath(vector<int>& v, ofstream& out) {
    if (v.empty()) return; //TODO
    for (int i = 0; i < v.size() - 1; i++) {
        out << v[i] << ',';
    }
    out << v[v.size() - 1];
}

void CLInterface::independantRoute(int sID, int dID, Graph<int>* g) {
    system("cls"); // clear screen
    cout << endl;
    cout << "Source:" << sID << endl;
    cout << "Destination:" << dID << endl;
    Vertex<int>* sNode = g->findVertex(sID);
    drivingDijkstra(g, sNode);
    cout << "BestDrivingRoute:";
}