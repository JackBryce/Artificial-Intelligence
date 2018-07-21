#include "LSTM.h";

LSTMBlock::LSTMBlock(int nextLayerSize) {
	for (int i = 0; i < 4; i++) {
		lstmBiases.push_back(Connection());
		lstmBiases.back().weight = rand()/RAND_MAX;
		weightsRecurrent.push_back(Connection());
		weightsRecurrent.back().weight = rand()/RAND_MAX;
	}

	for (int i = 0; i < 3; i++) {
		weightCell.push_back(Connection());
		weightCell.back().weight = rand()/RAND_MAX;
	}

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

double LSTMBlock::sigmoidFunction(double z) {
	return (1 / 1 - exp(-z));
}

vector<double> LSTMBlock::feedFoward(double data) {
	vector<double> neurons;
	prevCell = cell;

	cell = activationFunction((output*weightsRecurrent[0].weight)*(lstmBiases[0].weight*data));
	cell *= sigmoidFunction((weightCell[0].weight*prevCell)*(output*weightsRecurrent[1].weight)*(lstmBiases[1].weight*data));
	cell *= sigmoidFunction((weightCell[1].weight*prevCell)*(output*weightsRecurrent[2].weight)*(lstmBiases[2].weight*data));
	output = activationFunction(cell) * sigmoidFunction((weightCell[2].weight*prevCell)*(output*weightsRecurrent[3].weight)*(lstmBiases[3].weight*data));

	for (int i = 0; i < weightsFoward.size(); i++) {
		neurons.push_back(output*weightsFoward[i].weight);
	}

	return neurons;
}

double LSTMBlock::getValue() {
	return cell;
}