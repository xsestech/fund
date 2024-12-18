/**
 * @file
 * @brief
 * @details
 * @author xsestech 
 * @date 14.12.2024
 */
#include <libtask/task7/electronic_product.hpp>

namespace task {
ElectronicProduct::ElectronicProduct(const uint32_t id, const std::string& name,
                                     const double weight, const double cost,
                                     const uint32_t storage_days_,
                                     const uint32_t warranty_period,
                                     const double power_rating): Product(
      id, name,
      weight, cost, storage_days_), warranty_period_(warranty_period),
  power_rating_(power_rating) {
}
void ElectronicProduct::DisplayInfo() {
  Product::DisplayInfo();
  std::cout << "Warranty: " << warranty_period_ << "d Power: " << power_rating_
      << "W" << std::endl;
}
std::unique_ptr<Product> ElectronicProduct::Clone() const {
  return std::make_unique<ElectronicProduct>(id_, name_, weight_, cost_,
                                             storage_days_, warranty_period_,
                                             power_rating_);
}
std::string ElectronicProduct::get_type_str() const {
  return "Electronic product";
}
ProductType ElectronicProduct::get_type_id() const {
  return ProductType::kElectronicProduct;
}
} // namespace task