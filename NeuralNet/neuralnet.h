#include <vector>
#include "neuronlayer.h"

class NeuralNet
{
public:
	NeuralNet();
	void createNet();

	std::vector<double> GetWeights() const;
	int GetNumberOfWeights() const;
	void PutWeights(std::vector<double>& weights);
	std::vector<int> Update(std::vector<int> inputs);

private:
	int m_numInputs;
	int m_numOutputs;
	int m_numHiddenLayers;
	int m_numNeuronsPerHiddenLayer;
	std::vector<NeuronLayer> m_layers;
};