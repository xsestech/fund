/**
 * @file
 * @brief
 * @details
 * @author xsestech 
 * @date 29.11.2024
 */
#pragma once

#include <array>
#include <exception>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <limits>
#include <string>
#include <utility>
#include <vector>

#include <libtask/task2/state_array.hpp>



namespace task {


using vectorOfBytes = std::vector<std::byte>;

class Encoder {
  public:
    explicit Encoder(const vectorOfBytes& key);
    void EncodeFile(const std::string& input_file_name,
                const std::string& output_file_name);

    void set_key(const std::vector<std::byte>& key);

  private:


    vectorOfBytes key_;
    StateArray state_array_;


};
} // task