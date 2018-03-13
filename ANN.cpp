#include "ANN.h";

ANNBlock::ANNBlock() {
	weightsFoward.push_back(Connection());
	weightsFoward.back().weight = randWeight();
}

void ANNBlock::feedFoward(double data) {
	value = weightsFoward[0].weight*data;
}