#include "io.h"
#include <iostream>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <vector>

static const std::unordered_map<std::string, FrontmatterField> kStringToEnum = {
    {"Subject", FrontmatterField::Subject},
    {"Tag", FrontmatterField::Tag},
    {"Type", FrontmatterField::Type},
};

static const std::unordered_map<FrontmatterField, std::string> kEnumToString = {
    {FrontmatterField::Subject, "Subject"},
    {FrontmatterField::Tag, "Tag"},
    {FrontmatterField::Type, "Type"},
};

FrontmatterField stringToEnum(const std::string &s) {
  if (auto it = kStringToEnum.find(s); it != kStringToEnum.end())
    return it->second;
  throw std::runtime_error("Invalid frontmatter type: " + s +
                           "\nMust be of type: [Subject, Tag, Type]");
}

std::string enumToString(FrontmatterField key) {
  if (auto it = kEnumToString.find(key); it != kEnumToString.end()) {
    return it->second;
  }
  throw std::runtime_error("Invalid frontmatter value.");
}

void print_file_tree(std::vector<std::string> file_tree) {
  for (const std::string &file : file_tree) {
    std::cout << file << std::endl;
  }
}
