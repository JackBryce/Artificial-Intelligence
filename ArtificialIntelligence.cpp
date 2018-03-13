#include "ArtificialIntelligence.h";
#include <random>;

using namespace std;

//This constructor runs the Artificial Intelligence.
ArtificialIntelligence::ArtificialIntelligence(int count) {
	kg = new KeyGenerator();
	id = kg.generateKey(count);
	updatedKey = kg.generateKey(rand()%16);
	setupAI();

	while (checkID()) {
		
	}
}

//This method sets up the text based Recurrent Neural Network.
ArtificialIntelligence::setupAI() {
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

	_textNetwork = new DynamicNetworkGenerator(textNetwork);
}

//This method compares the id with a potentially updated key.
bool ArtificialIntelligence::checkID() {
	bool stayActive = true;
	if (this.privateKey != privateKey) {
		stayActive = false;
	}

	return stayActive;
}

//This method creates a binary string to generate a id for the AI and cores.
string ArtificialIntelligence::binary(int n) {
	string binaryVal;
	while (n != 0) {
		binaryVal += (n % 2 == 0 ? "0" : "1");
		n /= 2;
	}

	return binaryVal;
}

//This runs the Neural Network and processes the data before feeding it into the network.
template <typename T> void ArtificialIntelligence::runNetwork(fstream data, string dataType) {
	if (dataType == "AUDIO") {
		audioProcessing(data);
	} else if (dataType == "IMAGE") {
		imageProcessing(data);
	} else if (dataType == "TEXT") {
		textProcessing(data);
	} else {
		videoProcessing(data);
	}
}

//This creates a new Neural Network for the AI.
template <typename T> void ArtificialIntelligence::addNetwork(int count, vector<vector<string>> networkSetup) {
	threadDetails td = new threadDetails();
	td.id = _HEX(count);
	td.network = new DynamicNetworkGenerator(networkSetup);
	td.active = true;
	networkDetails.push_back(td);
}

//This prepares the audio data to be fed into the neural network.
void ArtificialIntelligence::audioProcessing(fstream data) {

}

//This prepares the image data to be fed into the neural network.
void ArtificialIntelligence::imageProcessing(fstream data) {

}

//This prepares the text data to be fed into the neural network.
void ArtificialIntelligence::textProcessing(fstream data) {

}

//This prepares the video data to be fed into the neural network.
void ArtificialIntelligence::videoProcessing(fstream data) {

}