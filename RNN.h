#pragma once
#include "Block.cpp";

class RNNBlock : public Block {
	public:
		RNNBlock(int nextLayerSize);
		vector<double> feedFoward(double data);
		double getValue();
		double activationFunction(double z) { return ((exp(z) - (exp(-z))) / ((exp(z) + (exp(-z))))); }

	private:
		double value;
};