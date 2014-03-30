#include "neuralnet.h"

NeuralNet::NeuralNet()
: m_numInputs(16)
, m_numOutputs(2)
, m_numHiddenLayers(2)
, m_numNeuronsPerHiddenLayer(18)
{
	createNet();
}


void NeuralNet::createNet()
{
	if(m_numHiddenLayers > 0)
	{
		m_layers.push_back(NeuronLayer(m_numNeuronsPerHiddenLayer, m_numInputs));
		for(int i = 1; i < m_numHiddenLayers; ++i)
			m_layers.push_back(NeuronLayer(m_numNeuronsPerHiddenLayer, m_numNeuronsPerHiddenLayer));

		m_layers.push_back(NeuronLayer(m_numOutputs, m_numNeuronsPerHiddenLayer));
	}
	else
	{
		m_layers.push_back(NeuronLayer(m_numOutputs, m_numInputs));
	}
}

std::vector<double> NeuralNet::GetWeights() const
{
	std::vector<double> weights;
	for(auto layer : m_layers)
	{
		for(auto neuron : layer)
		{
			auto neuronWeights = neuron.getWeights();
			weights.insert(weights.end(), neuronWeights.begin(), neuronWeights.end());
		}
	}
	return weights;

}