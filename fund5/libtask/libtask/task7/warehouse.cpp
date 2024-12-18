/**
 * @file
 * @brief
 * @details
 * @author xsestech 
 * @date 16.12.2024
 */
#include "warehouse.hpp"

namespace task {
Warehouse::Warehouse(const Warehouse& warehouse): product_map_(warehouse.product_map_.size()) {
  for (auto& [id, product]: warehouse.product_map_) {
    product_map_[id] = product->Clone();
  }
}
Warehouse& Warehouse::operator=(const Warehouse& warehouse) {
  product_map_.clear();
  for (auto& [id, product]: warehouse.product_map_) {
    product_map_[id] = product->Clone();
  }
  return *this;
}
Warehouse& Warehouse::operator+=(std::unique_ptr<Product> product) {
  AddProduct(std::move(product));
  return *this;
}
Warehouse& Warehouse::operator-=(const Product::id_type id) {
  DeleteProduct(id);
  return *this;
}
Product& Warehouse::operator[](const Product::id_type id) const {
  return findProduct(id);
}
double Warehouse::GetTotalCost() const {
  double total_cost = 0;
  for (auto& [_, product] : product_map_) {
    total_cost += product->get_cost();
  }
  return total_cost;
}
void Warehouse::AddProduct(std::unique_ptr<Product> product) {
  if (product == nullptr) {
    throw std::invalid_argument("Product can't be null");
  }
  const Product::id_type id = product->get_id();
  product_map_[id] = std::move(product);
}
void Warehouse::DeleteProduct(const Product::id_type id) {
  product_map_.erase(id);
}
Product& Warehouse::findProduct(const Product::id_type id) const {
  return *product_map_.at(id);
}
std::vector<const PerishableProduct*> Warehouse::GetExpiringProducts(
    uint32_t days) const {
  std::vector<const PerishableProduct*> expired_products;
  for (const auto& [_, product] : product_map_) {
    if (const auto* casted_product = dynamic_cast<const PerishableProduct*>(
      product.get())) {
      if (casted_product->get_expiration_date() <= casted_product->
          get_storage_days() + days) {
        expired_products.push_back(casted_product);
      }
    }
  }
  return expired_products;
}
void Warehouse::displayInventory() {
  std::vector<const Product*> products;
  products.reserve(product_map_.size());
  for (auto& [_, product] : product_map_) {
    products.emplace_back(const_cast<const Product*>(product.get()));
  }
  sort(products.begin(), products.end(), [](const Product* p1, const Product* p2) {
    return *p1 < *p2;
  });
  std::cout << "Warehouse Inventory:\n";
  std::cout << "-------------------\n";
  for (const auto& [_, product] : product_map_) {
    std::cout << "Product type:" << product->get_type_str() << " ";
    product->DisplayInfo();
  }
}
std::size_t Warehouse::get_size() const {
  return product_map_.size();
}

std::ostream& operator<<(std::ostream& stream, const Warehouse& warehouse) {
  stream << "Warehouse info:" << std::endl;
  stream << "Size: " << warehouse.get_size() << std::endl;
  stream << "All products info:" << std::endl;
  auto products = warehouse.FilterByType<Product>();
  for (auto product: products) {
    stream << *product;
  }
  return stream;
}
} // namespace task