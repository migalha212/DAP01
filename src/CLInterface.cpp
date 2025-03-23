#include "CLInterface.h"
#include "ShortestPathAlgorithms.cpp"
using namespace std;

void CLInterface::presentUI() {
    system("cls"); // clears the terminal
    while (true) {
        cout << endl << "Choose an option:" << endl;
        cout << "1: Shortest driving Path from A to B" << endl;
        cout << "2: Shortest walking Path from A to B" << endl;
        
        int choice;
        cin >> choice;
        
        while (choice < 1 || choice > 2) {
            cout << "Choose a valid option" << endl;
            cin >> choice;
        }
        switch (choice) {
            case 1:
            this->simpleDist();
            break;
            default:
            return;
        }
        cin >> choice;
        return;
    }
}

void CLInterface::simpleDist() {
    //system("cls");
    Graph<int> graph;
    Parsefile parser;
    parser.parseLocation("../small_data/Locations.csv",&graph);
    parser.parseDistance("../small_data/Distances.csv", &graph);
    cout << endl;
    cout << "Chosen: Shortest driving Path from A to B" << endl;
    cout << "Enter the desired values for A and B" << endl;
    int a,b;
    cin >> a >> b;

    dijkstra(&graph,a);
    getPath(&graph,a,b);
}
