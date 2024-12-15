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
                      uint32_t storage_days_,
                      uint32_t expiration_date);
    PerishableProduct(const PerishableProduct& other) = default;
    ~PerishableProduct() override = default;
    double CalculateStorageFee() override;



  private:
    uint32_t expiration_date_;
    double calculateExpirationFee() const;
};
} // namespace task