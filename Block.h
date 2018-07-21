#pragma once
#include <vector>;

using namespace std;

struct Connection {
	double deltaWeight;
	double weight;
};

class Block {
	public:
		void setOutputVal(double val) { outputFoward = val; }
		double getOutputVal(void) const { return outputFoward; };

		//This sub-program feeds the previous layer into the next layer.
		void feedFoward(const vector<double> &prevLayer) {
			double sum = 0.0;

			for (unsigned i = 0; i < prevLayer.size(); i++) {
				sum += prevLayer[i] * weightsFoward[m_myIndex].weight;
			}

			outputFoward = transferFunction(sum);
		}

		void calcOutputGradients(double targetVal) {
			double delta = targetVal - outputFoward;
			m_gradient = delta * transferFunctionDerivative(outputFoward);
		}

		//This sub-program calculates the gradients.
		void calcHiddenGradients(const vector<double> &nextLayer) {
			m_gradient = sumDOW(nextLayer) * transferFunctionDerivative(outputFoward);
		}


		/* This sub-program updates the input weights. Val
		   decides wether to return deltaWeight or weight.
		   */
		vector<double> updateInputWeights(vector<double> &prevLayer, int val) {
			vector<double> returning;
			vector<double> deltaWeight;
			vector<double> weight;

			//prevLayer = weightsFoward[m_myIndex]->deltaWeight;
			for (unsigned n = 0; n < prevLayer.size(); n++) {
				double oldDeltaWeight = prevLayer[n];
				double newDeltaWeight = eta * prevLayer[n] * m_gradient + alpha * oldDeltaWeight;

				deltaWeight[n] = newDeltaWeight;
				weight[n] = prevLayer[n] + newDeltaWeight;
			}

			if (val == 0) {
				returning = deltaWeight;
			} else {
				returning = weight;
			}

			return returning;
		}

		static double randomWeight(void) { return rand() / double(RAND_MAX); }
		vector<Connection> weightsFoward;
		vector<Connection> weightsRecurrent;
		vector<Connection> lstmBiases;
		vector<Connection> weightCell;

	private:
		const double eta = 0.15;
		const double alpha = 0.5;
		static double transferFunction(double x) { return tanh(x); }
		static double transferFunctionDerivative(double x) { return 1.0 - (tanh(x)*tanh(x)); }

		//This sub-program calculates the sum of the differentiation of the weights.
		double sumDOW(const vector<double> &nextLayer) const {
			double sum = 0.0;

			for (unsigned n = 0; n < nextLayer.size() - 1; n++) {
				sum += weightsFoward[n].weight*nextLayer[n];
			}

			return sum;
		}

		double outputFoward;
		unsigned m_myIndex;
		double m_gradient;
};