#include "ArtificialIntelligence.h";
#include <random>;
#include <thread>;
#include <string>;
#include <iostream>;
#include <fstream>;
#include <windows.h>;

using namespace std;

//This constructor runs the Artificial Intelligence.
ArtificialIntelligence::ArtificialIntelligence(int count) {
	id = bitset<8>(count).to_string();
	updatedKey = id;
	setupAI();
	thread(Thread); //C1189 error
}

void ArtificialIntelligence::Thread() {
	vector<WCHAR*> files;
	vector<WCHAR*> newFiles;

	//Load the files into the vector for the initial files.
	WIN32_FIND_DATA fd;
	HANDLE h = FindFirstFile((LPCWSTR)"*.txt", &fd); //Need to convert all files to the video, images etc. to text files.
	if (h != INVALID_HANDLE_VALUE) {
		do {
			files.push_back(fd.cFileName);
		} while (FindNextFile(h, &fd));
		FindClose(h);
	}
	int initialSize = files.size();
	int count = files.size();

	int counter = 0;
	int pointOne = 0;
	int pointTwo = 0;
	int pointThree = 0;
	while (updatedKey == id) {
		/* --- Check for new data files for DynamicNetworkGenerator's text RNN, video/image CNN to build the network. --- */
		WIN32_FIND_DATA fd;
		HANDLE audio = FindFirstFile((LPCWSTR)".mp3", &fd);
		HANDLE image = FindFirstFile((LPCWSTR)".png", &fd);
		HANDLE text = FindFirstFile((LPCWSTR)"*.txt", &fd);
		HANDLE video = FindFirstFile((LPCWSTR)"*.avi", &fd);

		if (audio != INVALID_HANDLE_VALUE) {
			do {
				newFiles.push_back(fd.cFileName);
				counter += 1;
			} while (FindNextFile(audio, &fd));
		} else if (image != INVALID_HANDLE_VALUE) {
			pointOne = counter;
			do {
				newFiles.push_back(fd.cFileName);
				counter += 1;
			} while (FindNextFile(image, &fd));
		} else if (text != INVALID_HANDLE_VALUE) {
			pointTwo = counter;
			do {
				newFiles.push_back(fd.cFileName);
				counter += 1;
			} while (FindNextFile(text, &fd));
			FindClose(text);
		} else if (video != INVALID_HANDLE_VALUE) {
			pointThree = counter;
			do {
				newFiles.push_back(fd.cFileName);
			} while (FindNextFile(video, &fd));
		}
		count = newFiles.size();

		if ((initialSize - count) < 0) {
			files = newFiles;
			newFiles.empty();

			/* --- Run data from section above through the appropriate Neural Network to generate a network if required. --- */
			for (int i = 0; i < files.size(); i++) {
				string line;
				ifstream fileInput;
				fileInput.open(files[i], ios::binary);

				int n = 1;
				double count = 0.0;

				vector<double> data;
				while (getline(fileInput, line)) {
					for (int i = line.size(); i >= 0; i--) {
						if (line[i] == '1') {
							count += n;
						}

						n *= 2;
					}
					n = 1;

					while (count < 0) {
						count /= 10;
					}
					data.push_back(count);
				}

				/* --- Feed the appropriate data files into the appropriate existing neural network if required and fetch any appropriate data from the Core's memory matrix. --- */
				for (int i = 0; i < data.size(); i++) {
					if (i <= pointOne) {
						_audioNetwork->feedFoward(data);
					} else if (i > pointOne && i <= pointTwo) {
						_imageNetwork->feedFoward(data);
					} else if (i > pointTwo && i <= pointThree) {
						_textNetwork->feedFoward(data);
					} else {
						_videoNetwork->feedFoward(data);
					}

				}
			}

			/* --- Store the output data from the neural networks above into the AI's Core's memory matrix if required. --- */


		}

		/* --- Check on the performance of the neural networks. --- */
		//Data Sets Collected - dsc
		//Data Sets Processed - dsp


		/* --- Use the data from the preformance check to decide whether or not to remove a specific neural network --- */


	}
}

//This method sets up the text based Recurrent Neural Network and the video and image CNN's.
void ArtificialIntelligence::setupAI() {
	vector<vector<string>> audioNetwork;
	vector<vector<string>> imageNetwork;
	vector<vector<string>> textNetwork;
	vector<vector<string>> videoNetwork;
	vector<string> layer;

	//This creates the neural network for Audio.


	//This creates the neural network for Image.
	imageNetwork.push_back(layer);
	for (int i = 0; i < 4; i++) {
		imageNetwork.back().push_back("ANNBlock");
	}

	for (int i = 0; i < 2; i++) {
		imageNetwork.push_back(layer);
		for (int j = 0; j < 4; j++) {
			imageNetwork.back().push_back("ANNBlock");
		}
	}

	for (int i = 0; i < 6; i++) {
		imageNetwork.back().push_back("ANNBlock");
	}

	//This creates the neural network for Text.
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

	//This creates the neural network for Video.
	videoNetwork.push_back(layer);
	for (int i = 0; i < 4; i++) {
		videoNetwork.back().push_back("ANNBlock");
	}

	for (int i = 0; i < 2; i++) {
		videoNetwork.push_back(layer);
		for (int j = 0; j < 4; j++) {
			videoNetwork.back().push_back("ANNBlock");
		}
	}

	for (int i = 0; i < 6; i++) {
		videoNetwork.back().push_back("ANNBlock");
	}

	//This generates the neural networks and stores them in the AI.
	_audioNetwork = new DynamicNetworkGenerator(audioNetwork);
	_imageNetwork = new DynamicNetworkGenerator(imageNetwork);
	_textNetwork = new DynamicNetworkGenerator(textNetwork);
	_videoNetwork = new DynamicNetworkGenerator(videoNetwork);
}

//This creates a new Neural Network for the AI.
void ArtificialIntelligence::addNetwork(int count, vector<vector<string>> networkSetup) {
	threadDetails *td = new threadDetails();
	td->id = bitset<4>(count).to_string();
	td->network = new DynamicNetworkGenerator(networkSetup);
	td->active = true;
	networkDetails.push_back(td);
}

//This calculates the performance of a network from the AI.
string ArtificialIntelligence::networkPerformance() {
	string genome = "";
	for (int i = 0; i < networkDetails.size(); i++) {
		if ((networkDetails[i]->dataSetsProcessed/networkDetails[i]->dataSetsCollected) >= 90.0) {
			genome += "1";
		} else {
			genome += "0";
		}
	}

	return genome;
}