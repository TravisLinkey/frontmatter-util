#ifndef PROCESSOR
#define PROCESSOR

#include "io.h"
#include <string>
#include <vector>

std::string add_frontmatter_from_template(std::string);
void add_tag(std::string file_contents, std::string new_tag);
std::vector<std::string>
add_tag_block(std::vector<std::string> filtered_file_contents,
              std::vector<std::string> tag_block, std::string tag);
std::string append_empty_subject(std::string file_contents, std::string value);
std::string append_empty_tag(std::string file_contents, std::string tag);
std::vector<std::string> copy_tag_block(std::vector<std::string> tokens);
bool detect_frontmatter(std::string file_contents);
bool frontmatter_contains_field(const std::string &file_contents,
                                FrontmatterField field);
std::string move_tag_block(const std::string file_contents, std::string tag);
std::string overwrite_subject(std::string file_contents, std::string value);
void process_files(std::vector<std::string> file_tree, FrontmatterField key,
                   std::string value);
std::string process_subject(const std::string file_contents,
                            const std::string value);
std::string process_tags(const std::string file_contents,
                         const std::string value);
std::vector<std::string> remove_tag_block(std::vector<std::string> tokens);

#endif
