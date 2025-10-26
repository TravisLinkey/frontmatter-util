#include "utils/io.h"
#include "utils/processor.h"
#include "utils/traversal.h"
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

/**
 * @argc - argument count
 * @argv - argument values
 * **/
int main(int argc, char *argv[]) {
  if (argc < 3) {
    throw std::invalid_argument("Missing required argument: tag");
  }

  std::string tag = argv[1];
  const std::string file_path = argv[2];

  std::cout << "[Tag]: " + tag << std::endl;
  std::cout << "[Location]: " + file_path << std::endl;

  // Depth first search to get filepaths for tree
  std::vector<std::string> file_tree = dfs(file_path);
  process_files(file_tree, tag);

  return 0;
}

// TODO
// 1. Accept different flags for Subject, tags, etc.
// 2. Branch on the flag passed
// 3. 
