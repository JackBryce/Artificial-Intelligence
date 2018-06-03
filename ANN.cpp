#include "ANN.h";

ANNBlock::ANNBlock() {
	weightsFoward.push_back(Connection());
	weightsFoward.back().weight = rand()/RAND_MAX;
}

void ANNBlock::feedFoward(double data) {
	value = weightsFoward[0].weight*data;
}

double ANNBlock::getValue() {
	return value;
}