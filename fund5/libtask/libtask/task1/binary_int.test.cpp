#include <gtest/gtest.h>
#include <libtask/task1/binary_int.hpp>
#include <random>

namespace task {

// Test constructors
TEST(BinaryIntTest, DefaultConstructor) {
  BinaryInt b;
  EXPECT_EQ(b.get_value(), 0);
}

TEST(BinaryIntTest, ParameterizedConstructor) {
  BinaryInt b(42);
  EXPECT_EQ(b.get_value(), 42);
}

TEST(BinaryIntTest, CopyConstructor) {
  BinaryInt b1(42);
  BinaryInt b2(b1);
  EXPECT_EQ(b2.get_value(), 42);
}

TEST(BinaryIntTest, MoveConstructor) {
  BinaryInt b1(42);
  BinaryInt b2(std::move(b1));
  EXPECT_EQ(b2.get_value(), 42);
}

// Test assignment operators
TEST(BinaryIntTest, CopyAssignment) {
  BinaryInt b1(42);
  BinaryInt b2;
  b2 = b1;
  EXPECT_EQ(b2.get_value(), 42);
}

TEST(BinaryIntTest, MoveAssignment) {
  BinaryInt b1(42);
  BinaryInt b2;
  b2 = std::move(b1);
  EXPECT_EQ(b2.get_value(), 42);
}

// Test unary minus operator
TEST(BinaryIntTest, UnaryMinus) {
  BinaryInt b(42);
  BinaryInt neg_b = -b;
  EXPECT_EQ(neg_b.get_value(), -42);
}

// Test addition operator
TEST(BinaryIntTest, Addition) {
  BinaryInt b1(42);
  BinaryInt b2(10);
  BinaryInt result = b1 + b2;
  EXPECT_EQ(result.get_value(), 52);
}

// Test subtraction operator
TEST(BinaryIntTest, Subtraction) {
  BinaryInt b1(42);
  BinaryInt b2(10);
  BinaryInt result = b1 - b2;
  EXPECT_EQ(result.get_value(), 32);
}

// Test multiplication operator
TEST(BinaryIntTest, Multiplication) {
  BinaryInt b1(42);
  BinaryInt b2(10);
  BinaryInt result = b1 * b2;
  EXPECT_EQ(result.get_value(), 420);
}

// Test pre-increment operator
TEST(BinaryIntTest, PreIncrement) {
  BinaryInt b(42);
  ++b;
  EXPECT_EQ(b.get_value(), 43);
}

// Test post-increment operator
TEST(BinaryIntTest, PostIncrement) {
  BinaryInt b(42);
  BinaryInt result = b++;
  EXPECT_EQ(result.get_value(), 42);
  EXPECT_EQ(b.get_value(), 43);
}

// Test pre-decrement operator
TEST(BinaryIntTest, PreDecrement) {
  BinaryInt b(42);
  --b;
  EXPECT_EQ(b.get_value(), 41);
}

// Test post-decrement operator
TEST(BinaryIntTest, PostDecrement) {
  BinaryInt b(42);
  BinaryInt result = b--;
  EXPECT_EQ(result.get_value(), 42);
  EXPECT_EQ(b.get_value(), 41);
}

// Test compound addition operator
TEST(BinaryIntTest, CompoundAddition) {
  BinaryInt b1(42);
  BinaryInt b2(10);
  b1 += b2;
  EXPECT_EQ(b1.get_value(), 52);
}

// Test compound subtraction operator
TEST(BinaryIntTest, CompoundSubtraction) {
  BinaryInt b1(42);
  BinaryInt b2(10);
  b1 -= b2;
  EXPECT_EQ(b1.get_value(), 32);
}

// Test compound multiplication operator
TEST(BinaryIntTest, CompoundMultiplication) {
  BinaryInt b1(42);
  BinaryInt b2(10);
  b1 *= b2;
  EXPECT_EQ(b1.get_value(), 420);
}

// Test shift left assignment operator
TEST(BinaryIntTest, ShiftLeftAssignment) {
  BinaryInt b(42);
  b <<= 2;
  EXPECT_EQ(b.get_value(), 168);
}

// Test shift right assignment operator
TEST(BinaryIntTest, ShiftRightAssignment) {
  BinaryInt b(42);
  b >>= 2;
  EXPECT_EQ(b.get_value(), 10);
}

// Test splitInHalf method
TEST(BinaryIntTest, SplitInHalf) {
  BinaryInt b(0x12345678);
  auto halves = b.splitInHalf();
  EXPECT_EQ(halves.first.get_value(), 0x12340000);
  EXPECT_EQ(halves.second.get_value(), 0x00005678);
}

// Test edge cases
TEST(BinaryIntTest, EdgeCases) {
  BinaryInt b1(INT_MAX);
  BinaryInt b2(INT_MIN);

  // Addition overflow
  BinaryInt result = b1 + BinaryInt(1);
  EXPECT_EQ(result.get_value(), INT_MIN);

  // Subtraction underflow
  result = b2 - BinaryInt(1);
  EXPECT_EQ(result.get_value(), INT_MAX);

  // Multiplication overflow
  result = b1 * BinaryInt(2);
  EXPECT_EQ(result.get_value(), -2);
}

// Test random cases
TEST(BinaryIntTest, RandomCases) {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> dis(-1000, 1000);

  for (int i = 0; i < 100; ++i) {
    int a = dis(gen);
    int b = dis(gen);
    BinaryInt b1(a);
    BinaryInt b2(b);

    EXPECT_EQ((b1 + b2).get_value(), a + b);
    EXPECT_EQ((b1 - b2).get_value(), a - b);
    EXPECT_EQ((b1 * b2).get_value(), a * b);
  }
}

}  // namespace task

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}