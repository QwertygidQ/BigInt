#include <iostream>

#include "BigInt.hpp"

int main()
{
	try
	{
		BigInt i = 2;
		BigInt j = 1;

		//int k = i;

		std::cout << (i ^ j) << std::endl;
	}
	catch (const std::exception& ex)
	{
		std::cerr << ex.what() << std::endl;
	}

	return 0;
}
