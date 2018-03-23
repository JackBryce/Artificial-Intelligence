#include "ArtificialIntelligence.h";
#include <random>;
#include <thread>;

using namespace std;

//This constructor runs the Artificial Intelligence.
ArtificialIntelligence::ArtificialIntelligence(int count) {
	//Variables
	thread filesThread(fileThread);
	thread networksThread(networksThread);
	thread performancesThread(performancesThread);
	kg = new KeyGenerator();
	id = kg.generateKey(count);
	updatedKey = id;
	setupAI();

	filesThread.join();
	networksThread.join();
	performancesThread.join();
}

void ArtificialIntelligence::fileThread() {
	while (checkID()) {
		/* --- Check for new data files for DynamicNetworkGenerator's text RNN, video/image CNN to build the network. --- */


		/* --- Run data from section above through the appropriate Neural Network to generate a network if required. --- */

	}
}

void ArtificialIntelligence::networkThread() {
	while (checkID()) {
		/* --- Feed the appropriate data files into the appropriate existing neural network if required and fetch any appropriate data from the Core's memory matrix. --- */


		/* --- Store the output data from the neural networks above into the AI's Core's memory matrix if required. --- */
	}
}

void ArtificialIntelligence::performanceThread() {
	while (checkID()) {
		/* --- Check on the performance of the neural networks. --- */


		/* --- Use the data from the preformance check to decide whether or not to remove a specific neural network --- */
	}
}

//This method sets up the text based Recurrent Neural Network and the video and image CNN's.
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
void ArtificialIntelligence::runNetwork(ifstream data, string dataType) {
	switch (dataType) {
		case "AUDIO":
			audioProcessing(data);

		case "IMAGE":
			imageProcessing(data);

		case "TEXT":
			textProcessing(data);

		case "VIDEO":
			videoProcessing(data);
	}


}

//This creates a new Neural Network for the AI.
void ArtificialIntelligence::addNetwork(int count, vector<vector<string>> networkSetup) {
	threadDetails td = new threadDetails();
	td.id = _HEX(count);
	td.network = new DynamicNetworkGenerator(networkSetup);
	td.active = true;
	networkDetails.push_back(td);
}

//This prepares the audio data to be fed into the neural network.
void ArtificialIntelligence::audioProcessing(ifstream data) {

}

//This prepares the image data to be fed into the neural network.
void ArtificialIntelligence::imageProcessing(ifstream data) {

}

//This prepares the text data to be fed into the neural network.
void ArtificialIntelligence::textProcessing(ifstream data) {

}

//This prepares the video data to be fed into the neural network.
void ArtificialIntelligence::videoProcessing(ifstream data) {

}