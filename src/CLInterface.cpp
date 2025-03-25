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

void CLInterface::presentPath(vector<int>& v) {
    for (int i = 0; i < v.size() - 1; i++) {
        cout << v[i] << ',';
    }
    cout << v[v.size() - 1] << endl;
}

void CLInterface::independantRoute(int sID, int dID, Graph<int>* g) {
    system("cls"); //clear screen
    cout << endl;
    cout << "Source:" << sID << endl;
    cout << "Destination:" << dID << endl;

    drivingDijkstra(g, sID);
    vector<int> res = getPath(g, sID, dID);
    cout << "BestDrivingRoute:";
    presentPath(res);
}