#include "neuralnet.h"
#include <assert.h>

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

void NeuralNet::PutWeights(std::vector<double>& weights)
{
	auto wit = weights.begin();
	for(auto & layer : m_layers)
	{
		for(auto & neuron : layer)
		{
			for(auto & weight : neuron)
			{
				assert(wit != weights.end());
				weight = *(wit++);
			}
		}
	}
}

std::vector<int> NeuralNet::Update(std::vector<int> inputs)
{
	std::vector<int> outputs;
	assert(inputs.size() == m_numInputs);
	bool firstLayer = true;

	for(auto & layer : m_layers)
	{
		if(!firstLayer)
			inputs = outputs;
		else
			firstLayer = false;

		outputs.clear();


		for(auto & neuron : layer)
		{
			double netInput = 0.0;

			auto w_it = neuron.begin();
			auto i_it = inputs.begin();
			while(i_it != inputs.end())
			{
				netInput += (*w_it++) * (*i_it++);
			}

			netInput -= *w_it;

			int value = 0;
			if(netInput > 0)
				value = 1;
			outputs.push_back(value);
		}
	}
	return outputs;
}
