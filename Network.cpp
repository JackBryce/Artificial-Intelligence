#include "Network.h";

//This constructor adds a node to a network and adds an AI to that node.
Network::Network() {
	Node *n = new Node();
	n->id = bitset<16>(0).to_string();
	n->AI_ID.push_back(n->id + bitset<2>(0).to_string());
	n->AIs.push_back(new ArtificialIntelligence(0));
	nodes.push_back(n);
}

//This method adds a node to the network.
void Network::addNode() {
	if (nodes.size() != 65535) {
		Node *n = new Node();
		n->id = bitset<16>(nodes.size() + 1).to_string();
		n->AI_ID.push_back(bitset<2>(0).to_string());
		n->AIs.push_back(new ArtificialIntelligence(nodes.size()+1));
		nodes.push_back(n);
		cout << "The Node " << n->id << " has been added to the network!!!" << endl;
	}
}

//This method adds a new AI to a specific node.
void Network::addAI(const string &nodeID) {
	bool found = false;
	int count = 0;

	while (found == false && count < nodes.size()) {
		if (nodes[count]->id == nodeID) {
			if (nodes[count]->AIs.size() != 4) {
				nodes[count]->AIs.push_back(new ArtificialIntelligence(nodes[count]->AIs.size()+1));
				nodes[count]->AI_ID.push_back(bitset<2>(nodes[count]->AIs.size()).to_string());
			}

			found = true;
		}
		count += 1;
	}

	cout << "An AI has been added to the node " << nodeID << "!!!" << endl;
}

//This returns the size of the node vector.
int Network::getNodesSize() {
	return nodes.size();
}

Node* Network::getNode(int i) {
	return nodes[i];
}