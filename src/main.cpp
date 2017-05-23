#include <iostream>

#include "BigInt.hpp"

int main()
{
	try
	{
		BigInt pi;

        int iterations;

		std::cout << "Enter number of iterations:" << std::endl;
		std::cin >> iterations;

		int power;
		std::cout << "Enter desired power to raise 10 to:" << std::endl;
		std::cin >> power;

		BigInt multiplier(10);
		multiplier ^= power;

		BigInt i(iterations);

		for (; i > 0; i -= 1)
		{
            BigInt pi_part(multiplier * (fact(i)^2) * (BigInt(2)^(i + 1)) / fact(2 * i + 1));
            std::cout << "pi_part["<<i<<"]: " << pi_part << std::endl;
            pi += pi_part;
		}

        std::string &str = pi.get_string_repr_ref();
        str[0] = '3';
        str.insert(1, ".", 1);

	}
	catch (const std::exception& ex)
	{
		std::cerr << ex.what() << std::endl;
	}

	return 0;
}
