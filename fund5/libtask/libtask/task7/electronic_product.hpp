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
    ElectronicProduct(id_type id, const std::string& name, double weight,
                      double cost,
                      uint32_t storage_days_, uint32_t warranty_period,
                      double power_rating);
    ElectronicProduct(const ElectronicProduct& product) = default;
    ElectronicProduct(ElectronicProduct&& product) = default;
    ~ElectronicProduct() override = default;

    ElectronicProduct& operator=(const ElectronicProduct& other) = default;
    ElectronicProduct& operator=(ElectronicProduct&& other) = default;

    void DisplayInfo() override;
    [[nodiscard]] std::unique_ptr<Product> Clone() const override;

    [[nodiscard]] std::string get_type_str() const override;
    [[nodiscard]] ProductType get_type_id() const override;

  private:
    uint32_t warranty_period_;
    double power_rating_;
};
} // namespace task