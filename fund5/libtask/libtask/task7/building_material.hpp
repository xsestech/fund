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

// ReSharper disable once CppVariableCanBeMadeConstexpr
const double kFlamableFeeCoef = 10.0;

class BuildingMaterial final : public Product {
  public:
  BuildingMaterial(uint32_t id, const std::string& name,
               double weight,
               double cost, uint32_t storage_days, bool is_flammable);
  BuildingMaterial(const BuildingMaterial& other) = default;
  BuildingMaterial(BuildingMaterial&& other) = default;
  ~BuildingMaterial() override = default;

  BuildingMaterial& operator=(const BuildingMaterial& other) = default;
  BuildingMaterial& operator=(BuildingMaterial&& other) = default;

  [[nodiscard]] double CalculateStorageFee() const override;

  [[nodiscard]] std::unique_ptr<Product> Clone() const override;

  [[nodiscard]] std::string get_type_str() const override;
  [[nodiscard]] ProductType get_type_id() const override;

  private:
   bool is_flammable_;

};

} // namespace task
