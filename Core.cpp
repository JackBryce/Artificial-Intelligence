#include "Core.h";

//This constructor runs the Core AI.
Core::Core(int count) {
	KeyGenerator kg = new KeyGenerator();
	key = kg.generateKey(binary(count));
	updatedKey = key;

	setupCore();

	while (checkID()) {

	}
}

//This method creates the neural networks to assist the Dynamic Network Generator.
void Core::setupCore() {
	vector<vector<string>> textNetwork;
	vector<string> layer;

	textNetwork.push_back(layer);
	for (int i = 0; i < 3; i++) {
		textNetwork.back().push_back("ANNBlock");
	}

	textNetwork.push_back(layer);
	textNetwork.back().push_back("RNNBlock");

	textNetwork.push_back(layer);
	for (int i = 0; i < 3; i++) {
		textNetwork.back().push_back("ANNBlock");
	}

	_textNetwork = new DynamicNetworkGenerator textNetwork;
}

//This method compares the id with a potentially updated key.
bool Core::checkID(string key) {
	bool stayActive = true;
	if (this.privateKey != privateKey) {
		stayActive = false;
	}

	return stayActive;
}

//This method creates a binary string to generate a id for the AI and cores.
string Core::binary(int n) {
	string binaryVal;
	while (n != 0) {
		binaryVal += (n % 2 == 0 ? "0" : "1");
		n /= 2;
	}

	return binaryVal;
}

//This method creates a new core to handle the excess data and process the data.
void Core::createSubcore() {
	subcore.push_back(new Core());
}

//This method creates a new network to process the data.
void Core::createAI() {

}