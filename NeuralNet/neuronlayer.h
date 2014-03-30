#include <vector>
#include "neuron.h"

class NeuronLayer
{
public:
	NeuronLayer(int numNeurons, int numInputesPerNeuron);
private:
	int m_numNeurons;
	std::vector<Neuron> m_neurons;
};