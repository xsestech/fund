/**
 * @file
 * @brief
 * @details
 * @author xsestech 
 * @date 30.11.2024
 */

#include <gtest/gtest.h>
#include <filesystem>

#include <libtask/task2/encoder.hpp>

#include <array>

namespace task {
namespace fs = std::filesystem;

class EncoderTest : public ::testing::Test {
  protected:
    void SetUp() override {
      encoder.set_key(key);
    }

    // void TearDown() override {
    // }

    std::vector<std::byte> key;
    Encoder encoder;
    EncoderTest() : key({std::byte{0xFF}, std::byte{0x1A}, std::byte{0x5F},
                         std::byte{0x10}, std::byte{0x16}}), encoder(key) {
    }
};

TEST_F(EncoderTest, testFileEncodeDecode) {
  encoder.EncodeFile("tests/task2/test1.in", "tests/task2/test1.out");
  encoder.EncodeFile("tests/task2/test1.out", "tests/task2/test1.out.out");
}

TEST_F(EncoderTest, testSimilarFiles) {
  EXPECT_THROW({
  try {
    encoder.EncodeFile("tests/task2/test1.in", "tests/task2/test1.in");
  } catch (const FileSimilarIOPathsException& e) {
    EXPECT_STREQ("Input and output paths are similar or paths doesn't exist: tests/task2/test1.in tests/task2/test1.in", e.what());
    throw;
  }}, FileSimilarIOPathsException);
}

TEST_F(EncoderTest, testShitPath) {
  EXPECT_THROW({
  try {
    encoder.EncodeFile("tests/task2/test1.in", "../fund5/tests/task2/test1.in");
  } catch (const FileSimilarIOPathsException& e) {
    EXPECT_STREQ("Input and output paths are similar or paths doesn't exist: tests/task2/test1.in ../fund5/tests/task2/test1.in", e.what());
    throw;
  }}, FileSimilarIOPathsException);
}

}