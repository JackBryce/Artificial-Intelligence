#pragma once
#include "ArtificialIntelligence.cpp";
#include "DynamicNetworkGenerator.cpp";
#include "DataSet.h";
#include <string>;
#include <vector>;
#include <bitset>;
#include <iostream>;

using namespace std;

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