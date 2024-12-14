/**
 * @file
 * @brief
 * @details
 * @author xsestech 
 * @date 12.12.2024
 */
#pragma once

#include <cstddef>
#include <iterator>
#include <algorithm>

namespace task {
class Vector {
  public:
    class Iterator {
      public:
        using iterator_category = std::random_access_iterator_tag;
        using difference_type = std::ptrdiff_t;
        using value_type = double;
        using pointer = double*;
        using reference = double&;

        explicit Iterator(double* ptr);
        Iterator(Iterator& other) = default;
        Iterator(Iterator&& other) = default;
        Iterator& operator=(const Iterator& other) = default;
        Iterator& operator=(Iterator&& other) = default;

        reference operator*();
        reference operator*() const;
        pointer operator->() const;

        Iterator& operator++();
        Iterator operator++(int);

        Iterator& operator--();
        Iterator operator--(int);

        Iterator operator+(difference_type offset) const;
        Iterator operator-(difference_type offset) const;

        Iterator& operator+=(difference_type offset);
        Iterator& operator-=(difference_type offset);

        reference operator[](difference_type offset) const;

        ptrdiff_t operator-(const Iterator& other) const;

        bool operator==(const Iterator& other) const;
        bool operator>(const Iterator& other) const;
        bool operator<(const Iterator& other) const;
        bool operator!=(const Iterator& other) const;
        bool operator>=(const Iterator& other) const;
        bool operator<=(const Iterator& other) const;

      private:
        double* ptr_;
    };
    using iterator = Iterator;
    using const_iterator = const Iterator;
    const std::size_t kInitPushBackCapacity = 1;

    /**
     * Initializes empty vector
     */
    Vector();
    /**
     * Initializes vector of n elements filled with value
     * @param n size of vector
     * @param value default values
     */
    Vector(std::size_t n, double value);
    /**
     * Init vector of size n filled with zeros
     * @param n size of vector
     */
    explicit Vector(std::size_t n);
    Vector(const Vector& other);
    Vector(Vector&& other) noexcept;
    ~Vector();

    Vector(Iterator begin, Iterator end);
    Vector(std::initializer_list<double> list);

    Vector& operator=(const Vector& other);
    Vector& operator=(Vector&& other) noexcept;

    /**
     * Increases the capacity of vector to the number greater or equal to num
     * @param num new capacity
     */
    void Reserve(std::size_t num);
    /**
     * Shrinks vector to take up only space equal to its size
     */
    void ShrinkToFit();
    /**
     * Clears vector making its size equal to zero
     */
    void Clear();
    /**
     * Inserts value to index and moves other elements to right
     * @param idx idx, where element will be inserted
     * @param elem element value
     */
    void Insert(std::size_t idx, double elem);
    /**
     * Deletes value at index and moves other elements to right
     * @param idx idx, where element will be inserted
     * @return elem element value
     */
    [[nodiscard]] double Erase(std::size_t idx);
    void PushBack(double elem);
    void PopBack();
    void Resize(std::size_t size, double elem);
    void Resize(std::size_t size);

    /**
     * Get element by index. Checks index for bounds.
     * Throws exception if bound is exceeded
     * @param idx index of element
     * @return element value at idx
     */
    double& At(std::size_t idx) const;

    double& Front();
    const double& Front() const;
    double& Back();
    const double& Back() const;
    double* Data();
    const double* Data() const;

    iterator Begin();
    iterator End();
    const_iterator Begin() const;
    const_iterator End() const;

    std::size_t Size() const;
    std::size_t Capacity() const;

    bool Empty() const;

  private:
    void ReserveWithoutChecks(std::size_t num);
    void ReserveAndFill(std::size_t n, double value);
    void CopyToNewData(double* new_data) const;
    std::size_t GetEndIdx() const;
    // void ReserveAndCopy(Iterator begin, Iterator end, std::size_t size);

    double* data_;
    std::size_t size_;
    std::size_t capacity_;
};
} // namespace task