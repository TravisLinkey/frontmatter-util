#ifndef IO_UTILS
#define IO_UTILS

#include <vector>
#include <string>

enum class FrontmatterField { Subject, Tag };

FrontmatterField toField(const std::string& s);
void print_file_tree(std::vector<std::string> file_tree);

#endif 
