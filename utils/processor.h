#ifndef PROCESSOR
#define PROCESSOR

#include <string>
#include <vector>

std::string add_frontmatter_from_template(std::string);
void add_tag(std::string file_contents, std::string new_tag);
std::vector<std::string>
add_tag_block(std::vector<std::string> filtered_file_contents,
              std::vector<std::string> tag_block, std::string tag);
std::string append_empty_tag(std::string file_contents, std::string tag);
std::vector<std::string> copy_tag_block(std::vector<std::string> tokens);
bool detect_frontmatter(std::string file_contents);
bool frontmatter_contains_tag(const std::string &file_contents);
std::string move_tag_block(const std::string file_contents, std::string tag);
void process_files(std::vector<std::string> file_tree, std::string tag);
std::vector<std::string> remove_tag_block(std::vector<std::string> tokens);

#endif
