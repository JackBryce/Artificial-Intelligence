#pragma once
#include "ANN.cpp";
#include "RNN.cpp";
#include "LSTM.cpp";
#include "BIASBlock.cpp";
#include <vector>;
#include <string>;
#include <math.h>;
#include <iostream>;

using namespace std;

class Layer {
	public:
		ANNBlock *ann;
		RNNBlock *rnn;
		LSTMBlock *lstm;
		BIASBlock *bias;
		bool _ann = false;
		bool _rnn = false;
		bool _lstm = false;
		bool _bias = false;
};

class DynamicNetworkGenerator {
	public:
		//This sub-program sets up the Neural Network with a Vector of Vector of Strings describing the node types.
		DynamicNetworkGenerator(vector<vector<string>> &blockTypes) {
			cout << "New Network!!!" << endl;
			for (int i = 0; i < blockTypes.size(); i++) {
				vector<Layer*> layers;
				unsigned numOutputs = i == blockTypes.size() - 1 ? 0 : blockTypes[i + 1].size();
				for (int j = 0; j < blockTypes[i].size(); j++) {
					Layer *layer = new Layer();
					if (blockTypes[i][j] == "ANNBlock") {
						if (i++ == blockTypes.size()-1) {
							i -= 1;
							layer->ann = new ANNBlock(0);
							layer->_ann = true;
						} else {
							i -= 1;
							layer->ann = new ANNBlock(blockTypes[i + 1].size());
							layer->_ann = true;
						}
					} else if (blockTypes[i][j] == "RNNBlock") {
						if (i++ == blockTypes.size()-1) {
							i -= 1;
							layer->rnn = new RNNBlock(0);
							layer->_rnn = true;
						} else {
							i -= 1;
							layer->rnn = new RNNBlock(blockTypes[i+1].size());
							layer->_rnn = true;
						}
					} else if (blockTypes[i][j] == "LSTMBlock") {
						if (i++ == blockTypes.size()-1) {
							i -= 1;
							layer->lstm = new LSTMBlock(0);
							layer->_lstm = true;
						} else {
							i -= 1;
							layer->lstm = new LSTMBlock(blockTypes[i + 1].size());
							layer->_lstm = true;
						}
					} else if (blockTypes[i][j] == "BIASBlock") {
						if (i++ == blockTypes.size()-1) {
							i -= 1;
							layer->bias = new BIASBlock(0);
							layer->_bias = true;
						} else {
							i -= 1;
							layer->bias = new BIASBlock(blockTypes[i+1].size());
							layer->_bias = true;
						}
					}
					layers.push_back(layer);
				}
				m_layer.push_back(layers);
			}
		}

		//This sub-program feeds the data through the Neural Network.
		void feedFoward(const vector<double> &data) {
			if (data.size() == m_layer[0].size()) {
				vector<double> input;
				for (unsigned i = 0; i < data.size(); i++) {
					if (m_layer[0][i]->_ann == true) {
						m_layer[0][i]->ann->setOutputVal(data[i]);
						m_layer[0][i]->ann->feedFoward(data[i]);
						input.push_back(m_layer[0][i]->ann->getValue());
					} else if (m_layer[0][i]->_rnn == true) {
						m_layer[0][i]->rnn->setOutputVal(data[i]);
						m_layer[0][i]->rnn->feedFoward(data[i]);
						input.push_back(m_layer[0][i]->rnn->getValue());
					} else if (m_layer[0][i]->_lstm == true) {
						m_layer[0][i]->lstm->setOutputVal(data[i]);
						m_layer[0][i]->lstm->feedFoward(data[i]);
						input.push_back(m_layer[0][i]->lstm->getValue());
					}
				}

				//Version One
				vector<double> prevNeurons;
				vector<double> Neurons;
				for (int i = 0; i < m_layer.size(); i++) {
					for (int j = 0; j < m_layer[i].size(); j++) {
						if (j <= m_layer[i].size()-2) {
							if (i == 0) {
								if (Neurons.size() == 0) {
									if (m_layer[0][j]->_ann == true) {
										Neurons = m_layer[0][j]->ann->feedFoward(data[j]);
									} else if (m_layer[0][j]->_rnn == true) {
										Neurons = m_layer[0][j]->rnn->feedFoward(data[j]);
									} else if (m_layer[0][j]->_lstm == true) {
										Neurons = m_layer[0][j]->lstm->feedFoward(data[j]);
									}
								} else {
									vector<double> calculations;
									if (m_layer[0][j]->_ann == true) {
										calculations = m_layer[0][j]->ann->feedFoward(data[j]);
										for (int k = 0; k < calculations.size(); k++) {
											Neurons[k] += calculations[k];
										}
									} else if (m_layer[0][j]->_rnn == true) {
										calculations = m_layer[0][j]->rnn->feedFoward(data[j]);
										for (int k = 0; k < calculations.size(); k++) {
											Neurons[k] += calculations[k];
										}
									} else if (m_layer[0][j]->_lstm == true) {
										calculations = m_layer[0][j]->lstm->feedFoward(data[j]);
										for (int k = 0; k < calculations.size(); k++) {
											Neurons[k] += calculations[k];
										}
									}
								}
							} else {
								if (prevNeurons.size() == 0) {
									if (m_layer[i][j]->_ann == true) {
										Neurons = m_layer[i][j]->ann->feedFoward(prevNeurons[j]);
									} else if (m_layer[i][j]->_rnn == true) {
										Neurons = m_layer[i][j]->rnn->feedFoward(prevNeurons[j]);
									} else if (m_layer[i][j]->_lstm == true) {
										Neurons = m_layer[i][j]->lstm->feedFoward(prevNeurons[j]);
									}
								} else {
									vector<double> calculations;
									if (m_layer[i][j]->_ann == true) {
										calculations = m_layer[i][j]->ann->feedFoward(prevNeurons[j]);
										for (int k = 0; k < calculations.size(); k++) {
											Neurons[k] += calculations[k];
										}
									} else if (m_layer[i][j]->_rnn == true) {
										calculations = m_layer[i][j]->ann->feedFoward(prevNeurons[j]);
										for (int k = 0; k < calculations.size(); k++) {
											Neurons[k] += calculations[k];
										}
									} else if (m_layer[i][j]->_lstm == true) {
										calculations = m_layer[i][j]->lstm->feedFoward(prevNeurons[j]);
										for (int k = 0; k < calculations.size(); k++) {
											Neurons[k] += calculations[k];
										}
									}
								}
							}
						} else if (j++ == m_layer[i].size()-2 && m_layer[i][j]->_bias == true) {
							for (int k = 0; k < Neurons.size(); k++) {
								Neurons[k] += m_layer[i][j]->bias->weightsFoward[k].weight;
								Neurons[k] = m_layer[i][j]->bias->activationFunction(Neurons[k]);
							}
						}
					}

					prevNeurons = Neurons;
					Neurons.empty();
				}

				//Version Two
				vector<vector<double>> hiddenLayer;
				hiddenLayer.push_back(input);
				for (unsigned layerNum = 1; layerNum < m_layer.size(); layerNum++) {
					vector<double> hiddenNeuron;
					for (unsigned n = 0; n < m_layer[layerNum].size() - 1; n++) {
						if (n <= m_layer[layerNum].size() - 2) {
							if (m_layer[layerNum][n]->_ann == true) {
								m_layer[layerNum][n]->ann->feedFoward(hiddenLayer[layerNum - 1][n]);
								hiddenNeuron.push_back(m_layer[layerNum][n]->ann->getValue());
							} else if (m_layer[layerNum][n]->_rnn == true) {
								m_layer[layerNum][n]->rnn->feedFoward(hiddenLayer[layerNum - 1][n]);
								hiddenNeuron.push_back(m_layer[layerNum][n]->rnn->getValue());
							} else if (m_layer[layerNum][n]->_lstm == true) {
								m_layer[layerNum][n]->lstm->feedFoward(hiddenLayer[layerNum - 1][n]);
								hiddenNeuron.push_back(m_layer[layerNum][n]->lstm->getValue());
							}
						}
					}
					hiddenLayer.push_back(hiddenNeuron);
				}
				output = hiddenLayer[m_layer.size()-1];
			}
		}

		//This sub-program trains the Neural Network with backpropigation.
		void backpropigation(const vector<double> &targetVals) {
			// Calculate RMS(Root Mean Score Error)
			vector<Layer*> &outputLayer = m_layer[m_layer.size() - 1];
			double m_error = 0.0;

			double delta;
			for (unsigned n = 0; n < outputLayer.size(); n++) {
				delta = targetVals[n] - outputLayer[n]->ann->getOutputVal();
				m_error += delta * delta;
			}

			m_error /= outputLayer.size() - 1;
			m_error = sqrt(m_error);

			//Implement a recent average measurement.
			double m_recentAverageSmoothingFactor = rand() / RAND_MAX;
			double m_recentAverageError = (m_recentAverageError*m_recentAverageSmoothingFactor + m_error) / (m_recentAverageSmoothingFactor + 1.0);

			//Calculate Output Layer Gradients.
			for (unsigned n = 0; n < outputLayer.size() - 1; n++) {
				outputLayer[n]->ann->calcOutputGradients(targetVals[n]);
			}

			//Calculate gradients on hidden layers.
			for (unsigned layerNum = m_layer.size() - 2; layerNum > 0; layerNum--) {
				vector<Layer*> &hiddenLayer = m_layer[layerNum];
				vector<double> nextLayer; //m_layer[layerNum+1]
				vector<double> nextLayerTwo;
				bool first = true;
				int count = 0;

				for (int i = 0; i < m_layer[layerNum].size(); i++) {
					if (m_layer[layerNum][i]->_ann == true) {
						for (int j = 0; j < m_layer[layerNum][i]->ann->weightsFoward.size(); j++) {
							if (first == true) {
								nextLayer.push_back(m_layer[layerNum][i]->ann->weightsFoward[j].weight);
							} else {
								nextLayerTwo.push_back(m_layer[layerNum][i]->ann->activationFunction(nextLayer[i] * m_layer[layerNum][i]->ann->weightsFoward[j].weight));
							}
						}
					} else if (m_layer[layerNum + 1][i]->_rnn == true) {
						if (first == true) {
							nextLayer.push_back(m_layer[layerNum][i]->rnn->weightsFoward[0].weight*m_layer[layerNum][i]->rnn->weightsRecurrent[0].weight);
						} else {
							nextLayerTwo.push_back(m_layer[layerNum][i]->rnn->activationFunction(m_layer[layerNum][i]->rnn->weightsFoward[0].weight*m_layer[layerNum][i]->rnn->weightsRecurrent[0].weight));
						}
					} else if (m_layer[layerNum + 1][i]->_lstm == true) {
						double cell;
						if (first == true) {
							cell = m_layer[layerNum][i]->lstm->activationFunction((m_layer[layerNum][i]->lstm->weightsRecurrent[0].weight)*(m_layer[layerNum][i]->lstm->lstmBiases[0].weight));
							cell *= m_layer[layerNum][i]->lstm->sigmoidFunction((m_layer[layerNum][i]->lstm->weightCell[0].weight)*(m_layer[layerNum][i]->lstm->weightsRecurrent[1].weight)*(m_layer[layerNum][i]->lstm->lstmBiases[1].weight));
							cell *= m_layer[layerNum][i]->lstm->sigmoidFunction((m_layer[layerNum][i]->lstm->weightCell[1].weight)*(m_layer[layerNum][i]->lstm->weightsRecurrent[2].weight)*(m_layer[layerNum][i]->lstm->lstmBiases[2].weight));
							nextLayer.push_back(m_layer[layerNum][i]->lstm->activationFunction(cell) * m_layer[layerNum][i]->lstm->sigmoidFunction((m_layer[layerNum][i]->lstm->weightCell[2].weight)*(m_layer[layerNum][i]->lstm->weightsRecurrent[3].weight)*(m_layer[layerNum][i]->lstm->lstmBiases[3].weight)));
							count += 1;
						} else {
							cell = m_layer[layerNum][i]->lstm->activationFunction((m_layer[layerNum][i]->lstm->weightsRecurrent[0].weight)*(m_layer[layerNum][i]->lstm->lstmBiases[0].weight));
							cell *= m_layer[layerNum][i]->lstm->sigmoidFunction((m_layer[layerNum][i]->lstm->weightCell[0].weight*nextLayer[count - 1])*(m_layer[layerNum][i]->lstm->weightsRecurrent[1].weight)*(m_layer[layerNum][i]->lstm->lstmBiases[1].weight));
							cell *= m_layer[layerNum][i]->lstm->sigmoidFunction((m_layer[layerNum][i]->lstm->weightCell[1].weight*nextLayer[count - 1])*(m_layer[layerNum][i]->lstm->weightsRecurrent[2].weight)*(m_layer[layerNum][i]->lstm->lstmBiases[2].weight));
							nextLayerTwo.push_back(m_layer[layerNum][i]->lstm->activationFunction(cell)*m_layer[layerNum][i]->lstm->sigmoidFunction((m_layer[layerNum][i]->lstm->weightCell[2].weight*nextLayer[count - 1])*(m_layer[layerNum][i]->lstm->weightsRecurrent[3].weight)*(m_layer[layerNum][i]->lstm->lstmBiases[3].weight)));
						}
					}

					if (first == true && layerNum == m_layer.size() - 2) {
						first == false;
					} else {
						nextLayer.empty();
						nextLayer = nextLayerTwo;
						nextLayerTwo.empty();
					}
				}

				for (unsigned n = 0; n < hiddenLayer.size(); n++) {
					hiddenLayer[n]->ann->calcHiddenGradients(nextLayer);
				}
			}

			//For all layers from outputs to first hidden layer, update connection weights.
			for (unsigned layerNum = m_layer.size() - 1; layerNum > 0; layerNum--) {
				vector<Layer*> &layer = m_layer[layerNum];
				vector<double> prevLayer; //m_layer[layerNum-1]
				vector<double> prevLayerTwo;
				bool first = false;
				int count = 0;

				for (int i = 0; i < m_layer[layerNum].size(); i++) {
					for (int i = 0; i < m_layer[layerNum].size(); i++) {
						if (m_layer[layerNum][i]->_ann == true) {
							for (int j = 0; j < m_layer[layerNum][i]->ann->weightsFoward.size(); j++) {
								if (first == true) {
									prevLayer.push_back(m_layer[layerNum][i]->ann->weightsFoward[j].weight);
								} else {
									prevLayerTwo.push_back(m_layer[layerNum][i]->ann->activationFunction(prevLayer[i] * m_layer[layerNum][i]->ann->weightsFoward[j].weight));
								}
							}
						} else if (m_layer[layerNum + 1][i]->_rnn == true) {
							if (first == true) {
								prevLayer.push_back(m_layer[layerNum][i]->rnn->weightsFoward[0].weight*m_layer[layerNum][i]->rnn->weightsRecurrent[0].weight);
							} else {
								prevLayerTwo.push_back(m_layer[layerNum][i]->rnn->activationFunction(m_layer[layerNum][i]->rnn->weightsFoward[0].weight*m_layer[layerNum][i]->rnn->weightsRecurrent[0].weight));
							}
						} else if (m_layer[layerNum + 1][i]->_lstm == true) {
							double cell;
							if (first == true) {
								cell = m_layer[layerNum][i]->lstm->activationFunction((m_layer[layerNum][i]->lstm->weightsRecurrent[0].weight)*(m_layer[layerNum][i]->lstm->lstmBiases[0].weight));
								cell *= m_layer[layerNum][i]->lstm->sigmoidFunction((m_layer[layerNum][i]->lstm->weightCell[0].weight)*(m_layer[layerNum][i]->lstm->weightsRecurrent[1].weight)*(m_layer[layerNum][i]->lstm->lstmBiases[1].weight));
								cell *= m_layer[layerNum][i]->lstm->sigmoidFunction((m_layer[layerNum][i]->lstm->weightCell[1].weight)*(m_layer[layerNum][i]->lstm->weightsRecurrent[2].weight)*(m_layer[layerNum][i]->lstm->lstmBiases[2].weight));
								prevLayer.push_back(m_layer[layerNum][i]->lstm->activationFunction(cell)*m_layer[layerNum][i]->lstm->sigmoidFunction((m_layer[layerNum][i]->lstm->weightCell[2].weight)*(m_layer[layerNum][i]->lstm->weightsRecurrent[3].weight)*(m_layer[layerNum][i]->lstm->lstmBiases[3].weight)));
								count += 1;
							} else {
								cell = m_layer[layerNum][i]->lstm->activationFunction((m_layer[layerNum][i]->lstm->weightsRecurrent[0].weight)*(m_layer[layerNum][i]->lstm->lstmBiases[0].weight));
								cell *= m_layer[layerNum][i]->lstm->sigmoidFunction((m_layer[layerNum][i]->lstm->weightCell[0].weight*prevLayer[count - 1])*(m_layer[layerNum][i]->lstm->weightsRecurrent[1].weight)*(m_layer[layerNum][i]->lstm->lstmBiases[1].weight));
								cell *= m_layer[layerNum][i]->lstm->sigmoidFunction((m_layer[layerNum][i]->lstm->weightCell[1].weight*prevLayer[count - 1])*(m_layer[layerNum][i]->lstm->weightsRecurrent[2].weight)*(m_layer[layerNum][i]->lstm->lstmBiases[2].weight));
								prevLayerTwo.push_back(m_layer[layerNum][i]->lstm->activationFunction(cell)*m_layer[layerNum][i]->lstm->sigmoidFunction((m_layer[layerNum][i]->lstm->weightCell[2].weight*prevLayer[count - 1])*(m_layer[layerNum][i]->lstm->weightsRecurrent[3].weight)*(m_layer[layerNum][i]->lstm->lstmBiases[3].weight)));
							}
						}

						if (first == true && layerNum == m_layer.size() - 2) {
							first == false;
						} else {
							prevLayer.empty();
							prevLayer = prevLayerTwo;
							prevLayerTwo.empty();
						}
					}

					vector<double> deltaWeights;
					vector<double> weights;
					for (unsigned n = 0; n < layer.size() - 1; n++) {
						if (layer[n]->_ann == true) {
							deltaWeights = layer[n]->ann->updateInputWeights(prevLayer, 0);
							weights = layer[n]->ann->updateInputWeights(prevLayer, 1);

							for (int i = 0; i < deltaWeights.size(); i++) {
								layer[n]->ann->weightsFoward[i].deltaWeight = deltaWeights[i];
								layer[n]->ann->weightsFoward[i].weight = weights[i];
							}
						} else if (layer[n]->_rnn == true) {
							deltaWeights = layer[n]->rnn->updateInputWeights(prevLayer, 0);
							weights = layer[n]->rnn->updateInputWeights(prevLayer, 1);

							for (int i = 0; i < deltaWeights.size(); i++) {
								layer[n]->rnn->weightsFoward[i].deltaWeight = deltaWeights[i];
								layer[n]->rnn->weightsFoward[i].weight = weights[i];
							}
						} else if (layer[n]->_lstm == true) {
							deltaWeights = layer[n]->lstm->updateInputWeights(prevLayer, 0);
							weights = layer[n]->lstm->updateInputWeights(prevLayer, 1);

							for (int i = 0; i < deltaWeights.size(); i++) {
								layer[n]->lstm->weightsFoward[i].deltaWeight = deltaWeights[i];
								layer[n]->lstm->weightsFoward[i].weight = weights[i];
							}
						}
					}
				}
			}
		}

		//This sub-program calculates the performance of the weights.
		vector<vector<string>> performance() {
			vector<vector<string>> networkGenome;
			vector<string> layerGenome;
			string weightGenome;

			for (int i = 0; i < m_layer.size(); i++) {
				for (int j = 0; j < m_layer[i].size(); j++) {
					if (m_layer[i][j]->_ann == true) {
						for (int k = 0; k < m_layer[i][j]->ann->weightsFoward.size(); k++) {
							if (to_string(m_layer[i][j]->ann->weightsFoward[k].weight) == ".") {
								weightGenome += "A";
							} else {
								weightGenome += to_string(m_layer[i][j]->ann->weightsFoward[k].weight);
							}
						}
					} else if (m_layer[i][j]->_rnn == true) {
						for (int k = 0; k < m_layer[i][j]->rnn->weightsFoward.size(); k++) {
							if (to_string(m_layer[i][j]->rnn->weightsFoward[k].weight) == ".") {
								weightGenome += "A";
							} else {
								weightGenome += to_string(m_layer[i][j]->rnn->weightsFoward[k].weight);
							}
						}

						for (int k = 0; k < m_layer[i][j]->rnn->weightsRecurrent.size(); k++) {
							if (to_string(m_layer[i][j]->rnn->weightsRecurrent[k].weight) == ".") {
								weightGenome += "A";
							} else {
								weightGenome += to_string(m_layer[i][j]->rnn->weightsRecurrent[k].weight);
							}
						}
					} else if (m_layer[i][j]->_lstm == true) {
						for (int k = 0; k < m_layer[i][j]->lstm->weightsFoward.size(); k++) {
							if (to_string(m_layer[i][j]->lstm->weightsFoward[k].weight) == ".") {
								weightGenome += "A";
							} else {
								weightGenome += to_string(m_layer[i][j]->lstm->weightsFoward[k].weight);
							}
						}

						for (int k = 0; k < m_layer[i][j]->lstm->weightsRecurrent.size(); k++) {
							if (to_string(m_layer[i][j]->lstm->weightsRecurrent[k].weight) == ".") {
								weightGenome += "A";
							} else {
								weightGenome += to_string(m_layer[i][j]->lstm->weightsRecurrent[k].weight);
							}
						}

						for (int k = 0; k < m_layer[i][j]->lstm->weightCell.size(); k++) {
							if (to_string(m_layer[i][j]->lstm->weightCell[k].weight) == ".") {
								weightGenome += "A";
							} else {
								weightGenome += to_string(m_layer[i][j]->lstm->weightCell[k].weight);
							}
						}
					}
					layerGenome.push_back(weightGenome);
				}
				networkGenome.push_back(layerGenome);
			}

			return networkGenome;
		}

		vector<double> output;
		vector<vector<Layer*>> m_layer;
};