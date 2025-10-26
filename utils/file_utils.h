#ifndef FILE_UTILS
#define FILE_UTILS

#include <string>

std::string get_file_extention(std::string file_path);
std::string read_file(std::string file_path);
void write_file(const std::string &file_path, const std::string &file_contents);

#endif
