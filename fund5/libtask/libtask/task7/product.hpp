/**
 * @file
 * @brief
 * @details
 * @author xsestech 
 * @date 14.12.2024
 */
#pragma once

#include <string>
#include <iostream>

namespace task {
enum class ProductType {
  kProduct,
  kBuildingMaterial,
  kElectronicProduct,
  kPerishableProduct,
};
// ReSharper disable once CppVariableCanBeMadeConstexpr
const double kWeightStorageCoef = 0.05;

class Product {
  public:
    using id_type = uint32_t;
    Product(id_type id, std::string name, double weight, double cost,
            uint32_t storage_days);
    Product(const Product& other);
    Product(Product&& other) = default;
    virtual ~Product() = default;

    Product& operator=(const Product& other) &;
    Product& operator=(Product&& other) = default;
    bool operator<(const Product& other) const;

    friend std::ostream& operator<<(std::ostream& stream,
                                    const Product& product);

    [[nodiscard]] virtual double CalculateStorageFee() const;
    virtual void DisplayInfo();
    [[nodiscard]] virtual std::unique_ptr<Product> Clone() const;

    [[nodiscard]] virtual std::string get_type_str() const;
    [[nodiscard]] virtual ProductType get_type_id() const;

    [[nodiscard]] id_type get_id() const;
    [[nodiscard]] const std::string& get_name() const;
    [[nodiscard]] double get_cost() const;
    [[nodiscard]] uint32_t get_storage_days() const;
    [[nodiscard]] double get_weight() const;

  protected:
    id_type id_; // NOLINT(*-non-private-member-variables-in-classes)
    std::string name_; // NOLINT(*-non-private-member-variables-in-classes)
    double weight_; // NOLINT(*-non-private-member-variables-in-classes)
    double cost_; // NOLINT(*-non-private-member-variables-in-classes)
    uint32_t storage_days_; // NOLINT(*-non-private-member-variables-in-classes)
};
} // namespace task