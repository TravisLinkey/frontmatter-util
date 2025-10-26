#include <vector>
#include <string>
#include <iostream>

void print_file_tree(std::vector<std::string> file_tree) {
  for (const std::string &file: file_tree) {
    std::cout << file << std::endl;
  }
}
