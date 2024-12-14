/**
 * @file
 * @brief
 * @details
 * @author xsestech 
 * @date 12.12.2024
 */
#include "vector.hpp"

namespace task {
Vector::Iterator::Iterator(double* ptr): ptr_(ptr) {
}
Vector::Iterator::reference Vector::Iterator::operator*() {
  return *ptr_;
}
Vector::Iterator::reference Vector::Iterator::operator*() const {
  return *ptr_;
}
double& Vector::Back() {
  if (Empty()) {
    throw std::range_error("Can't get back element of emtpy vector");
  }
  return At(GetEndIdx());
}
const double& Vector::Back() const {
  if (Empty()) {
    throw std::range_error("Can't get back element of emtpy vector");
  }
  return At(GetEndIdx());
}
double* Vector::Data() {
  return data_;
}
const double* Vector::Data() const {
  return data_;
}
Vector::Iterator::pointer Vector::Iterator::operator->() const {
  return ptr_;
}
Vector::Iterator& Vector::Iterator::operator++() {
  ++ptr_;
  return *this;
}
Vector::Iterator Vector::Iterator::operator++(int) {
  Iterator temp = *this;
  ++ptr_;
  return temp;
}
Vector::Iterator& Vector::Iterator::operator--() {
  --ptr_;
  return *this;
}
Vector::Iterator Vector::Iterator::operator--(int) {
  Iterator temp = *this;
  --ptr_;
  return temp;
}
Vector::Iterator Vector::Iterator::operator+(const difference_type offset) const {
  if (ptr_ == nullptr) {
    throw std::runtime_error("Can't add numbers to null iterator");
  }
  return Iterator(ptr_ + offset);
}
Vector::Iterator Vector::Iterator::operator-(difference_type offset) const {
  if (ptr_ == nullptr) {
    throw std::runtime_error("Can't add numbers to null iterator");
  }
  return Iterator(ptr_ - offset);
}
Vector::Iterator& Vector::Iterator::operator+=(difference_type offset) {
  ptr_ += offset;
  return *this;
}
Vector::Iterator& Vector::Iterator::operator-=(difference_type offset) {
  ptr_ -= offset;
  return *this;
}
Vector::Iterator::reference Vector::Iterator::operator[
](difference_type offset) const {
  return ptr_[offset];
}
ptrdiff_t Vector::Iterator::operator-(const Iterator& other) const {
  return ptr_ - other.ptr_;
}
bool Vector::Iterator::operator==(const Iterator& other) const {
  return ptr_ == other.ptr_;
}
bool Vector::Iterator::operator>(const Iterator& other) const {
  return ptr_ > other.ptr_;
}
bool Vector::Iterator::operator<(const Iterator& other) const {
  return ptr_ < other.ptr_;
}
bool Vector::Iterator::operator!=(const Iterator& other) const {
  return ptr_ != other.ptr_;
}
bool Vector::Iterator::operator>=(const Iterator& other) const {
  return ptr_ >= other.ptr_;
}
bool Vector::Iterator::operator<=(const Iterator& other) const {
  return ptr_ <= other.ptr_;
}
Vector::Vector(): data_(nullptr), size_(0), capacity_(0) {
}

Vector::Vector(const std::size_t n, const double value): data_(nullptr),
  size_(n), capacity_(0) {
  ReserveAndFill(n, value);
}
Vector::Vector(const std::size_t n): data_(nullptr), size_(0), capacity_(0) {
  ReserveAndFill(n, 0);
}
Vector::Vector(const Vector& other): data_(new double[other.size_]),
                                     size_(other.size_),
                                     capacity_(other.capacity_) {
  other.CopyToNewData(data_);
}
Vector::Vector(Vector&& other) noexcept : data_(other.data_),
                                          size_(other.size_),
                                          capacity_(other.capacity_) {
  other.data_ = nullptr;
  other.size_ = 0;
  other.capacity_ = 0;
}
Vector::~Vector() {
  delete[] data_;
}
Vector::Vector(Iterator begin, Iterator end): data_(nullptr),
                                              size_(end - begin),
                                              capacity_(0) {
  Reserve(size_);
  std::copy(begin, end, Iterator(data_));
}
Vector::Vector(std::initializer_list<double> list): data_(nullptr),
                                                    size_(list.size()),
                                                    capacity_(0) {
  Reserve(size_);
  std::copy(list.begin(), list.end(), Iterator(data_));
}
Vector& Vector::operator=(const Vector& other) {
  if (this == &other) {
    return *this;
  }
  Reserve(other.size_);
  std::copy(other.Begin(), other.End(), Iterator(data_));
  size_ = other.size_;
  return *this;
}
Vector& Vector::operator=(Vector&& other) noexcept {
  if (this != &other) {
    delete[] data_;
    data_ = other.data_;
    size_ = other.size_;
    capacity_ = other.capacity_;
    other.data_ = nullptr;
    other.size_ = 0;
    other.capacity_ = 0;
  }
  return *this;
}

void Vector::Reserve(const std::size_t num) {
  if (capacity_ < num) {
    ReserveWithoutChecks(num);
  }
}
void Vector::ShrinkToFit() {
  if (size_ < capacity_) {
    ReserveWithoutChecks(size_);
  }
}
void Vector::Clear() {
  size_ = 0;
}
void Vector::Insert(std::size_t idx, double elem) {
  if (size_ == 0 || idx > size_) {
    throw std::range_error("Can't delete from empty vector");
  }
  Reserve(size_ + 1);
  // Move to right
  for (std::size_t i = size_; i > idx; --i) {
    data_[i] = data_[i - 1];
  }
  data_[idx] = elem;
  size_++;
}
double Vector::Erase(std::size_t idx) {
  if (size_ == 0 || idx > size_) {
    throw std::range_error("Can't delete from empty vector");
  }
  const double deleted_value = data_[idx];
  size_--;
  // Move to left
  for (std::size_t i = idx; i < size_; ++i) {
    data_[i] = data_[i + 1];
  }

  return deleted_value;
}
void Vector::PushBack(const double elem) {
  if (size_ == capacity_) {
    if (capacity_ == 0) {
      Reserve(kInitPushBackCapacity);
    } else {
      Reserve(capacity_ * 2);
    }
  }
  data_[size_++] = elem;
}
void Vector::PopBack() {
  if (size_ == 0) {
    throw std::range_error("Can't pop back from empty vector");
  }
  size_--;
}
void Vector::Resize(std::size_t size, double elem) {
  if (size_ == size) {
    return;
  }
  if (size_ > size) {
    size_ = size;
    return;
  }
  const auto new_data = new double[size];
  CopyToNewData(new_data);
  for (std::size_t i = size_; i < size; i++) {
    new_data[i] = elem;
  }
  delete[] data_;
  data_ = new_data;
  size_ = size;
  capacity_ = size_;
}
void Vector::Resize(const std::size_t size) {
  Resize(size, 0.0);
}
double& Vector::At(std::size_t idx) const {
  if (idx >= size_) {
    throw std::range_error("Can't get element out of vector bounds");
  }
  return data_[idx];
}
double& Vector::Front() {
  if (Empty()) {
    throw std::range_error("Can't get front element of emtpy vector");
  }
  return *Begin();
}
const double& Vector::Front() const {
  if (Empty()) {
    throw std::range_error("Can't get front element of emtpy vector");
  }
  return *Begin();
}
Vector::iterator Vector::Begin() {
  return Iterator(data_);
}
Vector::iterator Vector::End() {
  return Iterator(data_ + size_);
}
Vector::const_iterator Vector::Begin() const {
  return Iterator(data_);
}
Vector::const_iterator Vector::End() const {
  return Iterator(data_ + size_);
}
std::size_t Vector::Size() const {
  return size_;
}
std::size_t Vector::Capacity() const {
  return capacity_;
}
bool Vector::Empty() const {
  return size_ == 0;
}
void Vector::ReserveWithoutChecks(std::size_t num) {
  capacity_ = num;
  const auto new_data = new double[capacity_];
  if (data_ != nullptr) {
    CopyToNewData(new_data);
    delete[] data_;
  }
  data_ = new_data;
}
void Vector::ReserveAndFill(const std::size_t n, const double value) {
  Reserve(n);
  std::fill_n(Begin(), static_cast<iterator::difference_type>(n),
            value);
}
void Vector::CopyToNewData(double* new_data) const {
  std::copy_n(Begin(), size_, Iterator(new_data));
}
std::size_t Vector::GetEndIdx() const {
  return size_ != 0 ? size_ - 1 : 0;
}
// void Vector::ReserveAndCopy(Iterator begin, Iterator end, std::size_t size) {
//   Reserve(size);
//   std::copy(begin, end, Iterator(data_));
// }
} // task