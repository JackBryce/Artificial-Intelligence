#pragma once
#include "DynamicNetworkGenerator.cpp";
#include <vector>;
#include <iostream>;
#include <fstream>;
#include <string>;

using namespace std;

struct DataSet {
	string id;
	vector<vector<double>> data;
};

struct threadDetails {
	string id;
	DynamicNetworkGenerator *network;
	int dataSetsProcessed;
	int dataSetsCollected;
	bool active;
};

class ArtificialIntelligence {
	public:
		string id;
		string updatedKey;
		ArtificialIntelligence(int count);
		void runNetwork(fstream data, string dataType);
		void addNetwork(int count, vector<vector<string>> networkSetup);
		int networkSize() { return networkDetails.size(); }
		string networkPerformance();

	private:
		vector<threadDetails*> networkDetails;
		vector<string> filePaths;
		vector<string> newFiles;
		DynamicNetworkGenerator *_audioNetwork;
		DynamicNetworkGenerator *_imageNetwork;
		DynamicNetworkGenerator *_textNetwork;
		DynamicNetworkGenerator *_videoNetwork;
		string binary();
		void setupAI();
		bool checkID();
		void Thread();
		void audioProcessing(fstream data);
		void imageProcessing(fstream data);
		void textProcessing(fstream data);
		void videoProcessing(fstream data);
};