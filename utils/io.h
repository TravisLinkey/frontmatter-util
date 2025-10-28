#ifndef IO_UTILS
#define IO_UTILS

#include <vector>
#include <string>

enum class FrontmatterField { Subject, Tag, Type };

FrontmatterField stringToEnum(const std::string& s);
std::string enumToString(FrontmatterField key);
void print_file_tree(std::vector<std::string> file_tree);

#endif 
