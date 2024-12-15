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
class ElectronicProduct final : public Product {
  public:
    ElectronicProduct(uint32_t id, const std::string& name, double weight,
                      double cost,
                      uint32_t storage_days_, uint32_t warranty_period,
                      double power_rating);
    ElectronicProduct(const ElectronicProduct& product) = default;
    ~ElectronicProduct() override = default;

    ElectronicProduct& operator=(const ElectronicProduct& other) & = default;

    void DisplayInfo() override;

  private:
    uint32_t warranty_period_;
    double power_rating_;
};
} // namespace task