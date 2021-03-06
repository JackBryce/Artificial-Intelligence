// ConsoleApplication2.cpp : Defines the entry point for the console application.
//

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

//This constructor runs the System.
Core::Core() {
	bool running = true;
	networks.push_back(new Network());

	while (running) {
		vector<bool> nodesFull;
		vector<int> numberOfNodes;
		vector<bool> aisFull;
		vector<vector<int>> numberOfAIs; //For a network unit.
		vector<vector<int>> numberOfDS;  //Number of Data Sets.

		Node* node;
		/* This section of the Core calculates the amount of Nodes a network has and if it needs a new one and the amount of AIs a node has and if it needs a new one. */
		//This for loop retrieves the amount of data sets the node has in its posession.
		for (int i = 0; i < networks.size(); i++) {
			vector<int> noOfDS; //Just for one node.
			for (int j = 0; j < networks[i]->getNodesSize(); j++) {
				noOfDS.push_back(networks[i]->getNode(j)->ds.size());
			}
			numberOfDS.push_back(noOfDS);
		}

		//This for loop retrieves the amount of AI's the node has in its posession.
		for (int i = 0; i < networks.size(); i++) {
			vector<int> noOfAIs; //Just for one node.
			numberOfNodes.push_back(networks[i]->getNodesSize());
			for (int j = 0; j < networks[i]->getNodesSize(); j++) {
				noOfAIs.push_back(networks[i]->getNode(j)->AIs.size());
			}
			numberOfAIs.push_back(noOfAIs);
		}

		//Retrieve the number of data sets that was processed by the AIs of a Node and Nodes.
		vector<double> nodesDS; //For the Nodes.
		vector<vector<double>> aisDS; //For the AIs. (Nodes, AIs)

		for (int i = 0; i < networks.size(); i++) {
			for (int j = 0; j < networks[i]->getNodesSize(); j++) {
				vector<double> noOfDS;
				double total = 0;
				for (int k = 0; k < networks[i]->getNode(j)->AIs.size(); k++) {
					if (networks[i]->getNode(j)->AIs[k]->dataSetsSize() == 0) {
						noOfDS.push_back(networks[i]->getNode(j)->AIs[k]->dsProcessedTotal/1);
					} else {
						noOfDS.push_back(networks[i]->getNode(j)->AIs[k]->dsProcessedTotal/networks[i]->getNode(j)->AIs[k]->dataSetsSize());
					}
					total += noOfDS[k];
				}

				nodesDS.push_back(total);
				aisDS.push_back(noOfDS);
			}
		}

		//These for loops check the amount of AIs inside a node. If there is less than 65535 AIs in the Node then another AI will be added.
		for (int i = 0; i < networks.size(); i++) {
			vector<bool> full_ai;
			for (int j = 0; j < networks[i]->getNodesSize(); j++) {
				node = networks[i]->getNode(j);
				int aiSize = node->AIs.size();

				if (aiSize < 128 && aisDS[i][j] < 0.75) {
					node->AIs.push_back(new ArtificialIntelligence(aiSize + 1));
					full_ai.push_back(false);
				} else if (aiSize == 128)  {
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

		//This for loop will find if an AI needs to be added to a node.
		for (int i = 0; i < numberOfNodes.size(); i++) {
			//numberOfNodes[i] < 65536 && nodesDS[i] > 0.75
			if (numberOfNodes[i] < 65536) {
				networks[i]->addNode();
				cout << "A new node has been added to the network || " << numberOfNodes[i] + 1 << endl;
				nodesFull.push_back(false);
			} else {
				nodesFull.push_back(true);
			}
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

		vector<vector<int>> networkChange; //Network, Node
		for (int i = 0; i < networks.size(); i++) {
			for (int j = 0; j < networks[i]->getNodesSize(); j++) {
				for (int k = 0; k < networks[i]->getNode(j)->AIs.size(); k++) {
					networkChange.push_back(networks[i]->getNode(j)->AIs[k]->change);
				}
			}
		}

		vector<int> networkImprovement;
		vector<int> networkSize;
		for (int i = 0; i < networkChange.size(); i++) {
			int total = 0;
			for (int j = 0; j < networkChange[i].size(); j++) {
				if (networkChange[i][j] == 1) {
					total += 1;
				}
			}

			networkImprovement.push_back(total);
			networkSize.push_back(networkChange[i].size());
		}

		vector<int> Networks;
		for (int i = 0; i < networkImprovement.size(); i++) {
			if ((networkSize[i])%2 == 0) {
				Networks.push_back((networkSize[i])/2);
			} else {
				Networks.push_back((networkSize[i]/2)+0.5);
			}
		}

		int counting = 0;
		for (int i = 0; i < networkImprovement.size(); i++) {
			if (networkImprovement[i] > Networks[i]) {
				counting += 1;
			}
		}

		int N = 0;
		if (Networks.size()%2 == 0) {
			N = Networks.size()/2;
		} else {
			N = (Networks.size()/2)+0.5;
		}

		if (counting > N) {
			running = false;
		}

		//Create a network if the condition is met.
		if (full_node == true && AIFull == true) {
			networks.push_back(new Network());
		}
	}
}

int main() {
	Core *c = new Core();

	return 0;
}
