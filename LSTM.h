#pragma once
#include "Block.cpp";

class LSTMBlock : public Block {
	public:
		LSTMBlock(int nextLayerSize);
		vector<double> feedFoward(double data);
		double getValue();
		double getOutput() { return output; }
		double activationFunction(double z) { return ((exp(z) - (exp(-z))) / ((exp(z) + (exp(-z))))); }
		double sigmoidFunction(double z);

	private:
		double cell = 1.0;
		double prevCell = 1.0;
		double output = 0.0;
};