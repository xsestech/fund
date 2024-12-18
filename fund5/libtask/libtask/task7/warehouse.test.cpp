#include <gtest/gtest.h>
#include "warehouse.hpp"
#include "perishable_product.hpp"
#include "building_material.hpp"
#include "electronic_product.hpp"

namespace task {
namespace testing {

class WarehouseTest : public ::testing::Test {
  protected:
    void SetUp() override {
      // Create some sample products for testing
      perishable_product_ = std::make_unique<PerishableProduct>(
          1, "Milk", 1.0, 2.5, 7, 5); // 5 days until expiration
      building_material_ = std::make_unique<BuildingMaterial>(
          2, "Wood", 10.0, 50.0, 30, false);
    }

    Warehouse warehouse_;
    std::unique_ptr<PerishableProduct> perishable_product_;
    std::unique_ptr<BuildingMaterial> building_material_;
};

// Test empty warehouse initialization
TEST_F(WarehouseTest, EmptyWarehouseHasZeroSize) {
  EXPECT_EQ(warehouse_.get_size(), 0);
}

// Test adding a product using AddProduct method
TEST_F(WarehouseTest, AddProductIncreasesSize) {
  warehouse_.AddProduct(std::make_unique<PerishableProduct>(
      1, "Milk", 1.0, 2.5, 7, 5));
  EXPECT_EQ(warehouse_.get_size(), 1);
}

// Test += operator for adding products
TEST_F(WarehouseTest, PlusEqualsOperatorAddsProduct) {
  warehouse_ += std::make_unique<PerishableProduct>(
      1, "Milk", 1.0, 2.5, 7, 5);
  EXPECT_EQ(warehouse_.get_size(), 1);
}

// Test deleting a product
TEST_F(WarehouseTest, DeleteProductDecreasesSize) {
  warehouse_.AddProduct(std::make_unique<PerishableProduct>(
      1, "Milk", 1.0, 2.5, 7, 5));
  warehouse_.DeleteProduct(1);
  EXPECT_EQ(warehouse_.get_size(), 0);
}

// Test -= operator for deleting products
TEST_F(WarehouseTest, MinusEqualsOperatorDeletesProduct) {
  warehouse_ += std::make_unique<PerishableProduct>(
      1, "Milk", 1.0, 2.5, 7, 5);
  warehouse_ -= 1;
  EXPECT_EQ(warehouse_.get_size(), 0);
}

// Test finding product by ID
TEST_F(WarehouseTest, FindProductReturnsCorrectProduct) {
  warehouse_.AddProduct(std::make_unique<PerishableProduct>(
      1, "Milk", 1.0, 2.5, 7, 5));
  const Product& found_product = warehouse_.findProduct(1);
  EXPECT_EQ(found_product.get_id(), 1);
  EXPECT_EQ(found_product.get_name(), "Milk");
}

// Test finding non-existent product throws exception
TEST_F(WarehouseTest, FindNonExistentProductThrows) {
  EXPECT_THROW(warehouse_.findProduct(999), std::out_of_range);
}

// Test getting total cost
TEST_F(WarehouseTest, GetTotalCostCalculatesCorrectly) {
  warehouse_.AddProduct(std::make_unique<PerishableProduct>(
      1, "Milk", 1.0, 2.5, 7, 5));
  warehouse_.AddProduct(std::make_unique<BuildingMaterial>(
      2, "Wood", 10.0, 50.0, 30, false));
  EXPECT_DOUBLE_EQ(warehouse_.GetTotalCost(), 52.5); // 2.5 + 50.0
}

// Test filtering products by type
TEST_F(WarehouseTest, FilterByTypeReturnsCorrectProducts) {
  warehouse_.AddProduct(std::make_unique<PerishableProduct>(
      1, "Milk", 1.0, 2.5, 7, 5));
  warehouse_.AddProduct(std::make_unique<PerishableProduct>(
      2, "Eggs", 0.5, 3.0, 14, 10));
  warehouse_.AddProduct(std::make_unique<BuildingMaterial>(
      3, "Wood", 10.0, 50.0, 30, false));

  auto perishable_products = warehouse_.FilterByType<PerishableProduct>();
  EXPECT_EQ(perishable_products.size(), 2);
}

// Test getting expiring products
TEST_F(WarehouseTest, GetExpiringProductsReturnsCorrectProducts) {
  warehouse_.AddProduct(std::make_unique<PerishableProduct>(
      1, "Milk", 1.0, 2.5, 7, 14));
  warehouse_.AddProduct(std::make_unique<PerishableProduct>(
      2, "Eggs", 0.5, 3.0, 14, 24));

  auto expiring_products = warehouse_.GetExpiringProducts(7);
  EXPECT_EQ(expiring_products.size(), 1); // Only milk expires within 7 days
}

// Test adding duplicate product ID throws exception
TEST_F(WarehouseTest, AddDuplicateProductThrows) {
  warehouse_.AddProduct(std::make_unique<PerishableProduct>(
      1, "Milk", 1.0, 2.5, 7, 5));
  warehouse_.AddProduct(std::make_unique<PerishableProduct>(
      1, "Different Milk", 2.0, 3.0, 7, 5));
  EXPECT_EQ(warehouse_[1].get_name(), "Different Milk");

}

// Test operator[] access
TEST_F(WarehouseTest, SquareBracketOperatorAccessesProduct) {
  warehouse_.AddProduct(std::make_unique<PerishableProduct>(
      1, "Milk", 1.0, 2.5, 7, 5));
  const Product& product = warehouse_[1];
  EXPECT_EQ(product.get_id(), 1);
  EXPECT_EQ(product.get_name(), "Milk");
}

// Test operator[] with invalid ID throws
TEST_F(WarehouseTest, SquareBracketOperatorWithInvalidIdThrows) {
  EXPECT_THROW(warehouse_[999], std::out_of_range);
}

// Test storage fee calculation for mixed products
TEST_F(WarehouseTest, StorageFeeCalculationForMixedProducts) {
  warehouse_.AddProduct(std::make_unique<PerishableProduct>(
      1, "Milk", 1.0, 2.5, 7, 5)); // With expiration fee
  warehouse_.AddProduct(std::make_unique<BuildingMaterial>(
      2, "Wood", 10.0, 50.0, 30, true)); // With flammability fee

  double total_storage_fee = 0.0;
  const Product& perishable = warehouse_.findProduct(1);
  const Product& building = warehouse_.findProduct(2);

  total_storage_fee += perishable.CalculateStorageFee();
  total_storage_fee += building.CalculateStorageFee();

  // Storage fee should include weight-based fee + expiration fee for perishable
  // and weight-based fee + flammability fee for building material
  EXPECT_GT(total_storage_fee, 0.0);
}

// Test removing multiple products in sequence
TEST_F(WarehouseTest, RemoveMultipleProductsInSequence) {
  // Add several products
  for (uint32_t i = 1; i <= 5; ++i) {
    warehouse_.AddProduct(std::make_unique<PerishableProduct>(
        i, "Product" + std::to_string(i), 1.0, 2.5, 7, 5));
  }
  EXPECT_EQ(warehouse_.get_size(), 5);

  // Remove products in different order
  warehouse_ -= 3;
  EXPECT_EQ(warehouse_.get_size(), 4);
  warehouse_ -= 1;
  EXPECT_EQ(warehouse_.get_size(), 3);
  warehouse_ -= 5;
  EXPECT_EQ(warehouse_.get_size(), 2);

  // Verify remaining products
  EXPECT_NO_THROW(warehouse_.findProduct(2));
  EXPECT_NO_THROW(warehouse_.findProduct(4));
}

// Test copy constructor behavior
TEST_F(WarehouseTest, CopyConstructorCreatesDeepCopy) {
  warehouse_.AddProduct(std::make_unique<PerishableProduct>(
      1, "Milk", 1.0, 2.5, 7, 5));

  Warehouse copied_warehouse(warehouse_);

  // Modify original warehouse
  warehouse_ -= 1;

  // Copied warehouse should still have the product
  EXPECT_EQ(copied_warehouse.get_size(), 1);
  EXPECT_NO_THROW(copied_warehouse.findProduct(1));
}

// Test move constructor behavior
TEST_F(WarehouseTest, MoveConstructorTransfersOwnership) {
  warehouse_.AddProduct(std::make_unique<PerishableProduct>(
      1, "Milk", 1.0, 2.5, 7, 5));

  Warehouse moved_warehouse(std::move(warehouse_));

  // Original warehouse should be empty
  EXPECT_EQ(warehouse_.get_size(), 0);

  // Moved warehouse should have the product
  EXPECT_EQ(moved_warehouse.get_size(), 1);
  EXPECT_NO_THROW(moved_warehouse.findProduct(1));
}

// Test assignment operator
TEST_F(WarehouseTest, AssignmentOperatorCopiesCorrectly) {
  warehouse_.AddProduct(std::make_unique<PerishableProduct>(
      1, "Milk", 1.0, 2.5, 7, 5));

  Warehouse other_warehouse;
  other_warehouse = warehouse_;

  // Both warehouses should have the same content
  EXPECT_EQ(other_warehouse.get_size(), warehouse_.get_size());
  EXPECT_NO_THROW(other_warehouse.findProduct(1));
}

// Test move assignment operator
TEST_F(WarehouseTest, MoveAssignmentTransfersOwnership) {
  warehouse_.AddProduct(std::make_unique<PerishableProduct>(
      1, "Milk", 1.0, 2.5, 7, 5));

  Warehouse other_warehouse;
  other_warehouse = std::move(warehouse_);

  // Original warehouse should be empty
  EXPECT_EQ(warehouse_.get_size(), 0);

  // Other warehouse should have the product
  EXPECT_EQ(other_warehouse.get_size(), 1);
  EXPECT_NO_THROW(other_warehouse.findProduct(1));
}

// Test boundary conditions for expiring products
TEST_F(WarehouseTest, ExpiringProductsBoundaryConditions) {
  // Add products with different expiration dates
  warehouse_.AddProduct(std::make_unique<PerishableProduct>(
      1, "Today", 1.0, 2.5, 7, 0)); // Expires today
  warehouse_.AddProduct(std::make_unique<PerishableProduct>(
      2, "Tomorrow", 1.0, 2.5, 7, 8)); // Expires tomorrow
  warehouse_.AddProduct(std::make_unique<PerishableProduct>(
      3, "Far", 1.0, 2.5, 7, 100)); // Expires in 100 days

  // Check products expiring today
  auto expiring_today = warehouse_.GetExpiringProducts(0);
  EXPECT_EQ(expiring_today.size(), 1);

  // Check products expiring within one day
  auto expiring_tomorrow = warehouse_.GetExpiringProducts(1);
  EXPECT_EQ(expiring_tomorrow.size(), 2);

  // Check products expiring within long period
  auto expiring_all = warehouse_.GetExpiringProducts(100);
  EXPECT_EQ(expiring_all.size(), 3);
}

// Test type filtering with empty results
TEST_F(WarehouseTest, FilterByTypeWithNoMatches) {
  warehouse_.AddProduct(std::make_unique<BuildingMaterial>(
      1, "Wood", 10.0, 50.0, 30, false));
  warehouse_.AddProduct(std::make_unique<BuildingMaterial>(
      2, "Steel", 20.0, 100.0, 30, false));

  // Should return empty vector for PerishableProduct
  auto perishable_products = warehouse_.FilterByType<PerishableProduct>();
  EXPECT_EQ(perishable_products.size(), 0);
}
TEST_F(WarehouseTest, testCout) {
  warehouse_.AddProduct(std::make_unique<BuildingMaterial>(
      1, "Wood", 10.0, 50.0, 30, false));
  warehouse_.AddProduct(std::make_unique<BuildingMaterial>(
      2, "Steel", 20.0, 100.0, 30, false));
  // Add products with different expiration dates
  warehouse_.AddProduct(std::make_unique<PerishableProduct>(
      1, "Today", 1.0, 2.5, 7, 0)); // Expires today
  warehouse_.AddProduct(std::make_unique<PerishableProduct>(
      2, "Tomorrow", 1.0, 2.5, 7, 8)); // Expires tomorrow
  warehouse_.AddProduct(std::make_unique<PerishableProduct>(
      3, "Far", 1.0, 2.5, 7, 100)); // Expires in 100 days
  std::cout << warehouse_;
}

TEST_F(WarehouseTest, testDisplayInfo) {
  warehouse_.AddProduct(std::make_unique<BuildingMaterial>(
      1, "Wood", 10.0, 50.0, 30, false));
  warehouse_.AddProduct(std::make_unique<ElectronicProduct>(
      2, "Steel", 20.0, 100.0, 30, 5, 500.0));


  warehouse_[1].DisplayInfo();
  warehouse_[2].DisplayInfo();
}

} // namespace testing
} // namespace task