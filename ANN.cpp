#include "ANN.h";

ANNBlock::ANNBlock(int nextLayerSize) {
	if (nextLayerSize != 0) {
		for (int i = 0; i < nextLayerSize; i++) {
			weightsFoward.push_back(Connection());
			weightsFoward.back().weight = rand()/RAND_MAX;
		}
	} else {
		weightsFoward.push_back(Connection());
		weightsFoward.back().weight = 1.0;
	}
}

vector<double> ANNBlock::feedFoward(double data) {
	vector<double> layer;
	for (int i = 0; i < weightsFoward.size(); i++) {
		layer.push_back(weightsFoward[i].weight*data);
	}

	return layer;
}

double ANNBlock::getValue() {
	return value;
}