#include "board.h"
#include <iostream>
#include "utils.h"
#include "NeuralNet/neuralnet.h"

int main()
{
	Board b;
	NeuralNet net;


	std::cout << b << std::endl;

	Board pb = b;

	do
	{
		std::cin.ignore();
		
		std::vector<int> outputs = net.Update(b.GetValues());

		int dir = outputs[1] * 2 + outputs[0];
		pb = b;
		b.turn(dir);

		std::cout << dir << std::endl;
		std::cout << b << std::endl;
	}
	while(!b.complete() && pb != b);

	std::cout << "Complete!" << std::endl;

}
