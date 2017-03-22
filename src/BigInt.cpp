#include "BigInt.hpp"

#include <cstdlib>
#include <cctype>
#include <exception>

#include <iostream>

static void make_equal_length(std::string &str1, std::string &str2)
{
	const int delta_size = str1.size() - str2.size();

	if (delta_size > 0)
		str2.insert(0, delta_size, '0');
	else
		str1.insert(0, -delta_size, '0');
}

inline static int char_to_int(char c)
{
	if (c < '0' || c > '9')
		throw std::runtime_error("char_to_int() received a non-digit character");

	return c - '0';
}

inline static char int_to_char(int i)
{
	if (i < 0 || i > 9)
		throw std::runtime_error("int_to_char() received a non-digit number");

	return i + '0';
}


BigInt::BigInt() :
	number("0"), is_negative(false)
{}

BigInt::BigInt(const std::string &str)
{
	if (str == "")
	{
		number = "0";
		is_negative = false;
		return;
	}
	else if (str.at(0) == '-')
	{
		number = str.substr(1);
		is_negative = true;
	}
	else
	{
		number = str;
		is_negative = false;
	}

	size_t zero_len = number.find_first_not_of('0');

	if (zero_len == std::string::npos)
	{
		number = "0";
		is_negative = false;
	}
	else if (zero_len > 0)
	{
		number.erase(0, zero_len);

		for (size_t i = 0; i < number.size(); i++)
		{
			if (!isdigit(number.at(i)))
				throw std::runtime_error("BigInt constructor called with an invalid string");
		}
	}
}

BigInt::BigInt(const BigInt &num) :
	number(num.number), is_negative(num.is_negative)
{}

BigInt operator+(const BigInt &lhs, const BigInt &rhs)
{
	if (lhs.is_negative)
	{
		if (!rhs.is_negative)
			return rhs - (-lhs);
		else
			return -((-lhs) + (-rhs));
	}
	else if (rhs.is_negative)
		return lhs - (-rhs);
	else
	{
		std::string new_lhs = lhs.number, new_rhs = rhs.number, result = "";
		make_equal_length(new_lhs, new_rhs);

		int carry = 0;
		for (int i = new_lhs.size() - 1; i >= 0; i--)
		{
			int digit_sum = char_to_int(new_lhs.at(i)) + char_to_int(new_rhs.at(i)) + carry;
			if (digit_sum >= 10)
			{
				digit_sum -= 10;
				carry = 1;
			}
			else
				carry = 0;

			result.insert(result.begin(), int_to_char(digit_sum));
		}

		if (carry)
			result.insert(result.begin(), '1');

		return BigInt(result);
	}
}

BigInt& BigInt::operator+=(const BigInt &rhs)
{
	*this = *this + rhs;
	return *this;
}

BigInt operator-(const BigInt &lhs, const BigInt &rhs)
{
	if (lhs.is_negative)
	{
		if (!rhs.is_negative)
			return -(-lhs + rhs);
		else
			return (-rhs) - (-lhs);
	}
	else if (rhs.is_negative)
		return lhs + (-rhs);
	else
	{
		if (lhs < rhs)
			return -(rhs - lhs);

		std::string new_lhs = lhs.number, new_rhs = rhs.number, result = "";
		make_equal_length(new_lhs, new_rhs);

		int carry = 0;
		for (int i = new_lhs.size() - 1; i >= 0; i--)
		{
			int digit_difference = char_to_int(new_lhs[i]) - char_to_int(new_rhs[i]) - carry;

			if (digit_difference < 0)
			{
				digit_difference += 10;
				carry = 1;
			}
			else
				carry = 0;

			result.insert(result.begin(), int_to_char(digit_difference));
		}

		return BigInt(result);
	}
}

BigInt& BigInt::operator-=(const BigInt & rhs)
{
	*this = *this - rhs;
	return *this;
}

BigInt BigInt::operator-() const
{
	BigInt result(*this);
	result.is_negative = !result.is_negative;

	return result;
}

BigInt& operator*(const BigInt &lhs, const BigInt &rhs)
{
	if (lhs.is_negative)
		if (!rhs.is_negative)
			return -((-lhs) * rhs);
		else
			return (-lhs) * (-rhs);
	else if (rhs.is_negative)
		return -(lhs * (-rhs));
	else
	{
		BigInt result;
		
		for (int i = rhs.number.size() - 1; i >= 0; i--)
		{
			std::string intermediate(rhs.number.size() - 1 - i, '0');
			int carry = 0;
			for (int j = lhs.number.size() - 1; j >= 0; j--)
			{
				int digit_mul = char_to_int(lhs.number[j]) * char_to_int(rhs.number[i]) + carry;
				
				if (digit_mul > 9)
				{
					carry = digit_mul / 10;
					digit_mul %= 10;
				}
				else
					carry = 0;
				
				intermediate.insert(intermediate.begin(), int_to_char(digit_mul));
			}
			
			if (carry)
				intermediate.insert(intermediate.begin(), int_to_char(carry));
			
			BigInt intermediate_num(intermediate);
			
			result += intermediate_num;
		}
		
		return result;
	}
}

bool operator>(const BigInt &lhs, const BigInt &rhs)
{
	if (lhs.is_negative && !rhs.is_negative)
	{
		return false;
	}
	else if (!lhs.is_negative && rhs.is_negative)
	{
		return true;
	}
	else if (lhs.is_negative && rhs.is_negative)
	{
		return -lhs < -rhs;
	}
	else
	{
		std::string new_lhs = lhs.number, new_rhs = rhs.number;
		make_equal_length(new_lhs, new_rhs);

		for (size_t i = 0; i < new_lhs.size(); i++)
		{
			if (char_to_int(new_lhs[i]) > char_to_int(new_rhs[i]))
				return true;
			else if (char_to_int(new_lhs[i]) < char_to_int(new_rhs[i]))
				return false;
		}

		return false;
	}
}

bool operator<(const BigInt &lhs, const BigInt &rhs)
{
	if (lhs.is_negative && !rhs.is_negative)
	{
		return true;
	}
	else if (!lhs.is_negative && rhs.is_negative)
	{
		return false;
	}
	else if (lhs.is_negative && rhs.is_negative)
	{
		return -lhs > -rhs;
	}
	else
	{
		std::string new_lhs = lhs.number, new_rhs = rhs.number;
		make_equal_length(new_lhs, new_rhs);

		for (size_t i = 0; i < new_lhs.size(); i++)
		{
			if (char_to_int(new_lhs[i]) < char_to_int(new_rhs[i]))
				return true;
			else if (char_to_int(new_lhs[i]) > char_to_int(new_rhs[i]))
				return false;
		}

		return false;
	}
}

bool operator==(const BigInt &lhs, const BigInt &rhs)
{
	return (lhs.is_negative == rhs.is_negative) && (lhs.number == rhs.number);
}

std::ostream& operator<<(std::ostream& os, const BigInt& num)
{
	return os << (num.is_negative ? "-" : "") << num.number;
}

