#include "LSTM.h";

LSTMBlock::LSTMBlock() {
	for (int i = 0; i < 4; i++) {
		lstmBiases.push_back(rand()/RAND_MAX);
		weightsRecurrent.push_back(rand()/RAND_MAX);
	}

	for (int i = 0; i < 3; i++) {
		weightCell.push_back(rand()/RAND_MAX);
	}

	weightsFoward.push_back(rand()/RAND_MAX);
}

double LSTMBlock::sigmoidFunction(double z) {
	return (1 / 1 - exp(-z));
}

void LSTMBlock::feedFoward(double data) {
	prevCell = cell;
	cell = activationFunction((output*weightsRecurrent[0].weight)*(lstmBiases[0].weight*data));
	cell *= sigmoidFunction((weightCell[0].weight*prevCell)*(output*weightsRecurrent[1].weight)*(lstmBiases[1].weight*data));
	cell *= sigmoidFunction((weightCell[1].weight*prevCell)*(output*weightsRecurrent[2].weight)*(lstmBiases[2].weight*data));
	output = activationFunction(cell) * sigmoidFunction((weightCell[2].weight*prevCell)*(output*weightsRecurrent[3].weight)*(lstmBiases[3].weight*data));
}

double LSTMBlock::getValue() {
	return cell;
}