/**
 * @file
 * @brief
 * @details
 * @author xsestech 
 * @date 14.12.2024
 */
#include "electronic_product.hpp"

namespace task {
ElectronicProduct::ElectronicProduct(uint32_t id, const std::string& name,
                                     double weight, double cost,
                                     uint32_t storage_days_,
                                     uint32_t warranty_period,
                                     double power_rating): Product(id, name,
    weight, cost, storage_days_), warranty_period_(warranty_period),
  power_rating_(power_rating) {
}
void ElectronicProduct::DisplayInfo() {
  Product::DisplayInfo();
  std::cout << "Warranty: " << warranty_period_ << "d Power: " << power_rating_
      << "W" << std::endl;
}
} // task