#include <vector>
#include "../utils.h"

class Neuron
{
public:
	Neuron(int numInputs)
	: m_numInputs(numInputs)
	{
		for(int i = 0; i < m_numInputs + 1; ++i)
			m_weights.push_back(randFloat(-1, 1));
	}

	std::vector<double> getWeights() const
	{
		return m_weights;
	}

	std::vector<double>::iterator begin() { return m_weights.begin(); }
	std::vector<double>::iterator end() { return m_weights.end(); }

private:
	int m_numInputs;
	std::vector<double> m_weights;
	
};