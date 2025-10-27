#include "io.h"
#include <iostream>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <vector>

FrontmatterField toField(const std::string &s) {
  static const std::unordered_map<std::string, FrontmatterField> lookup = {
      {"Subject", FrontmatterField::Subject},
      {"-s", FrontmatterField::Subject},
      {"Tag", FrontmatterField::Tag},
      {"-t", FrontmatterField::Tag}
  };

  if (auto it = lookup.find(s); it != lookup.end())
    return it->second;
  throw std::runtime_error("Invalid frontmatter type: " + s +
                           "\nMust be of type: [Subject, Tag]");
}

void print_file_tree(std::vector<std::string> file_tree) {
  for (const std::string &file : file_tree) {
    std::cout << file << std::endl;
  }
}
