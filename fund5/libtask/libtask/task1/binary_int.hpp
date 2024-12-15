#pragma once

#include <iostream>

namespace task {

class BinaryInt {
 public:
  explicit BinaryInt(int value = 0) : value_(value) {};
  BinaryInt(const BinaryInt &other) = default; // Copy constructor
  BinaryInt(BinaryInt &&other) = default; // Move constructor
  BinaryInt &operator=(const BinaryInt &other) = default; // Copy operator
  BinaryInt &operator=(BinaryInt &&other) noexcept = default; // Move operator
  ~BinaryInt() = default; // Destructor

  BinaryInt operator-() const; // Unary - minus
  BinaryInt operator+(const BinaryInt &other) const;
  BinaryInt operator-(const BinaryInt &other) const;
  BinaryInt operator*(const BinaryInt &other) const;
  BinaryInt operator--(int);
  BinaryInt& operator--();
  BinaryInt& operator++();
  BinaryInt operator++(int);
  BinaryInt& operator+=(const BinaryInt &other) &;
  BinaryInt& operator-=(const BinaryInt &other) &;
  BinaryInt& operator*=(const BinaryInt &other) &;
  BinaryInt& operator>>=(int shift);
  BinaryInt& operator<<=(int shift);

  friend std::ostream &operator<<(std::ostream &os, const BinaryInt &binary_int);

  std::pair<BinaryInt, BinaryInt> splitInHalf() const;

  int get_value();



 private:
  int value_;
  void Increment();
  void Decrement();
  void Multiply(const BinaryInt& other);
  void Subtract(const BinaryInt& other);
  void Add(const BinaryInt& other);
  static BinaryInt AbsoluteValue(const BinaryInt& bin);


};
} // namespace task