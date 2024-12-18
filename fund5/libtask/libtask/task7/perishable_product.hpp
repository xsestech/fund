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

const double kExprationCoef = 5.0;

class PerishableProduct final : public Product {
  public:
    PerishableProduct(uint32_t id, const std::string& name, double weight,
                      double cost,
                      uint32_t storage_days,
                      uint32_t expiration_date);
    PerishableProduct(const PerishableProduct& other) = default;
    ~PerishableProduct() override = default;
    [[nodiscard]] double CalculateStorageFee() const override;
    [[nodiscard]] std::unique_ptr<Product> Clone() const override;

    [[nodiscard]] std::string get_type_str() const override;
    [[nodiscard]] ProductType get_type_id() const override;
    [[nodiscard]] uint32_t get_expiration_date() const;

  private:
    uint32_t expiration_date_;
    double calculateExpirationFee() const;
};
} // namespace task