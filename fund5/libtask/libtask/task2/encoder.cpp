/**
 * @file
 * @brief
 * @details
 * @author xsestech 
 * @date 29.11.2024
 */
#include <libtask/task2/encoder.hpp>

namespace task {

namespace fs = std::filesystem;

Encoder::Encoder(const vectorOfBytes& key): key_(key), state_array_(key_){

}

void Encoder::EncodeFile(const std::string& input_file_name, const std::string& output_file_name) {
  if (fs::equivalent(input_file_name, output_file_name)) {
    throw std::runtime_error("Input and output files are the same");
  }
  std::ifstream const input_file(input_file_name, std::ios::binary);
  std::ofstream const output_file(output_file_name, std::ios::binary);

  if (!input_file.is_open() || !output_file.is_open()) {
    throw std::system_error();
  }




}
void Encoder::set_key(const std::vector<std::byte>& key) {
  state_array_.set_key(key);
}

} // task