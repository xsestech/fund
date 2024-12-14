/**
 * @file
 * @brief
 * @details
 * @author xsestech 
 * @date 02.12.2024
 */
#pragma once

#include <string>

namespace task {
constexpr std::size_t kDefaultStringSize = 10;
class LogicalValuesArray {
  public:
    explicit LogicalValuesArray(unsigned int value = 0): value_(value) {
    }
    LogicalValuesArray(LogicalValuesArray&) = default;
    LogicalValuesArray(LogicalValuesArray&&) = default;
    LogicalValuesArray& operator=(const LogicalValuesArray&) = default;
    LogicalValuesArray& operator=(const LogicalValuesArray&&) = default;

    void Invert();
    void And(const LogicalValuesArray& other);
    void Or(const LogicalValuesArray& other);
    void Mod2(const LogicalValuesArray& other);
    void Complication(const LogicalValuesArray& other);
    void Implication(const LogicalValuesArray& other);
    void Pearce(const LogicalValuesArray& other);
    void Sheffer(const LogicalValuesArray& other);

    void ToString(char*& dest);

    static bool Equals(const LogicalValuesArray& first,
                       const LogicalValuesArray& second);

    bool get_bit(std::size_t index);
    unsigned int get_value();

  private:
    unsigned int value_;
};
} // task