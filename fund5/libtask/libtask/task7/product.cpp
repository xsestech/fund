/**
 * @file
 * @brief
 * @details
 * @author xsestech 
 * @date 14.12.2024
 */
#include <libtask/task7/product.hpp>


namespace task {
Product::Product(const id_type id, std::string  name,
                 const double weight,
                 const double cost, const uint32_t storage_days): id_(id),
  name_(std::move(name)),
  weight_(weight), cost_(cost), storage_days_(storage_days) {
}
Product::Product(const Product& other): id_(other.id_), name_(other.name_), // NOLINT(*-use-equals-default)
                                        weight_(other.weight_),
                                        cost_(other.cost_),
                                        storage_days_(
                                            other.storage_days_) {
}
Product& Product::operator=(const Product& other) & { // NOLINT(*-use-equals-default)
  id_ = other.id_;
  name_ = other.name_;
  cost_ = other.cost_;
  weight_ = other.weight_;
  storage_days_ = other.storage_days_;
  return *this;
}
double Product::CalculateStorageFee() const {
  return kWeightStorageCoef * weight_;
}
void Product::DisplayInfo() {
  std::cout << "Product info:" << std::endl;
  std::cout << "id: " << id_ << " name: " << name_ << std::endl;
  std::cout << "cost: " << cost_ << " weight: " << weight_ << std::endl;
  std::cout << "storage days: " << storage_days_ << std::endl;
}
std::unique_ptr<Product> Product::Clone() const {
  return std::make_unique<Product>(id_, name_, weight_, cost_, storage_days_);
}
std::string Product::get_type_str() const {
  return "Product";
}
ProductType Product::get_type_id() const {
  return ProductType::kProduct;
}
uint32_t Product::get_id() const {
  return id_;
}
const std::string& Product::get_name() const {
  return name_;
}
double Product::get_cost() const {
  return cost_;
}
uint32_t Product::get_storage_days() const {
  return storage_days_;
}
double Product::get_weight() const{
  return weight_;
}
bool Product::operator<(const Product& other) const {
  return get_type_id() < other.get_type_id();
}
std::ostream& operator<<(std::ostream& stream, const Product& product) {
  stream << product.get_type_str() << std::endl;
  stream << "id: " << product.get_id() << " name: " << product.get_name() << std::endl;
  stream << "cost: " << product.get_cost() << " weight: " << product.get_weight() << std::endl;
  stream << "storage days: " << product.get_storage_days() << std::endl;
  return stream;
}
} // namespace task