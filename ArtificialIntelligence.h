#pragma once
#include "DynamicNetworkGenerator.cpp";
#include "KeyGenerator.cpp";
#include <vector>;
#include <iostream>;
#include <fstream>;
#include <string>;

using namespace std;

struct threadDetails {
	string id;
	DynamicNetworkGenerator network;
	bool active;
};

class ArtificialIntelligence {
	public:
		string id;
		string updatedKey;
		KeyGenerator kg;
		ArtificialIntelligence();
		void runNetwork(fstream data, string dataType);
		template <typename T> void addNetwork(int count, T network);

	private:
		vector<threadDetails> networkDetails;
		vector<string> filePaths;
		vector<string> newFiles;
		DynamicNetworkGenerator _textNetwork;
		string binary();
		bool checkID();
		void fileThread();
		void networkThread();
		void performanceThread();
		void audioProcessing(fstream data);
		void imageProcessing(fstream data);
		void textProcessing(fstream data);
		void videoProcessing(fstream data);
};