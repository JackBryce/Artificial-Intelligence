#include "Block.h";

//This sub-program feeds the previous layer into the next layer.
void Block::feedFoward(const vector<double> &prevLayer) {
	double sum = 0.0;

	for (unsigned i = 0; i < prevLayer.size(); i++) {
		sum += prevLayer[i]*weightsFoward[m_myIndex].weight;
	}

	outputFoward = transferFunction(sum);
}

//This sub-program calculates the gradients.
void Block::calcHiddenGradients(const vector<double> &nextLayer) {
	m_gradient = sumDOW(nextLayer) * transferFunctionDerivative(outputFoward);
}

//This sub-program calculates the sum of the differentiation of the weights.
double Block::sumDOW(const vector<double> &nextLayer) const {
	double sum = 0.0;

	for (unsigned n = 0; n < nextLayer.size() - 1; n++) {
		sum += weightsFoward[n].weight*nextLayer[n];
	}

	return sum;
}

//This sub-program updates the input weights.
void Block::updateInputWeights(vector<double> &prevLayer) {
	//prevLayer = weightsFoward[m_myIndex]->deltaWeight;
	for (unsigned n = 0; n < prevLayer.size(); n++) {
		double oldDeltaWeight = prevLayer[n].weightsFoward[m_myIndex]->deltaWeight;
		double newDeltaWeight = eta * prevLayer[n]*m_gradient + alpha * oldDeltaWeight;

		prevLayer[n].weightsFoward[m_myIndex]->deltaWeight = newDeltaWeight;
		prevLayer[n].weightsFoward[m_myIndex]->weight += newDeltaWeight;
	}
}