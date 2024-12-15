/**
* @file
 * @brief
 * @details
 * @author xsestech
 * @date 23.11.2024
 */

#include <libtask/task1/binary_int.hpp>

namespace task {

void BinaryInt::Increment() {
  int carry = 1;
  while (carry) {
    int temp = value_ & carry;
    value_ ^= carry;
    carry = temp << 1;
  }
}

void BinaryInt::Decrement() {
  int borrow = 1;
  while (borrow) {
    int temp = (~value_) & borrow;
    value_ ^= borrow;
    borrow = temp << 1;
  }
}
void BinaryInt::Add(const BinaryInt &other) {
  int b = other.value_;
  while (b != 0) {
    int carry = value_ & b;
    value_ ^= b;
    b = carry << 1;
  }
}
void BinaryInt::Subtract(const BinaryInt &other) {
  Add(-other); // Our operator is used here
}

void BinaryInt::Multiply(const task::BinaryInt &other) {
  BinaryInt result(0);
  BinaryInt multiplicand = AbsoluteValue(*this);
  BinaryInt multiplier = AbsoluteValue(other);
  bool result_negative = (value_ < 0) ^ (other.value_ < 0);

  while (multiplier.value_ != 0) {
    if (multiplier.value_ & 1) {
      result.Add(multiplicand);
    }
    multiplicand.value_ <<= 1;
    multiplier.value_ >>= 1;
  }

  if (result_negative) {
    result = -result;
  }
  *this =  result;
}

BinaryInt BinaryInt::AbsoluteValue(const BinaryInt &bin) {
  return (bin.value_ < 0) ? -bin : bin;
}
BinaryInt BinaryInt::operator-() const {
  BinaryInt result;
  // Two's complement shit
  result.value_ = ~value_;  // Invert all bits.
  result.Increment();       // Add 1 to get the two's complement.
  return result;
}

BinaryInt &BinaryInt::operator++() {
  Increment();
  return *this;
}

BinaryInt BinaryInt::operator++(int) {
  BinaryInt temp(*this);
  Increment();
  return temp;
}
BinaryInt BinaryInt::operator+(const BinaryInt &other) const {
  BinaryInt result(*this);
  result.Add(other);
  return result;
}

BinaryInt BinaryInt::operator-(const BinaryInt &other) const {
  BinaryInt result(*this);
  result.Subtract(other);
  return result;
}
BinaryInt &BinaryInt::operator--() {
  Decrement();
  return *this;
}
BinaryInt BinaryInt::operator--(int) {
  BinaryInt temp(*this);
  Decrement();
  return temp;
}

BinaryInt BinaryInt::operator*(const BinaryInt &other) const {
  BinaryInt result(*this);
  result.Multiply(other);
  return result;
}
BinaryInt& BinaryInt::operator<<=(int shift) {
  value_ <<= shift;
  return *this;
}

BinaryInt& BinaryInt::operator>>=(int shift) {
  value_ >>= shift;
  return *this;
}
BinaryInt& BinaryInt::operator+=(const BinaryInt &other) & {
  Add(other);
  return *this;
}

BinaryInt& BinaryInt::operator-=(const BinaryInt &other) & {
  Subtract(other);
  return *this;
}

BinaryInt& BinaryInt::operator*=(const BinaryInt &other) & {
  Multiply(other);
  return *this;
}

std::pair<BinaryInt, BinaryInt> BinaryInt::splitInHalf() const {
  const int low_mask = 0x0000FFFF;
  const int high_mash = 0xFFFF0000;
  return {BinaryInt(value_ & high_mash), BinaryInt(value_ & low_mask)};
}
std::ostream &operator<<(std::ostream &os, const BinaryInt &binary_int) {
  os << std::bitset<32>(binary_int.value_);
  return os;
}

int BinaryInt::get_value() {
  return value_;
}

}

