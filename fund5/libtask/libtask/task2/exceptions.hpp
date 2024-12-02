/**
 * @file
 * @brief
 * @details
 * @author xsestech 
 * @date 30.11.2024
 */

#pragma once

#include <stdexcept>
#include <string>

namespace task {
class FileOpenException : public std::runtime_error {
  public:
    explicit FileOpenException(const std::string& filename)
      : std::runtime_error("Failed to open file: " + filename) {
    }
};

class FileSimilarIOPathsException : public std::runtime_error {
  public:
    explicit FileSimilarIOPathsException(const std::string& filename1,
                                         const std::string& filename2)
      : std::runtime_error(
          "Input and output paths are similar or paths doesn't exist: " +
          filename1 + " " + filename2) {
    }
};
};