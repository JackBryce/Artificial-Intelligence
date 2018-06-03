#include "Block.cpp";

#include "RNN.h";

RNNBlock::RNNBlock() {
	weightsFoward.push_back(Connection());
	weightsRecurrent.push_back(Connection());
	weightsFoward.back().weight = rand()/RAND_MAX;
	weightsRecurrent.back().weight = rand()/RAND_MAX;
}

void RNNBlock::feedFoward(double data) {
	value *= data * weightsFoward[0].weight*weightsRecurrent[0].weight;
}

double RNNBlock::getValue() {
	return value;
}