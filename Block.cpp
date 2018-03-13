#include "Block.h";

double Block::transferFunction(double x) {
	return tanh(x);
}
double Block::transferFunctionDerivative(double x) {
	return 1.0 - (tanh(x)*tanh(x));
}
void Block::feedFoward(const Layer &prevLayer) {
	double sum = 0.0;

	for (unsigned i = 0; i < prevLayer.size(); i++) {
		sum += prevLayer[i].getOutputVal()*weightsFoward[m_myIndex].weight;
	}

	outputFoward = Neuron::transferFunction(sum);
}
void Block::calcOutputGradients(double targetVal) {
	double delta = targetVal - outputFoward;
	m_gradient = delta * Neuron::transferFunctionDerivative(outputFoward);
}
void Block::calcHiddenGradients(const Layer &nextLayer) {
	double dow = sumDOW(nextLayer);
	m_gradient = dow * Neuron::transferFunctionDerivative(outputFoward);
}
double Block::sumDOW(const Layer &nextLayer) const {
	double sum = 0.0;

	for (unsigned n = 0; n < nextLayer.size() - 1; n++) {
		sum += weightsFoward[n].weight*nextLayer[n].m_gradient;
	}

	return sum;
}
void Block::updateInputWeights(Layer &prevLayer) {
	for (unsigned n = 0; n < prevLayer.size(); n++) {
		Neuron &neuron = prevLayer[n];
		double oldDeltaWeight = neuron.weightsFoward[m_myIndex].deltaWeight;
		double newDeltaWeight = eta * neuron.getOutputVal()*m_gradient + alpha * oldDeltaWeight;

		neuron.weightsFoward[m_myIndex].deltaWeight = newDeltaWeight;
		neuron.weightsFoward[m_myIndex].weight += newDeltaWeight;
	}
}
double Block::eta = 0.15;
double Block::alpha = 0.5;