#include <iostream>
#include <windows.h>

#include "BigInt.hpp"

int main()
{
	try
	{
		BigInt i(16);
		BigInt j(32);

		i *= j;

		std::cout << i << std::endl;
	}
	catch (const std::exception& ex)
	{
		std::cerr << ex.what() << std::endl;
	}

	return 0;
}
