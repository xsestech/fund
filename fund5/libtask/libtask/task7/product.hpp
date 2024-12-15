/**
 * @file
 * @brief
 * @details
 * @author xsestech 
 * @date 14.12.2024
 */
#pragma once

#include <string>
#include <iostream>

namespace task {
const double kWeightStorageCoef = 0.05;
class Product {
  public:
    Product(uint32_t id, const std::string& name, double weight, double cost,
            uint32_t storage_days);
    Product(const Product& other);
    virtual ~Product() = default;
    Product& operator=(const Product& other) &;

    virtual double CalculateStorageFee();
    virtual void DisplayInfo();


  protected:
    uint32_t id_;
    std::string name_;
    double weight_;
    double cost_;
    uint32_t storage_days_;
};
} // task