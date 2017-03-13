#include <iostream>

#include "BigInt.hpp"

int main()
{
	try
	{
		BigInt i("0");
		BigInt j("-7");

		i -= j;

		std::cout << i << std::endl;
	}
	catch (const std::exception& ex)
	{
		std::cerr << ex.what() << std::endl;
	}

	system("pause");

	return 0;
}