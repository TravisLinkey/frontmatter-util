#include "file_utils.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

std::string get_file_extention(std::string file_path) {
  std::filesystem::path current_path(file_path);
  std::string file_name = current_path.filename().string();

  // split the file on '.'
  const char delimiter = '.';

  std::vector<std::string> tokens;
  std::istringstream iss(file_name);
  std::string token;

  while(std::getline(iss, token, delimiter)) {
    // return the extention
    tokens.push_back(token);
  }

  return tokens.back();
}

std::string read_file(std::string file_path) {
  std::ifstream input_file(file_path);
  std::string file_contents = "";

  if (!input_file.is_open()) {
    throw std::runtime_error("Failed to open file: " + file_path);
  }

  std::ostringstream buffer;
  buffer << input_file.rdbuf(); // read entire file efficiently

  if (input_file.fail() && !input_file.eof()) {
    throw std::runtime_error("Error reading file: " + file_path);
  }

  return buffer.str();
}

void write_file(const std::string &file_path,
                const std::string &file_contents) {
  std::ofstream output_file(file_path, std::ios::out);

  std::cout << "[Updating]: " + file_path << std::endl;

  if (!output_file.is_open()) {
    throw std::runtime_error("Failed to open file for writing: " + file_path);
  }

  output_file << file_contents;
  if (!output_file) {
    throw std::runtime_error("Failed to write to file: " + file_path);
  }

  output_file.close();
  if (!output_file) {
    throw std::runtime_error("Failed to close file properly: " + file_path);
  }
}
