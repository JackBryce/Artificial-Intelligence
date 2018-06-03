#pragma once
#include "ArtificialIntelligence.cpp";
#include "DynamicNetworkGenerator.cpp";
#include <string>;
#include <vector>;
#include <bitset>;
#include <iostream>;

using namespace std;

struct DataSet {
	string id;
	vector<double> memoryMatrixOutput;
	vector<double> memoryMatrixInputS;		    //For Text and Audio.
	vector<vector<double>> memoryMatrixInputL;  //For Images and Videos due to RGB.
};

struct Node {
	string id;
	vector<string> AI_ID;
	vector<ArtificialIntelligence*> AIs;
	vector<DataSet*> ds;
};

class Network {
	public:
		Network();
		void addNode();
		void addAI(const string &nodeID);
		int getNodesSize();
		Node* getNode(int i);

	private:
		vector<Node*> nodes;
};