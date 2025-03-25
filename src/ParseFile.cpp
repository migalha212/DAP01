#include "ParseFile.h"

using namespace std;


void Parsefile::parseLocation(std::string filename, Graph<int> *graph) {
    fstream file(filename);
    string line;
    getline(file,line); // first line is ignored, header

    if(!file.is_open()){
        cerr << "Error occurred when opening file" << endl;
        return;
    }
    while(getline(file,line)){
        istringstream iss(line);
        string name,id,code,parking;
        getline(iss,name,',');
        getline(iss,id,',');
        getline(iss,code,',');
        getline(iss,parking,'\r');
        graph->addVertex(name, stoi(id), code, stoi(parking));
    }
    file.close();
    return;
}

void Parsefile::parseDistance(std::string filename, Graph<int> *graph) {
    fstream file(filename);
    string line;
    getline(file, line); // first line is ignored, header

    if (!file.is_open()) {
        cerr << "Error occurred when opening file" << endl;
        return;
    }
    while(getline(file,line)){
        istringstream iss(line);
        string code1,code2,walkTime,driveTime;
        getline(iss,code1,',');
        getline(iss,code2,',');
        getline(iss,driveTime,',');
        getline(iss,walkTime,'\r');
        double dt;
        if(driveTime == "X") dt = INF;
        else dt = stoi(driveTime);
        graph->addBidirectionalEdge(code1,code2,stoi(walkTime),dt);
    }
    file.close();
}
