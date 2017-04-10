#ifndef BIGINT_HPP
#define BIGINT_HPP

#include <string>
#include <ostream>

class BigInt
{
public:
	BigInt();
	BigInt(const int num);
	BigInt(const std::string &str);
	BigInt(const BigInt &num);

	friend BigInt abs(const BigInt &lhs);

	friend BigInt operator+(const BigInt &lhs, const BigInt& rhs);
	BigInt& operator+=(const BigInt &rhs);

	friend BigInt operator-(const BigInt &lhs, const BigInt& rhs);
	BigInt& operator-=(const BigInt &rhs);
	BigInt operator-() const;

	friend BigInt operator*(const BigInt &lhs, const BigInt &rhs);
	BigInt& operator*=(const BigInt &rhs);

	friend BigInt operator^(const BigInt &lhs, const BigInt &rhs); // power
	BigInt operator^=(const BigInt &rhs);

	friend BigInt operator/(const BigInt &lhs, const BigInt &rhs);
	BigInt& operator/=(const BigInt &rhs);

	friend bool operator>(const BigInt &lhs, const BigInt& rhs);
	friend bool operator>=(const BigInt &lhs, const BigInt& rhs);
	friend bool operator<(const BigInt &lhs, const BigInt& rhs);
	friend bool operator<=(const BigInt &lhs, const BigInt& rhs);
	friend bool operator==(const BigInt &lhs, const BigInt& rhs);
	friend bool operator!=(const BigInt &lhs, const BigInt& rhs);

	friend std::ostream& operator<<(std::ostream& os, const BigInt &num);

private:
	std::string number;
	bool is_negative;
};

#endif //BIGINT_HPP
