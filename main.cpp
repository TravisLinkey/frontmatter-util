#include "utils/io.h"
#include "utils/processor.h"
#include "utils/traversal.h"
#include <array>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

const bool just_testing = false;

/**
 * @argc - argument count
 * @argv - argument values
 * **/
int main(int argc, char *argv[]) {
  if (argc < 2) {
    std::cerr << "Usage: " << argv[0] << " Key=Value [file_path]\n"
              << "  Key=Value: e.g. Subject=Software Engineering, Tag=reviewed\n"
              << "  file_path: path to file or directory (default: .)\n"
              << "Example: " << argv[0] << " \"Subject=Software Engineering\"\n";
    return 1;
  }

  std::string key_value = argv[1];
  std::string::size_type eq = key_value.find('=');
  if (eq == std::string::npos || eq == 0 || eq == key_value.size() - 1) {
    std::cerr << "Expected Key=Value; got: " << key_value << "\n";
    return 1;
  }
  std::string key = key_value.substr(0, eq);
  std::string value = key_value.substr(eq + 1);
  std::string file_path = (argc >= 3) ? argv[2] : ".";

  std::cout << "[Type]: " + key << std::endl;
  std::cout << "[Tag]: " + value << std::endl;
  std::cout << "[Location]: " + file_path << std::endl;

  FrontmatterField field = stringToEnum(key);

  std::vector<std::string> file_tree = dfs(file_path);

  process_files(file_tree, field, value, just_testing);

  return 0;
}

