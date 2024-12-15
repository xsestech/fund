/**
 * @file
 * @brief
 * @details
 * @author xsestech 
 * @date 14.12.2024
 */
#include "perishable_product.hpp"

namespace task {
PerishableProduct::PerishableProduct(uint32_t id, const std::string& name,
                                     double weight, double cost,
                                     uint32_t storage_days_,
                                     uint32_t expiration_date): Product(
      id, name, weight, cost,
      storage_days_),
  expiration_date_(
      expiration_date) {
}
double PerishableProduct::CalculateStorageFee() {
  return Product::CalculateStorageFee() + calculateExpirationFee();
}
double PerishableProduct::calculateExpirationFee() const {
  double delta = static_cast<double>(storage_days_) - static_cast<double>(expiration_date_);
  if (delta < 0) {
    return 0;
  }
  return delta * kExprationCoef;
}
} // namespace task