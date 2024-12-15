/**
 * @file
 * @brief
 * @details
 * @author xsestech 
 * @date 14.12.2024
 */
#include "building_material.hpp"

namespace task {
BuildingMaterial::BuildingMaterial(const uint32_t id, const std::string& name,
                                   const double weight, const double cost,
                                   const uint32_t storage_days,
                                   const bool is_flammable): Product(id, name,
  weight, cost, storage_days), is_flammable_(is_flammable) {
}
} // task