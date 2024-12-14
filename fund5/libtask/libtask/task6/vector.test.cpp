#include <gtest/gtest.h>

#include <numeric>

#include "vector.hpp"

namespace task {
TEST(VectorTest, DefaultConstructor) {
  Vector vec;
  EXPECT_EQ(vec.Size(), 0u);
  EXPECT_EQ(vec.Capacity(), 0u);
}

TEST(VectorTest, SizeConstructor) {
  Vector vec(5, 3.14);
  EXPECT_EQ(vec.Size(), 5u);
  for (size_t i = 0; i < 5; ++i) {
    EXPECT_DOUBLE_EQ(vec.At(i), 3.14);
  }
}

TEST(VectorTest, CopyConstructor) {
  Vector vec1(3, 2.71);
  Vector vec2(vec1);
  EXPECT_EQ(vec2.Size(), 3u);
  for (size_t i = 0; i < 3; ++i) {
    EXPECT_DOUBLE_EQ(vec2.At(i), 2.71);
  }
}

TEST(VectorTest, MoveConstructor) {
  Vector vec1(2, 1.618);
  Vector vec2(std::move(vec1));
  EXPECT_EQ(vec2.Size(), 2u);
  EXPECT_EQ(vec1.Size(), 0u);
  EXPECT_DOUBLE_EQ(vec2.At(0), 1.618);
  EXPECT_DOUBLE_EQ(vec2.At(1), 1.618);
}

TEST(VectorTest, InitializerListConstructor) {
  Vector vec{1.1, 2.2, 3.3};
  EXPECT_EQ(vec.Size(), 3u);
  EXPECT_DOUBLE_EQ(vec.At(0), 1.1);
  EXPECT_DOUBLE_EQ(vec.At(1), 2.2);
  EXPECT_DOUBLE_EQ(vec.At(2), 3.3);
}

TEST(VectorTest, ReserveIncreasesCapacity) {
  Vector vec;
  vec.Reserve(10);
  EXPECT_GE(vec.Capacity(), 10u);
}

TEST(VectorTest, ShrinkToFit) {
  Vector vec(10, 1.0);
  vec.ShrinkToFit();
  EXPECT_EQ(vec.Capacity(), 10u);
  vec.Resize(5);
  vec.ShrinkToFit();
  EXPECT_EQ(vec.Capacity(), 5u);
}

TEST(VectorTest, Clear) {
  Vector vec(5, 2.0);
  vec.Clear();
  EXPECT_EQ(vec.Size(), 0u);
  EXPECT_EQ(vec.Capacity(), 5u);
}

TEST(VectorTest, InsertAtPosition) {
  Vector vec(3, 1.0);
  vec.Insert(1, 2.0);
  EXPECT_EQ(vec.Size(), 4u);
  EXPECT_DOUBLE_EQ(vec.At(0), 1.0);
  EXPECT_DOUBLE_EQ(vec.At(1), 2.0);
  EXPECT_DOUBLE_EQ(vec.At(2), 1.0);
  EXPECT_DOUBLE_EQ(vec.At(3), 1.0);
}

TEST(VectorTest, EraseFromPosition) {
  Vector vec(4, 1.0);
  vec.Insert(1, 2.0);
  double erased = vec.Erase(1);
  EXPECT_DOUBLE_EQ(erased, 2.0);
  EXPECT_EQ(vec.Size(), 4u);
  EXPECT_DOUBLE_EQ(vec.At(0), 1.0);
  EXPECT_DOUBLE_EQ(vec.At(1), 1.0);
  EXPECT_DOUBLE_EQ(vec.At(2), 1.0);
}

TEST(VectorTest, PushBack) {
  Vector vec;
  vec.PushBack(3.14);
  EXPECT_EQ(vec.Size(), 1u);
  EXPECT_DOUBLE_EQ(vec.At(0), 3.14);
}

TEST(VectorTest, PopBack) {
  Vector vec(3, 2.0);
  vec.PopBack();
  EXPECT_EQ(vec.Size(), 2u);
  EXPECT_DOUBLE_EQ(vec.At(1), 2.0);
}

TEST(VectorTest, ResizeLarger) {
  Vector vec(2, 1.0);
  vec.Resize(4, 2.0);
  EXPECT_EQ(vec.Size(), 4u);
  EXPECT_DOUBLE_EQ(vec.At(0), 1.0);
  EXPECT_DOUBLE_EQ(vec.At(1), 1.0);
  EXPECT_DOUBLE_EQ(vec.At(2), 2.0);
  EXPECT_DOUBLE_EQ(vec.At(3), 2.0);
}

TEST(VectorTest, ResizeSmaller) {
  Vector vec(5, 1.0);
  vec.Resize(3);
  EXPECT_EQ(vec.Size(), 3u);
}

TEST(VectorTest, AtInBounds) {
  Vector vec(3, 2.0);
  EXPECT_DOUBLE_EQ(vec.At(1), 2.0);
}

TEST(VectorTest, AtOutOfBounds) {
  Vector vec(2, 1.0);
  EXPECT_THROW(vec.At(5), std::range_error);
}

TEST(VectorTest, FrontAndBack) {
  Vector vec(3, 3.14);
  EXPECT_DOUBLE_EQ(vec.Front(), 3.14);
  EXPECT_DOUBLE_EQ(vec.Back(), 3.14);
}

TEST(VectorTest, DataPointer) {
  Vector vec(3, 2.71);
  double* data = vec.Data();
  for (size_t i = 0; i < 3; ++i) {
    EXPECT_DOUBLE_EQ(data[i], 2.71);
  }
}

TEST(VectorTest, IteratorBeginEnd) {
  Vector vec{1.1, 2.2, 3.3};
  auto it = vec.Begin();
  EXPECT_DOUBLE_EQ(*it, 1.1);
  ++it;
  EXPECT_DOUBLE_EQ(*it, 2.2);
  ++it;
  EXPECT_DOUBLE_EQ(*it, 3.3);
  EXPECT_EQ(++it, vec.End());
}

TEST(VectorTest, IteratorComparison) {
  Vector vec{1.1, 2.2, 3.3};
  auto it1 = vec.Begin();
  auto it2 = vec.Begin();
  EXPECT_EQ(it1, it2);
  ++it2;
  EXPECT_NE(it1, it2);
  EXPECT_LT(it1, it2);
  EXPECT_GT(it2, it1);
}

TEST(VectorTest, IteratorArithmetic) {
  Vector vec{1.1, 2.2, 3.3};
  auto it = vec.Begin();
  EXPECT_DOUBLE_EQ(it[0], 1.1);
  EXPECT_DOUBLE_EQ(it[1], 2.2);
  EXPECT_DOUBLE_EQ(it[2], 3.3);
}

TEST(VectorTest, EmptyCheck) {
  Vector vec;
  EXPECT_TRUE(vec.Empty());
  vec.PushBack(1.0);
  EXPECT_FALSE(vec.Empty());
}

TEST(VectorTest, AssignmentOperator) {
  Vector vec1(3, 2.0);
  Vector vec2;
  vec2 = vec1;
  EXPECT_EQ(vec2.Size(), 3u);
  EXPECT_DOUBLE_EQ(vec2.At(0), 2.0);
}

TEST(VectorTest, MoveAssignmentOperator) {
  Vector vec1(2, 1.618);
  Vector vec2;
  vec2 = std::move(vec1);
  EXPECT_EQ(vec2.Size(), 2u);
  EXPECT_EQ(vec1.Size(), 0u);
  EXPECT_DOUBLE_EQ(vec2.At(0), 1.618);
  EXPECT_DOUBLE_EQ(vec2.At(1), 1.618);
}

TEST(VectorTest, ReserveAndFill) {
  Vector vec(4, 0.0);
  vec.Reserve(8);
  EXPECT_GE(vec.Capacity(), 8u);
}

TEST(VectorTest, ReserveNoIncrease) {
  Vector vec(5, 1.0);
  vec.Reserve(3);
  EXPECT_EQ(vec.Capacity(), 5u);
}

TEST(VectorTest, ReserveAndCopy) {
  Vector vec1(3, 2.0);
  Vector vec2(vec1.Begin(), vec1.End());
  EXPECT_EQ(vec2.Size(), 3u);
  EXPECT_DOUBLE_EQ(vec2.At(0), 2.0);
}

TEST(VectorTest, ResizeWithFill) {
  Vector vec(2, 1.0);
  vec.Resize(5, 2.0);
  EXPECT_EQ(vec.Size(), 5u);
  EXPECT_DOUBLE_EQ(vec.At(4), 2.0);
}

TEST(VectorTest, InsertAtEnd) {
  Vector vec(3, 1.0);
  vec.Insert(3, 2.0);
  EXPECT_EQ(vec.Size(), 4u);
  EXPECT_DOUBLE_EQ(vec.At(3), 2.0);
}

TEST(VectorTest, EraseFromEnd) {
  Vector vec(4, 1.0);
  double erased = vec.Erase(3);
  EXPECT_DOUBLE_EQ(erased, 1.0);
  EXPECT_EQ(vec.Size(), 3u);
}

TEST(VectorTest, IteratorDereference) {
  Vector vec{1.1, 2.2, 3.3};
  auto it = vec.Begin();
  EXPECT_DOUBLE_EQ(*it, 1.1);
  it++;
  EXPECT_DOUBLE_EQ(*it, 2.2);
}

TEST(VectorTest, ConstIterator) {
  const Vector vec{1.1, 2.2, 3.3};
  auto it = vec.Begin();
  EXPECT_DOUBLE_EQ(*it, 1.1);
  ++it;
  EXPECT_DOUBLE_EQ(*it, 2.2);
}

TEST(VectorTest, SizeEmpty) {
  Vector vec;
  EXPECT_EQ(vec.Size(), 0u);
}

TEST(VectorTest, EmptyVectorAt) {
  Vector vec;
  EXPECT_THROW(vec.At(0), std::range_error);
}

TEST(VectorTest, EmptyVectorFrontBack) {
  Vector vec;
  EXPECT_THROW(vec.Front(), std::range_error);
  EXPECT_THROW(vec.Back(), std::range_error);
}

TEST(VectorTest, EmptyVectorErase) {
  Vector vec;
  EXPECT_THROW(vec.Erase(0), std::range_error);
}

TEST(VectorTest, EmptyVectorInsert) {
  Vector vec;
  EXPECT_THROW(vec.Insert(0, 1.0), std::range_error);
}

TEST(VectorTest, EmptyVectorPopBack) {
  Vector vec;
  EXPECT_THROW(vec.PopBack(), std::range_error);
}

TEST(VectorTest, EmptyVectorIterator) {
  Vector vec;
  EXPECT_EQ(vec.Begin(), vec.End());
}

TEST(VectorTest, SortVector) {
  Vector vec = {6, 3, 5, 3, 4, 5, 1, 3};
  std::sort(vec.Begin(), vec.End());
  for (int i = 0; i < vec.Size() - 1; ++i) {
    EXPECT_LE(vec.At(i), vec.At(i + 1));
  }
}


}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}