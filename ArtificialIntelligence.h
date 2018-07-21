#pragma once
#include "DynamicNetworkGenerator.cpp";
#include "DataSet.h";
#include <vector>;
#include <iostream>;
#include <fstream>;
#include <string>;

using namespace std;

class threadDetails {
	public:
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
		int dsProcessedTotal;
		ArtificialIntelligence(int count);
		void runNetwork(fstream data, string dataType);
		void addNetwork(int count, vector<vector<string>> networkSetup);
		int networkSize() { return networkDetails.size(); }
		string networkPerformance();
		double activationFunction(double z) { return ((exp(z) - (exp(-z))) / ((exp(z) + (exp(-z))))); }
		int dataSetsSize() { return dataSets.size(); }
		vector<int> change;

	private:
		vector<threadDetails*> networkDetails;
		vector<DataSet*> dataSets;
		vector<string> filePaths;
		vector<string> newFiles;
		DynamicNetworkGenerator* _networkGenerator;
		DynamicNetworkGenerator* _audioNetwork;
		DynamicNetworkGenerator* _imageNetwork;
		DynamicNetworkGenerator* _textNetwork;
		DynamicNetworkGenerator* _videoNetwork;
		string binary();
		void setupAI();
		bool checkID();
		void Thread();
		void audioProcessing(fstream data);
		void imageProcessing(fstream data);
		void textProcessing(fstream data);
		void videoProcessing(fstream data);
};