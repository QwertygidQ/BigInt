#ifndef BIGINT_HPP
#define BIGINT_HPP

#include <string>
#include <ostream>
#include <utility>

class BigInt
{
public:
	BigInt();
	BigInt(const int num);
	BigInt(const std::string &str);
	BigInt(const BigInt &num);

	friend BigInt abs(const BigInt &lhs);
	friend BigInt fact(const BigInt &lhs);
	friend BigInt twos_complement_subtraction(const BigInt &lhs, const BigInt &rhs);

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

    friend BigInt operator%(const BigInt &lhs, const BigInt &rhs);
    BigInt& operator%=(const BigInt &rhs);

	friend bool operator>(const BigInt &lhs, const BigInt& rhs);
	friend bool operator>=(const BigInt &lhs, const BigInt& rhs);
	friend bool operator<(const BigInt &lhs, const BigInt& rhs);
	friend bool operator<=(const BigInt &lhs, const BigInt& rhs);
	friend bool operator==(const BigInt &lhs, const BigInt& rhs);
	friend bool operator!=(const BigInt &lhs, const BigInt& rhs);

	friend std::ostream& operator<<(std::ostream& os, const BigInt &num);

	std::string& get_string_repr_ref();

private:
    friend std::pair<BigInt, BigInt> division(const BigInt &lhs, const BigInt& rhs); // first - quotient; second - remainder
    inline void fix_negative_zero();
    void fix_trailing_zeroes();
    friend BigInt twos_complement(const BigInt &lhs, const size_t digits_num);
    void to_normal_from_twos_complement();


	std::string number;
	bool is_negative;
};

#endif //BIGINT_HPP
