/**
 * @file
 * @brief
 * @details
 * @author xsestech 
 * @date 14.12.2024
 */
#pragma once

#include <libtask/task7/product.hpp>

namespace task {

class BuildingMaterial: public Product {
  public:
  BuildingMaterial(const uint32_t id, const std::string& name,
               const double weight,
               const double cost, const uint32_t storage_days, const bool is_flammable);

  private:
   bool is_flammable_;

};

} // task
