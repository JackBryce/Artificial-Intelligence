#pragma once
#include "Block.cpp";

class RNNBlock : public Block {
	public:
		RNNBlock();
		void feedFoward(double data);

	private:
		double value;
		double activationFunction(double z) { return ((exp(z) - (exp(-z))) / ((exp(z) + (exp(-z)))); }
};