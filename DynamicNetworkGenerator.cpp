#include "DynamicNetworkGenerator.h";

DynamicNetwork::DynamicNetwork(const vector<vector<string>> &blockTypes) {
	for (int i = 0; i < blockTypes.size(); i++) {
		m_layer.push_back(Layer);
		unsigned numOutputs = index == topology.size() - 1 ? 0 : topology[index + 1];
		for (int j = 0; j < blockTypes[i].size(); j++) {
			if (i != block.size() - 1) {
				switch (blockTypes[i][j]) {
				case "ANNBlock":
					m_layer.back().push_back(new ANNBlock());

				case "RNNBlock":
					m_layer.back().push_back(new RNNBlock());

				case "LSTMBlock":
					m_layer.back().push_back(new LSTMBlock());
				}
			}
		}
	}
}

void DynamicNetwork::feedFoward(const vector<double> &data) {
	if (data.size() == m_layer[0].size()) {
		vector<double> input;
		for (unsigned i = 0; i < inputVals.size(); i++) {
			m_layer[0][i].setOutputVal(inputVals[i]);
			input.push_back(m_layer[0][i] * m_layer[0][i].weightsFoward);
		}

		vector<vector<double>> hiddenLayer;
		for (unsigned layerNum = 1; layerNum < m_layer.size(); layerNum++) {
			Layer &prevLayer = m_layer[layerNum - 1];
			vector<double> hiddenNeuron;

			for (unsigned n = 0; n < m_layer[layerNum].size() - 1; n++) {
				m_layer[layerNum][n].feedFoward(prevLayer);
				if (n == m_layer[layerNum].size() - 2) {
					hiddenNeuron.push_back(m_layer[layerNum][n].weightsFoward*m_layer[layerNum][n].weightsRecurrent);
				}
			}
			hiddenLayer.push_back(hiddenNeuron);
		}
	}
}

void DynamicNetwork::backpropigation() {
	// Calculate RMS(Root Mean Score Error)
	Layer &outputLayer = m_layer.back();
	m_error = 0.0;

	for (unsigned n = 0; n < outputLayer.size(); n++) {
		double delta = targetVals[n] - outputLayer[n].getOutputVal();
		m_error += delta * delta;
	}

	m_error /= outputLayer.size() - 1;
	m_error = sqrt(m_error);

	//Implement a recent average measurement.
	m_recentAverageError = (m_recentAverageError*m_recentAverageSmoothingFactor + m_error) / (m_recentAverageSmoothingFactor + 1.0);

	//Calculate Output Layer Gradients.
	for (unsigned n = 0; n < outputLayer.size() - 1; n++) {
		outputLayer[n].calcOutputGradients(targetVals[n]);
	}

	//Calculate gradients on hidden layers.
	for (unsigned layerNum = m_layer.size() - 2; layerNum > 0; layerNum--) {
		Layer &hiddenLayer = m_layer[layerNum];
		Layer &nextLayer = m_layer[layerNum + 1];

		for (unsigned n = 0; n < hiddenLayer.size(); n++) {
			hiddenLayer[n].calcHiddenGradients(nextLayer);
		}
	}

	//For all layers from outputs to first hidden layer, update connection weights.
	for (unsigned layerNum = m_layer.size() - 1; layerNum > 0; layerNum--) {
		Layer &layer = m_layer[layerNum];
		Layer &prevLayer = m_layer[layerNum - 1];

		for (unsigned n = 0; n < layer.size() - 1; n++) {
			layer[n].updateInputWeights(prevLayer);
		}
	}
}