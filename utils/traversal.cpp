#include "traversal.h"
#include <filesystem>
#include <iostream>
#include <string>
#include <vector>

const std::array<std::string, 1> ignore_directories = {"node_modules"};

std::vector<std::string> dfs(const std::string file_path) {
  std::vector<std::string> file_tree;

  std::filesystem::path current_path(file_path);
  std::string file_name = current_path.filename().string();

  // base case: stop when we hit ignore directories
   if (std::find(ignore_directories.begin(), ignore_directories.end(), file_name) != ignore_directories.end()) {
     file_tree.push_back(file_path);
     return file_tree;
   }

  for (std::string &child : get_children(file_path)) {
    auto children = dfs(child);
    file_tree.reserve(file_tree.size() + children.size());
    file_tree.insert(file_tree.end(), children.begin(), children.end());
  }

  file_tree.push_back(current_path.string());

  return file_tree;
}

std::vector<std::string> get_children(const std::string file_path) {
  std::vector<std::string> children = {};

  if (!std::filesystem::is_directory(file_path)) {
    return children;
  }

  // get all children files and folders in this filepath
  for (const auto &child : std::filesystem::directory_iterator(file_path)) {
    std::filesystem::path current_path = child.path();
    std::string file_name = current_path.filename().string();

    // skip the hidden dotfiles
    if (file_name[0] == '.') continue;
    
    children.push_back(current_path.string());
  }

  return children;
}
