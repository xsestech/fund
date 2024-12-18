/**
 * @file
 * @brief
 * @details
 * @author xsestech 
 * @date 14.12.2024
 */
#include "building_material.hpp"

namespace task {
BuildingMaterial::BuildingMaterial(const id_type id, const std::string& name,
                                   const double weight, const double cost,
                                   const uint32_t storage_days,
                                   const bool is_flammable): Product(id, name,
  weight, cost, storage_days), is_flammable_(is_flammable) {
}
double BuildingMaterial::CalculateStorageFee() const {
  return Product::CalculateStorageFee() + kFlamableFeeCoef;
}
std::unique_ptr<Product> BuildingMaterial::Clone() const {
  return std::make_unique<BuildingMaterial>(id_, name_, weight_, cost_,
                                            storage_days_, is_flammable_);
}

std::string BuildingMaterial::get_type_str() const {
  return "Building material";
}
ProductType BuildingMaterial::get_type_id() const {
  return ProductType::kBuildingMaterial;
}
} // namespace task