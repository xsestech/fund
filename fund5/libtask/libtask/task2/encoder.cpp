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

Encoder::Encoder(vectorOfBytes& key): state_array_(key){

}

bool areFilesEquivalent(const fs::path& path1, const fs::path& path2) {
  try {
    // Get the canonical paths of both files
    fs::path canonicalPath1 = fs::canonical(path1);
    fs::path canonicalPath2 = fs::canonical(path2);

    // Compare the canonical paths
    return canonicalPath1 == canonicalPath2;
  } catch (const fs::filesystem_error& e) {
    // std::cerr << "Filesystem error: " << e.what() << std::endl;
    return false;
  }
}

void Encoder::EncodeFile(const std::string& input_file_name, const std::string& output_file_name) {
  if (areFilesEquivalent(input_file_name, output_file_name)) {
    throw FileSimilarIOPathsException(input_file_name, output_file_name);
  }
  std::ifstream input_file(input_file_name, std::ios::binary);
  std::ofstream output_file(output_file_name, std::ios::binary);

  if (!input_file) {
    throw FileOpenException(input_file_name);
  }

  if (!output_file) {
    throw FileOpenException(output_file_name);
  }


  char byte;
  auto byte_generator = state_array_.begin();
  while (input_file.get(byte)) {
    byte ^= *byte_generator;
    ++byte_generator;
    output_file.write(&byte, 1);
  }
  output_file.close();
  input_file.close();
  state_array_.ResetState();

}
void Encoder::set_key(vectorOfBytes& key) {
  state_array_.set_key(key);
}

} // task