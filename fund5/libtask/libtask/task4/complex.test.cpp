/**
 * @file
 * @brief
 * @details
 * @author xsestech 
 * @date 12.12.2024
 */
#include <gtest/gtest.h>
#include "complex.hpp"
#include <complex>
#include <cmath>
#include <stdexcept>

namespace task {
using std::complex;

TEST(ComplexTest, Addition) {
  Complex a(1.0, 2.0);
  Complex b(3.0, 4.0);
  a.Add(b);
  complex<double> a_std(1.0, 2.0);
  complex<double> b_std(3.0, 4.0);
  a_std += b_std;
  EXPECT_DOUBLE_EQ(a.get_real(), a_std.real());
  EXPECT_DOUBLE_EQ(a.get_imaginary(), a_std.imag());

  // Test adding zero
  Complex c(0.0, 0.0);
  Complex d(5.0, 6.0);
  d.Add(c);
  complex<double> d_std(5.0, 6.0);
  d_std += complex<double>(0.0, 0.0);
  EXPECT_DOUBLE_EQ(d.get_real(), d_std.real());
  EXPECT_DOUBLE_EQ(d.get_imaginary(), d_std.imag());
}

TEST(ComplexTest, Subtraction) {
  Complex a(1.0, 2.0);
  Complex b(3.0, 4.0);
  a.Subtract(b);
  complex<double> a_std(1.0, 2.0);
  complex<double> b_std(3.0, 4.0);
  a_std -= b_std;
  EXPECT_DOUBLE_EQ(a.get_real(), a_std.real());
  EXPECT_DOUBLE_EQ(a.get_imaginary(), a_std.imag());

  // Test subtracting zero
  Complex c(0.0, 0.0);
  Complex d(5.0, 6.0);
  d.Subtract(c);
  complex<double> d_std(5.0, 6.0);
  d_std -= complex<double>(0.0, 0.0);
  EXPECT_DOUBLE_EQ(d.get_real(), d_std.real());
  EXPECT_DOUBLE_EQ(d.get_imaginary(), d_std.imag());
}

TEST(ComplexTest, Multiplication) {
  Complex a(1.0, 2.0);
  Complex b(3.0, 4.0);
  a.Multiply(b);
  complex<double> a_std(1.0, 2.0);
  complex<double> b_std(3.0, 4.0);
  a_std *= b_std;
  EXPECT_DOUBLE_EQ(a.get_real(), a_std.real());
  EXPECT_DOUBLE_EQ(a.get_imaginary(), a_std.imag());

  // Test multiplying by zero
  Complex c(0.0, 0.0);
  Complex d(5.0, 6.0);
  d.Multiply(c);
  complex<double> d_std(5.0, 6.0);
  d_std *= complex<double>(0.0, 0.0);
  EXPECT_DOUBLE_EQ(d.get_real(), d_std.real());
  EXPECT_DOUBLE_EQ(d.get_imaginary(), d_std.imag());

  // Test multiplying by one
  Complex e(1.0, 0.0);
  Complex f(5.0, 6.0);
  f.Multiply(e);
  complex<double> f_std(5.0, 6.0);
  f_std *= complex<double>(1.0, 0.0);
  EXPECT_DOUBLE_EQ(f.get_real(), f_std.real());
  EXPECT_DOUBLE_EQ(f.get_imaginary(), f_std.imag());
}

TEST(ComplexTest, Division) {
  Complex a(1.0, 2.0);
  Complex b(3.0, 4.0);
  a.Divide(b);
  complex<double> a_std(1.0, 2.0);
  complex<double> b_std(3.0, 4.0);
  a_std /= b_std;
  EXPECT_DOUBLE_EQ(a.get_real(), a_std.real());
  EXPECT_DOUBLE_EQ(a.get_imaginary(), a_std.imag());

  // Test dividing by one
  Complex c(1.0, 0.0);
  Complex d(5.0, 6.0);
  d.Divide(c);
  complex<double> d_std(5.0, 6.0);
  d_std /= complex<double>(1.0, 0.0);
  EXPECT_DOUBLE_EQ(d.get_real(), d_std.real());
  EXPECT_DOUBLE_EQ(d.get_imaginary(), d_std.imag());

  // Test dividing by zero (should throw an exception)
  Complex e(1.0, 2.0);
  Complex zero(0.0, 0.0);
  EXPECT_THROW(e.Divide(zero), std::domain_error);
}

TEST(ComplexTest, Modulo) {
  Complex a(3.0, 4.0);
  double mod = a.Modulo();
  complex<double> a_std(3.0, 4.0);
  EXPECT_DOUBLE_EQ(mod, std::abs(a_std));

  // Test modulo of zero
  Complex b(0.0, 0.0);
  mod = b.Modulo();
  EXPECT_DOUBLE_EQ(mod, 0.0);

  // Test with negative real and imaginary
  Complex c(-1.0, -1.0);
  mod = c.Modulo();
  EXPECT_DOUBLE_EQ(mod, sqrt(2.0));
}

TEST(ComplexTest, Arg) {
  Complex a(1.0, 1.0);
  double arg = a.Arg();
  complex<double> a_std(1.0, 1.0);
  EXPECT_DOUBLE_EQ(arg, std::arg(a_std));

  // Test argument of positive real
  Complex b(1.0, 0.0);
  arg = b.Arg();
  EXPECT_DOUBLE_EQ(arg, 0.0);

  // Test argument of negative real
  Complex c(-1.0, 0.0);
  arg = c.Arg();
  EXPECT_DOUBLE_EQ(arg, M_PI);

  // Test argument of positive imaginary
  Complex d(0.0, 1.0);
  arg = d.Arg();
  EXPECT_DOUBLE_EQ(arg, M_PI_2);

  // Test argument of negative imaginary
  Complex e(0.0, -1.0);
  arg = e.Arg();
  EXPECT_DOUBLE_EQ(arg, -M_PI_2);
  Complex k(0.0, 0.0);
  EXPECT_THROW(k.Arg(), std::domain_error);
}

TEST(ComplexTest, ConstructorsAndAssignment) {
  // Default constructor
  Complex a;
  EXPECT_DOUBLE_EQ(a.get_real(), 0.0);
  EXPECT_DOUBLE_EQ(a.get_imaginary(), 0.0);

  // Single-argument constructor
  Complex b(5.0);
  EXPECT_DOUBLE_EQ(b.get_real(), 5.0);
  EXPECT_DOUBLE_EQ(b.get_imaginary(), 0.0);

  // Copy constructor
  Complex c(1.0, 2.0);
  Complex d(c);
  EXPECT_DOUBLE_EQ(d.get_real(), 1.0);
  EXPECT_DOUBLE_EQ(d.get_imaginary(), 2.0);

  // Assignment operator
  Complex e(3.0, 4.0);
  Complex f(5.0, 6.0);
  f = e;
  EXPECT_DOUBLE_EQ(f.get_real(), 3.0);
  EXPECT_DOUBLE_EQ(f.get_imaginary(), 4.0);
}
}
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
