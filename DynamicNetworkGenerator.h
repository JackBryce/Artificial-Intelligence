#pragma once
#include "ANN.cpp";
#include "RNN.cpp";
#include "LSTM.cpp";
#include <vector>;
#include <string>;
#include <math.h>;

using namespace std;

template <typename T> Layer;
class DynamicNetwork {
	public:
		DynamicNetwork(const vector<vector<string>> *blockTypes);
		void feedFoward(const vector<double> &data);
		void backpropigation();

	private:
		vector<Layer> m_layer;
}