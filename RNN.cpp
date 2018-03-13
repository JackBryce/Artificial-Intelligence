#include "RNN.h";

RNNBlock::RNNBlock() {
	weightsFoward.push_back(Connection());
	weightsRecurrent.push_back(Connection());
	weightsFoward.back().weight = randWeight();
	weightsRecurrent.back().weight = randWeight();
}

void RNNBlock::feedFoward(double data) {
	value *= data * weightFoward[0].weight*weightRecurrent[0].weight;
}