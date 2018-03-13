#pragma once
#include "DynamicNetworkGenerator.cpp";
#include "ArtificialIntelligence.cpp";
#include "KeyGenerator.cpp";
#include <vector>;

using namespace std;

class Core {
	public:
		Core();
		void createSubcore();
		void createAI();
		bool checkID();

	private:
		string key;
		string updatedKey;
		vector<Core> subcore;
		DynamicNetworkGenerator _textNetwork;
		string binary();
		void setupCore();
};