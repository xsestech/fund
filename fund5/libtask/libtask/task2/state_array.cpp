/**
 * @file
 * @brief
 * @details
 * @author xsestech 
 * @date 30.11.2024
 */
#include <libtask/task2/state_array.hpp>

namespace task {
constexpr size_t kStateArraySize = 256;

StateArray::PRGAGenerator::PRGAGenerator(StateArray& state_array): i_(0), j_(0),
  state_array_(state_array) {
}

StateArray::PRGAGenerator& StateArray::PRGAGenerator::operator++() {
  state_array_.PRGANextStep(i_, j_);
  return *this;
}
StateArray::PRGAGenerator StateArray::PRGAGenerator::operator++(int) {
  PRGAGenerator temp = *this;
  ++(*this);
  return temp;
}
u_char StateArray::PRGAGenerator::operator*() const {
  return state_array_.At(i_) + state_array_.At(j_);
}

bool StateArray::PRGAGenerator::operator==(const PRGAGenerator& other) const {
  return false;
}
bool StateArray::PRGAGenerator::operator!=(const PRGAGenerator& other) const {
  return true;
}

StateArray::StateArray(const vectorOfBytes& key): key_(key) {
  state_array_.reserve(kStateArraySize);
  for (size_t i = 0; i < kStateArraySize; ++i) {
    state_array_.push_back(i);
  }
  applyKSA();
}

void StateArray::set_key(const vectorOfBytes& key): key_(key) {
  std::iota(state_array_.begin(), state_array_.end(), 0);
  applyKSA();
}

void StateArray::applyKSA() {
  size_t j = 0;
  for (size_t i = 0; i < kStateArraySize; ++i) {
    j = (j + state_array_.at(i) + key_.at(i % key_.size())) % kStateArraySize;
    std::swap(state_array_.at(i), state_array_.at(j));
  }
}
void StateArray::PRGANextStep(size_t& i, size_t& j) {
  i = (i + 1) % 256;
  j = (j + state_array_.at(i) % 256;
  std::swap(state_array_.at(i), state_array_.at(j));
}
u_char& StateArray::At(size_t idx) {
  return state_array_.at(idx);
}
} // task