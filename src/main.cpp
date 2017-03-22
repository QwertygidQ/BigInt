#include <iostream>

#include "BigInt.hpp"

int main()
{
	try
	{
		BigInt i("36");
		BigInt j("730");

		std::cout << i * j;

		std::cout << i << std::endl;
	}
	catch (const std::exception& ex)
	{
		std::cerr << ex.what() << std::endl;
	}

	return 0;
}