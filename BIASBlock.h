#pragma once
#include "block.cpp";

class BIASBlock : public Block {
	public:
		BIASBlock(int nextLayerSize);
		double getValue() { return value; }
		double activationFunction(double z) { return ((exp(z) - (exp(-z))) / ((exp(z) + (exp(-z))))); }

	private:
		double value;
};