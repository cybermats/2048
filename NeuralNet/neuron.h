#include <vector>

class Neuron
{
public:
	Neuron(int numInputs);
private:
	int m_numInputs;
	std::vector<double> m_weights;
	
};