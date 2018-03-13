#pragma once
#include "Block.cpp";

class ANNBlock : public Block {
	public:
		ANNBlock();
		void feedFoward(double data);

	private:
		double value;
		double activationFunction(double z) { return ((exp(z) - (exp(-z))) / ((exp(z) + (exp(-z)))); }
};