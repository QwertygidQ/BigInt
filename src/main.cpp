#include <iostream>

#include "BigInt.hpp"

int main()
{
	try
	{
		BigInt i = 6;
		BigInt j = -4;

		/*std::cout << (i + j) << std::endl;
		std::cout << (i - j) << std::endl;
		std::cout << (i * j) << std::endl;
		std::cout << (j / i) << std::endl;
		std::cout << (j % i) << std::endl;
		std::cout << (BigInt(351) ^ BigInt(3)) << std::endl;
		std::cout << fact(BigInt(8)) << std::endl;*/

		std::cout << twos_complement_subtraction(BigInt(630), BigInt(565)) << std::endl;
	}
	catch (const std::exception& ex)
	{
		std::cerr << ex.what() << std::endl;
	}

	return 0;
}
