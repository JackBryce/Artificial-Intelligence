#pragma once
#include "ANN.cpp";
#include "RNN.cpp";
#include "LSTM.cpp";
#include <vector>;
#include <string>;
#include <math.h>;

using namespace std;

class Layer {
	public:
		ANNBlock *ann;
		RNNBlock *rnn;
		LSTMBlock *lstm;
		bool _ann = false;
		bool _rnn = false;
		bool _lstm = false;
};

class DynamicNetworkGenerator {
	public:
		DynamicNetworkGenerator(const vector<vector<string>> &blockTypes);
		void feedFoward(const vector<double> &data);
		void backpropigation(const vector<double> &targets);
		vector<vector<string>> performance();
		vector<double> output;
		vector<vector<Layer*>> m_layer;
};