/**
 * @file
 * @brief
 * @details
 * @author xsestech 
 * @date 14.12.2024
 */
#include <libtask/task7/perishable_product.hpp>

namespace task {
PerishableProduct::PerishableProduct(uint32_t id, const std::string& name,
                                     double weight, double cost,
                                     uint32_t storage_days,
                                     uint32_t expiration_date): Product(
      id, name, weight, cost,
      storage_days),
  expiration_date_(
      expiration_date) {
}
double PerishableProduct::CalculateStorageFee() const {
  return Product::CalculateStorageFee() + calculateExpirationFee();
}
std::unique_ptr<Product> PerishableProduct::Clone() const {
  return std::make_unique<PerishableProduct>(id_, name_, weight_, cost_,
                                             storage_days_, expiration_date_);
}
std::string PerishableProduct::get_type_str() const {
  return "Perishable product";
}
ProductType PerishableProduct::get_type_id() const {
  return ProductType::kPerishableProduct;
}
uint32_t PerishableProduct::get_expiration_date() const {
  return expiration_date_;
}
double PerishableProduct::calculateExpirationFee() const {
  double delta = static_cast<double>(storage_days_) - static_cast<double>(
                   expiration_date_);
  if (delta < 0) {
    return 0;
  }
  return delta * kExpirationCoef;
}
} // namespace task