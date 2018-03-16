#include "Core.h";

//This constructor runs the Core AI.
Core::Core(int count) {
	//Variables
	KeyGenerator kg = new KeyGenerator();
	AIs.push_back(new ArtificialIntelligence());
	key = kg.generateKey(binary(count));
	updatedKey = key;

	//Processes
	while (updatedKey == key) {
		bool allMaxNetworks = false;
		vector<bool> maxNetwork;
		for (int i = 0; i < AIs.size(); i++) {
			maxNetwork.push_back(false);
		}

		/* --- 
		   Check the amount of neural networks an AI has, if the AI has 16 neural networks then.
		   --- */
		vector<int> numNetworks;
		for (int i = 0; i < AIs.size(); i++) {
			numNetworks.push_back(AIs.networkDetails.size());
			if (numNetworks[i] == 16) {
				maxNetwork[i] = true;
			}
		}

		for (int i = 0; i < maxNetwork.size(); i++) {
			if (maxNetwork[i] == true) {
				allMaxNetwork = true;
			} else {
				allMaxNetwork = false;
			}
		}

		/* --- 
		   If there are 16 AIs and one needs to be added, then create a core and then add the new AI to that core, else create a new AI in the current Core. 
		   --- */
		if (AIs.size() < 16 && allMaxNetwork == true) {
			AIs.push_back(new ArtificialIntelligence());
		} else if (AIs.size()+1 == 16 && subcore.size() < 16) {
			subcore.push_back(new Core());
		}
	}
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