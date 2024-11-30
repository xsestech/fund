/**
 * @file
 * @brief
 * @details
 * @author xsestech 
 * @date 30.11.2024
 */
#pragma once

#include <libtask/task2/types.hpp>
#include <numeric>
#include <iterator>

namespace task {
class StateArray {
  public:
    class PRGAGenerator {
      public:
        using iterator_category = std::input_iterator_tag;
        using value_type = u_char;
        using difference_type = std::ptrdiff_t;
        using pointer = u_char*;
        using reference = u_char&;

        explicit PRGAGenerator(StateArray& state_array);
        PRGAGenerator& operator++();
        PRGAGenerator operator++(int);
        u_char operator*() const;
        bool operator==(const PRGAGenerator& other) const;
        bool operator!=(const PRGAGenerator& other) const;

      private:
        size_t i_;
        size_t j_;
        StateArray& state_array_;

    };

    explicit StateArray(const vectorOfBytes& key);

    void set_key(const vectorOfBytes& key);


  private:
    void applyKSA();
    void PRGANextStep(size_t& i, size_t& j);

    u_char& At(size_t idx);

    vectorOfUChars state_array_;
    const vectorOfBytes& key_;
};
} // task