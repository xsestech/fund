/**
 * @file
 * @brief
 * @details
 * @author xsestech 
 * @date 09.12.2024
 */


#include <libtask/task4/complex.hpp>

namespace task {
void Complex::Add(const Complex& other) {
  im_ += other.im_;
  real_ += other.real_;
}

void Complex::Subtract(const Complex& other) {
  im_ -= other.im_;
  real_ -= other.real_;
}

void Complex::Multiply(const Complex& other) {
  double const new_im_ = real_ * other.im_ + im_ * other.real_;
  double const new_real_ = real_ * other.real_ - im_ * other.im_;
  real_ = new_real_;
  im_ = new_im_;
}

void Complex::Divide(const Complex& other) {
  const double denominator = pow(other.real_, 2) + pow(other.im_, 2);
  if (denominator == 0.0) {
    throw std::domain_error("Division by zero");
  }
  double const new_real_ = (real_ * other.real_ + im_ * other.im_) / (denominator);
  double const new_im_ = (im_ * other.real_ - real_ * other.im_) / (
                 denominator);
  real_ = new_real_;
  im_ = new_im_;
}
double Complex::Modulo() const {
  return sqrt(pow(real_, 2) + pow(im_, 2));
}

double Complex::Arg() const {
  if (real_ == 0 && im_ == 0) {
    throw std::domain_error("Can't get argument for zero complex number");
  }
  return atan2(im_, real_);
}
double Complex::get_real() const{
  return real_;
}
double Complex::get_imaginary() const{
  return im_;
}

} // namespace task