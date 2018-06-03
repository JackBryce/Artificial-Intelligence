// ConsoleApplication1.cpp : main project file.

#include "stdafx.h";
#include "Network.cpp";
#include <iostream>;

using namespace std;

class Core {
	public:
		Core();

	private:
		vector<Network*> networks;
		int Key;
};

Core::Core() {
	bool running = true;
	networks.push_back(new Network());
	
	while (running) {
		vector<bool> nodesFull;
		vector<int> numberOfNodes;
		vector<bool> aisFull;
		vector<vector<int>> numberOfAIs; //For a network unit.
		
		Node* node;
		/* This section of the Core calculates the amount of Nodes a network has and if it needs a new one and the amount of AIs a node has and if it needs a new one. */
		for (int i = 0; i < networks.size(); i++) {
			vector<int> noOfAIs; //Just for one node.
			numberOfNodes.push_back(networks[i]->getNodesSize());
			for (int j = 0; j < networks[i]->getNodesSize(); j++) {
				noOfAIs.push_back(networks[i]->getNode(j)->AIs.size());
			}
			numberOfAIs.push_back(noOfAIs);
		}

		//This for loop will find if an AI needs to be added to a node.
		for (int i = 0; i < numberOfNodes.size(); i++) {
			if (numberOfNodes[i] < 65536) {
				networks[i]->addNode();
				nodesFull.push_back(false);
			} else {
				nodesFull.push_back(true);
			}
		}

		//These for loops check the amount of AIs inside a node. If there is less than 65535 AIs in the Node then another AI will be added.
		for (int i = 0; i < networks.size(); i++) {
			vector<bool> full_ai;
			for (int j = 0; j < networks[i]->getNodesSize(); j++) {
				node = networks[i]->getNode(j);
				int aiSize = node->AIs.size();
				if (aiSize < 128) {
					node->AIs.push_back(new ArtificialIntelligence(aiSize+1));
					full_ai.push_back(false);
				} else {
					full_ai.push_back(true);
				}
			}

			bool full_AI = true;
			int index = 0;
			while (full_AI == true && index < full_ai.size()) {
				if (full_ai[index] == false) {
					full_AI == false;
				}
				index += 1;
			}

			aisFull.push_back(full_AI);
		}

		//This checks if a new network needs to be added to the Core.
		int count = 0;
		bool full_node = true;
		while (full_node == true && count < nodesFull.size()) {
			if (nodesFull[count] == false) {
				full_node = false;
			}
			count += 1;
		}

		int indexer = 0;
		bool AIFull = true;
		while (AIFull == true && indexer < aisFull.size()) {
			if (aisFull[indexer] == false) {
				AIFull = false;
			}
			indexer += 1;
		}

		if (full_node == true && AIFull == true) {
			networks.push_back(new Network());
		}

		/* This section of the Core calculates the performance of all the networks. The performance
		   depends on the adjusted performances of the nodes which is based upon the adjusted
		   performances of the AIs.
		 */


	}

	cout << "The System has Stopped Running!!!" << endl;
	cin.get();
}

int main() {
	Core *c = new Core();

	return 0;
}
