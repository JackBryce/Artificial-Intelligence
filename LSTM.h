#pragma once
#include "Block.cpp";

class LSTMBlock : public Block {
	public:
		LSTMBlock();
		void feedFoward(double data);

	private:
		double cell = 1.0;
		double prevCell = 1.0;
		double output = 0.0;
		double activationFunction(double z) { return ((exp(z) - (exp(-z))) / ((exp(z) + (exp(-z)))); }
		double sigmoidFunction(double z);
};