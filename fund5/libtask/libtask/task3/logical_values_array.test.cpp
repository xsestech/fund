/**
 * @file
 * @brief
 * @details
 * @author xsestech 
 * @date 03.12.2024
 */

#include <gtest/gtest.h>
#include <libtask/task3/logical_values_array.hpp>
#include <cstdint>
#include <iostream>

namespace task {


TEST(LogicalValuesArrayTest, DefaultConstructor) {
    LogicalValuesArray lva;
    EXPECT_EQ(lva.get_value(), 0u);
}

TEST(LogicalValuesArrayTest, ParameterizedConstructor) {
    LogicalValuesArray lva(0b1010);
    EXPECT_EQ(lva.get_value(), 0b1010u);
}

TEST(LogicalValuesArrayTest, CopyConstructor) {
    LogicalValuesArray lva1(0b1010);
    LogicalValuesArray lva2(lva1);
    EXPECT_EQ(lva2.get_value(), 0b1010u);
}

TEST(LogicalValuesArrayTest, MoveConstructor) {
    LogicalValuesArray lva1(0b1010);
    LogicalValuesArray lva2(std::move(lva1));
    EXPECT_NE(lva2.get_value(), 0u);
}

TEST(LogicalValuesArrayTest, Invert) {
    LogicalValuesArray lva(0b1010);
    lva.Invert();
    EXPECT_EQ(lva.get_value(), ~0b1010u);
}

TEST(LogicalValuesArrayTest, AndOperation) {
    LogicalValuesArray lva1(0b1010);
    LogicalValuesArray lva2(0b1100);
    lva1.And(lva2);
    EXPECT_EQ(lva1.get_value(), 0b1000u);
}

TEST(LogicalValuesArrayTest, OrOperation) {
    LogicalValuesArray lva1(0b1010);
    LogicalValuesArray lva2(0b1100);
    lva1.Or(lva2);
    EXPECT_EQ(lva1.get_value(), 0b1110u);
}

TEST(LogicalValuesArrayTest, Mod2Operation) {
    LogicalValuesArray lva1(0b1010);
    LogicalValuesArray lva2(0b1100);
    lva1.Mod2(lva2);
    EXPECT_EQ(lva1.get_value(), 0b0110u);
}

TEST(LogicalValuesArrayTest, ComplicationOperation) {
    LogicalValuesArray lva1(0b1010);
    LogicalValuesArray lva2(0b1100);
    lva1.Complication(lva2);
    EXPECT_EQ(lva1.get_value(), ~(0b1010u ^ 0b1100u));
}

TEST(LogicalValuesArrayTest, ImplicationOperation) {
    LogicalValuesArray lva1(0b1010);
    LogicalValuesArray lva2(0b1100);
    lva1.Implication(lva2);
    EXPECT_EQ(lva1.get_value(), (~0b1010u) | 0b1100u);
}

TEST(LogicalValuesArrayTest, PearceOperation) {
    LogicalValuesArray lva1(0b1010);
    LogicalValuesArray lva2(0b1100);
    lva1.Pearce(lva2);
    EXPECT_EQ(lva1.get_value(), ~(0b1010u | 0b1100u));
}

TEST(LogicalValuesArrayTest, ShefferOperation) {
    LogicalValuesArray lva1(0b1010);
    LogicalValuesArray lva2(0b1100);
    lva1.Sheffer(lva2);
    EXPECT_EQ(lva1.get_value(), ~(0b1010u & 0b1100u));
}

TEST(LogicalValuesArrayTest, EqualsFunction) {
    LogicalValuesArray lva1(0b1010);
    LogicalValuesArray lva2(0b1010);
    EXPECT_TRUE(LogicalValuesArray::Equals(lva1, lva2));
    LogicalValuesArray lva3(0b1111);
    EXPECT_FALSE(LogicalValuesArray::Equals(lva1, lva3));
}

TEST(LogicalValuesArrayTest, GetBitFunction) {
    LogicalValuesArray lva(0b1010);
    EXPECT_EQ(lva.get_bit(0), 0);
    EXPECT_EQ(lva.get_bit(1), 1);
    EXPECT_EQ(lva.get_bit(2), 0);
    EXPECT_EQ(lva.get_bit(3), 1);
    EXPECT_EQ(lva.get_bit(32), 0);
}

TEST(LogicalValuesArrayTest, ToStringFunction) {
    char* dest = NULL;
    LogicalValuesArray lva(0b1010);
    lva.ToString(dest);
    ASSERT_STREQ(dest, "1010");
    std::cout << std::string(dest);

}

TEST(LogicalValuesArrayTest, EdgeCaseZero) {
    LogicalValuesArray lva(0u);
    lva.Invert();
    EXPECT_EQ(lva.get_value(), ~0u);
    lva.And(LogicalValuesArray(0u));
    EXPECT_EQ(lva.get_value(), 0u);
}

TEST(LogicalValuesArrayTest, EdgeCaseAllOnes) {
    LogicalValuesArray lva(UINT_MAX);
    lva.Invert();
    EXPECT_EQ(lva.get_value(), 0u);
    lva.Or(LogicalValuesArray(0u));
    EXPECT_EQ(lva.get_value(), 0u);
}

} // namespace task

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}