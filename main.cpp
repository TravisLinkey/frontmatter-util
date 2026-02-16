#include "utils/io.h"
#include "utils/processor.h"
#include "utils/traversal.h"
#include <array>
#include <filesystem>
#include <iostream>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

const bool just_testing = false;

int main(int argc, char *argv[]) {
  if (argc < 2) {
    std::cerr << "Usage: " << argv[0] << " Key=Value [Key=Value ...] [file_path]\n"
              << "  Key=Value: e.g. Subject=\"Software Engineering\", Tag=reviewed, Filter=concept\n"
              << "  file_path: path to file or directory (default: .)\n"
              << "Example: " << argv[0] << " Subject=\"Software Engineering\" Filter=concept\n";
    return 1;
  }

  std::vector<std::pair<FrontmatterField, std::string>> key_values;
  std::string file_path = ".";

  for (int i = 1; i < argc; ++i) {
    std::string arg = argv[i];
    std::string::size_type eq = arg.find('=');
    if (eq == std::string::npos || eq == 0 || eq == arg.size() - 1) {
      file_path = arg;
      break;
    }
    std::string key = arg.substr(0, eq);
    std::string value = arg.substr(eq + 1);
    key_values.push_back({stringToEnum(key), value});
  }

  if (key_values.empty()) {
    std::cerr << "At least one Key=Value pair is required.\n";
    return 1;
  }

  for (const auto &[field, value] : key_values) {
    std::cout << "[" << enumToString(field) << "]: " << value << std::endl;
  }
  std::cout << "[Location]: " << file_path << std::endl;

  std::vector<std::string> file_tree = dfs(file_path);

  namespace fs = std::filesystem;
  fs::path exe_path = fs::path(argv[0]).lexically_normal();
  std::string template_path =
      (exe_path.parent_path() / "source" / "templates" / "front_matter_template.md").string();

  process_files(file_tree, key_values, just_testing, template_path);

  return 0;
}

