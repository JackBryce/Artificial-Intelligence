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
		void feedFoward(const vector<double> &prevLayer);
		void calcOutputGradients(double targetVal) {
			double delta = targetVal - outputFoward;
			m_gradient = delta * transferFunctionDerivative(outputFoward);
		}
		void calcHiddenGradients(const vector<double> &nextLayer);
		void updateInputWeights(vector<double> &prevLayer);
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
		double sumDOW(const vector<double> &nextLayer) const;
		double outputFoward;
		unsigned m_myIndex;
		double m_gradient;
};