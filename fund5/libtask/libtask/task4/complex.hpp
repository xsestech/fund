/**
 * @file
 * @brief
 * @details
 * @author xsestech 
 * @date 09.12.2024
 */
#pragma once
#include <cmath>
#include <stdexcept>

namespace task {
class Complex {
  public:
    explicit Complex(double real = 0, double imaginary = 0): real_(real),
      im_(imaginary) {
    }
    Complex(Complex& other) = default;
    Complex(Complex&& other) = default;

    Complex& operator=(const Complex& other) = default;
    Complex& operator=(Complex&& other) = default;

    void Add(const Complex& other);
    void Subtract(const Complex& other);
    void Multiply(const Complex& other);
    void Divide(const Complex& other);
    double Modulo() const;
    double Arg() const;

    double get_real() const;
    double get_imaginary() const;

  private:
    double real_;
    double im_;
};
} // namespace task