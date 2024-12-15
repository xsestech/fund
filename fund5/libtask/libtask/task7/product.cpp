/**
 * @file
 * @brief
 * @details
 * @author xsestech 
 * @date 14.12.2024
 */
#include "product.hpp"

namespace task {
Product::Product(const uint32_t id, const std::string& name,
                 const double weight,
                 const double cost, const uint32_t storage_days): id_(id),
  name_(name),
  weight_(weight), cost_(cost), storage_days_(storage_days) {
}
Product::Product(const Product& other): id_(other.id_), name_(other.name_),
                                        weight_(other.weight_),
                                        cost_(other.cost_),
                                        storage_days_(
                                            other.storage_days_) {
}
Product& Product::operator=(const Product& other) & {
  id_ = other.id_;
  name_ = other.name_;
  cost_ = other.cost_;
  weight_ = other.weight_;
  storage_days_ = other.storage_days_;
  return *this;
}
double Product::CalculateStorageFee() {
  return kWeightStorageCoef * weight_;
}
void Product::DisplayInfo() {
  std::cout << "Product info:" << std::endl;
  std::cout << "id: " << id_ << " name: " << name_ << std::endl;
  std::cout << "cost: " << cost_ << " weight: " << weight_ << std::endl;
  std::cout << "storage days: " << storage_days_ << std::endl;
}
} // task