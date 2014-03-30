#include <vector>
#include "neuron.h"

class NeuronLayer
{
public:
	NeuronLayer(int numNeurons, int numInputsPerNeuron)
	: m_numNeurons(numNeurons)
	{
		for(int i = 0; i < m_numNeurons; ++i)
			m_neurons.push_back(Neuron(numInputsPerNeuron));
	}

	std::vector<Neuron>::iterator begin() { return m_neurons.begin(); }
	std::vector<Neuron>::iterator end() { return m_neurons.end(); }

private:
	int m_numNeurons;
	std::vector<Neuron> m_neurons;
};