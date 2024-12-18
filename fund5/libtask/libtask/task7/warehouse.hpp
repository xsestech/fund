/**
 * @file
 * @brief
 * @details
 * @author xsestech 
 * @date 16.12.2024
 */
#pragma once

#include <libtask/task7/product.hpp>
#include <libtask/task7/building_material.hpp>
#include <libtask/task7/electronic_product.hpp>
#include <libtask/task7/perishable_product.hpp>

namespace task {

class Warehouse {
  public:
    Warehouse() = default;
    Warehouse(const Warehouse& warehouse);
    Warehouse(Warehouse&& warehouse) noexcept = default;
    Warehouse& operator=(const Warehouse& warehouse);
    Warehouse& operator=(Warehouse&& warehouse) = default;
    ~Warehouse() = default;

    Warehouse& operator+=(std::unique_ptr<Product> product);
    Warehouse& operator-=(Product::id_type id);
    Product& operator[](Product::id_type id) const;
    friend std::ostream& operator<<(std::ostream& stream,
                                    const Warehouse& warehouse);

    void AddProduct(std::unique_ptr<Product> product);
    void DeleteProduct(Product::id_type id);
    [[nodiscard]] double GetTotalCost() const;
    [[nodiscard]] Product& findProduct(Product::id_type id) const;
    template <typename T>
    std::vector<const T*> FilterByType() const {
      std::vector<const T*> filtered_warehouse;
      static_assert(std::is_base_of_v<Product, T>,
                    "T must be a derived class of Product");
      for (const auto& [_, product] : product_map_) {
        if (const T* casted_product = dynamic_cast<const T*>(product.get())) {
          filtered_warehouse.push_back(casted_product);
        }
      }
      return filtered_warehouse;
    }
    [[nodiscard]] std::vector<const PerishableProduct*> GetExpiringProducts(
        uint32_t days) const;
    void displayInventory();

    [[nodiscard]] std::size_t get_size() const;

  private:
    std::unordered_map<Product::id_type, std::unique_ptr<Product> >
    product_map_;

};
} // namespace task