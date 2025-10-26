#include <vector>
#include <string>
#include <sstream>

bool string_contains(std::string s, std::string substring) {
  return (s.find(substring) != std::string::npos);
}

/**
 * Takes a string, returns a vector of strings. ie tokens
 * */
std::vector<std::string> vectorize_string(std::string s) {
  std::vector<std::string> string_vector;

  std::istringstream iss(s);
  std::ostringstream oss;

  std::vector<std::string> tokens;
  std::string token;

  char delimiter = '\n';

  while(std::getline(iss, token, delimiter)) {
    tokens.push_back(token + '\n');
  }

  return tokens;
}

/**
 * Takes a vector, returns a string
 * */
std::string stringify_vector(std::vector<std::string> v) {
  std::ostringstream oss;

  for (std::string &line: v) {
    oss << line;
  }

  return oss.str();
}
