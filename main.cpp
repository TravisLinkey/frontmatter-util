#include "utils/io.h"
#include "utils/processor.h"
#include "utils/traversal.h"
#include <array>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

/**
 * @argc - argument count
 * @argv - argument values
 * **/
int main(int argc, char *argv[]) {
  if (argc < 4) {
    throw std::invalid_argument("Missing required argument: tag");
  }

  auto args = std::array<std::string, 3>{argv[1], argv[2], argv[3]};
  auto [key, value, file_path] = args;

  std::cout << "[Type]: " + key << std::endl;
  std::cout << "[Tag]: " + value << std::endl;
  std::cout << "[Location]: " + file_path << std::endl;

  FrontmatterField field = toField(key);

  std::vector<std::string> file_tree = dfs(file_path);
  process_files(file_tree, field, value);

  return 0;
}

