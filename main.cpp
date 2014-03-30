#include "board.h"
#include <iostream>
#include "utils.h"

int main()
{
	Board b(0);
	for(int i = 0; i < 10; ++i)
		std::cout << randInt(10) << std::endl;

	for(int i = 0; i < 10; ++i)
		std::cout << randFloat(1) << std::endl;
}