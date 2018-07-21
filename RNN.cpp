#include "Block.cpp";
#include "RNN.h";

RNNBlock::RNNBlock(int nextLayerSize) {
	if (nextLayerSize != 0) {
		for (int i = 0; i < nextLayerSize; i++) {
			weightsFoward.push_back(Connection());
			weightsFoward.back().weight = rand()/RAND_MAX;
		}
	} else {
		weightsFoward.push_back(Connection());
		weightsFoward.back().weight = 1.0;
	}

	weightsRecurrent.push_back(Connection());
	weightsRecurrent.back().weight = rand()/RAND_MAX;
}

vector<double> RNNBlock::feedFoward(double data) {
	int recurrentCalc = data * weightsRecurrent[0].weight;
	vector<double> values;
	for (int i = 0; i < weightsFoward.size(); i++) {
		values.push_back(recurrentCalc*weightsFoward[i].weight);
		value *= recurrentCalc * weightsFoward[i].weight;
	}

	return values;
}

double RNNBlock::getValue() {
	return value;
}