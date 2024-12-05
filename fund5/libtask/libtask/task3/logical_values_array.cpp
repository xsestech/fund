/**
 * @file
 * @brief
 * @details
 * @author xsestech 
 * @date 02.12.2024
 */

#include <libtask/task3/logical_values_array.hpp>



namespace task {
void LogicalValuesArray::Invert() {
  value_ = ~value_;
}
void LogicalValuesArray::And(const LogicalValuesArray& other) {
  value_ &= other.value_;
}
void LogicalValuesArray::Or(const LogicalValuesArray& other) {
  value_ |= other.value_;
}

void LogicalValuesArray::Mod2(const LogicalValuesArray& other) {
  value_ ^= other.value_;
}
void LogicalValuesArray::Complication(const LogicalValuesArray& other) {
  Mod2(other);
  Invert();
}
void LogicalValuesArray::Implication(const LogicalValuesArray& other) {
  value_ = ~value_ | other.value_;
}
void LogicalValuesArray::Pearce(const LogicalValuesArray& other) {
  value_ = ~(value_ | other.value_);
}

void LogicalValuesArray::Sheffer(const LogicalValuesArray& other) {
  value_ = ~(value_ & other.value_);
}


void LogicalValuesArray::ToString(char*& dest) {
  if (dest != NULL) {
    throw std::runtime_error("Destanation string should be null");
  }
  unsigned int temp_value = value_;
  std::size_t current_size = kDefaultStringSize;
  dest = new char[current_size];
  std::size_t idx = 0;
  while (temp_value > 0) {
    if (idx >= current_size - 1) {
      char* new_buff = new char[current_size * 2];
      std::copy_n(dest, current_size, new_buff);
      delete[] dest;
      dest = new_buff;
      current_size *= 2;
    }
    if (temp_value & 1) {
      dest[idx++] = '0';
    } else {
      dest[idx++] = '1';
    }
    temp_value >>= 1;
  }
  dest[idx] = 0;
}

bool LogicalValuesArray::Equals(const LogicalValuesArray& first,
                                const LogicalValuesArray& second) {
  return first.value_ == second.value_;
}
bool LogicalValuesArray::get_bit(std::size_t index) {
  return (value_ >> index) & 1;
}
unsigned int LogicalValuesArray::get_value() {
  return value_;
}
}