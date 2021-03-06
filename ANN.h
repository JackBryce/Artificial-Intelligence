#pragma once
#include "Block.cpp";

class ANNBlock : public Block {
	public:
		ANNBlock(int nextLayerSize);
		vector<double> feedFoward(double data);
		double getValue();
		double activationFunction(double z) { return ((exp(z) - (exp(-z))) / ((exp(z) + (exp(-z))))); }

	private:
		double value;
};