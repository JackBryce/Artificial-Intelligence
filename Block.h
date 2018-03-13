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
		void feedFoward(const Layer &prevLayer);
		void calcOutputGradients(double targetVal);
		void calcHiddenGradients(const Layer &nextLayer);
		void updateInputWeights(Layer &prevLayer);
		static double randomWeight(void) { return rand() / double(RAND_MAX); }
		vector<Connection> weightsFoward;
		vector<Connection> weightsRecurrent;
		vector<Connection> lstmBiases;
		vector<Connection> weightCell;

	private:
		static double eta;
		static double alpha;
		static double transferFunction(double x);
		static double transferFunctionDerivative(double x);
		double sumDOW(const Layer &nextLayer) const;
		double outputFoward;
		unsigned m_myIndex;
		double m_gradient;
};