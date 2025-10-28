#include "processor.h"
#include "file_utils.h"
#include "io.h"
#include "string_utils.h"
#include <filesystem>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

std::string template_filepath =
    "/Users/travislinkey/Projects/cpp/workspace/frontmatter-util/source/"
    "templates/front_matter_template.md";

std::string add_frontmatter_from_template(std::string file_contents) {
  if (detect_frontmatter(file_contents)) {
    return file_contents;
  }

  std::string header = read_file(template_filepath);
  return header + file_contents;
}

std::vector<std::string>
add_tag_block(std::vector<std::string> filtered_file_contents,
              std::vector<std::string> tag_block, std::string tag) {

  std::vector<std::string> updated_tokens;

  int frontmatter_delimiter_count = 0;
  for (const std::string &token : filtered_file_contents) {
    if (string_contains(token, "---")) {
      frontmatter_delimiter_count++;
    }

    if (frontmatter_delimiter_count == 2) {
      updated_tokens.push_back("tags:\n");
      updated_tokens.push_back("  - " + tag + '\n');
      updated_tokens.reserve(updated_tokens.size() + tag_block.size() + 1);
      updated_tokens.insert(updated_tokens.end(), tag_block.begin(),
                            tag_block.end());
      frontmatter_delimiter_count++;
    }

    updated_tokens.push_back(token);
  }

  return updated_tokens;
}

std::string append_empty_subject(std::string file_contents,
                                 FrontmatterField key, std::string value) {
  std::vector<std::string> tokens = vectorize_string(file_contents);
  std::ostringstream oss;

  // append subject to the second field
  int line_number = 0;
  for (const std::string &line : tokens) {
    if (line_number == 1) {
      oss << enumToString(key) + ": " + value + "\n";
    }
    oss << line;
    line_number++;
  }

  std::string updated_frontmatter = oss.str();
  return updated_frontmatter;
}

std::string append_empty_tag(std::string file_contents, std::string tag) {

  std::vector<std::string> tokens = vectorize_string(file_contents);

  std::ostringstream oss;

  // append empty tag to bottom of frontmatter
  int frontmatter_delimiter_count = 0;
  for (const std::string &line : tokens) {
    if (line.find("---") != std::string::npos) {
      frontmatter_delimiter_count++;
    }

    if (frontmatter_delimiter_count == 2) {
      oss << "tags:\n";
      oss << tag;
      frontmatter_delimiter_count++;
    }
    oss << line;
  }

  std::string updated_frontmatter = oss.str();
  return updated_frontmatter;
}

std::vector<std::string> copy_tag_block(std::vector<std::string> tokens) {
  std::vector<std::string> tag_block;

  bool block_started = false;

  // process the tokens, copy the tag block
  for (const std::string &line : tokens) {
    if (block_started) {
      if (string_contains(line, "- ")) {
        tag_block.push_back(line);
      } else {
        break;
      }
    }

    if (string_contains(line, "tags:")) {
      block_started = true;
    }
  }

  return tag_block;
}

bool detect_frontmatter(std::string file_contents) {
  std::vector<std::string> tokens = vectorize_string(file_contents);

  int count = 0;
  bool hasTop = false;
  bool hasBottom = false;

  for (std::string &t : tokens) {
    if (hasTop && (t.find("---") != std::string::npos)) {
      hasBottom = true;
    }

    if (count == 0 && (t.find("---") != std::string::npos)) {
      hasTop = true;
    }

    count++;
  }

  return hasTop && hasBottom;
}

bool frontmatter_contains_field(const std::string &file_contents,
                                FrontmatterField field) {
  switch (field) {
  case FrontmatterField::Tag:
    return string_contains(file_contents, "tags:");
  case FrontmatterField::Subject:
    return string_contains(file_contents, "Subject:");
  case FrontmatterField::Type:
    return string_contains(file_contents, "Type:");
  }

  return false;
}

std::string move_tag_block(const std::string file_contents, std::string tag) {
  std::vector<std::string> tokens = vectorize_string(file_contents);
  std::vector<std::string> tag_block = copy_tag_block(tokens);

  std::string s = stringify_vector(tag_block);

  std::vector<std::string> filtered_file_contents = remove_tag_block(tokens);
  std::string t = stringify_vector(filtered_file_contents);

  std::vector<std::string> updated_file_contents =
      add_tag_block(filtered_file_contents, tag_block, tag);

  std::string final_content = stringify_vector(updated_file_contents);

  return final_content;
}

std::string overwrite_subject(std::string file_contents, FrontmatterField key,
                              std::string value) {
  std::vector<std::string> tokens = vectorize_string(file_contents);
  std::ostringstream oss;

  std::string field = enumToString(key);

  // find type, overwrite it
  for (const std::string &line : tokens) {
    if (line.find(field + ":") != std::string::npos) {
      oss << field + ": " + value + "\n";
      continue;
    }

    oss << line;
  }

  std::string updated_frontmatter = oss.str();
  return updated_frontmatter;
}

void process_files(std::vector<std::string> file_tree, FrontmatterField key,
                   std::string value, bool just_testing) {
  namespace fs = std::filesystem;

  for (std::string &file_path : file_tree) {
    // skip directories
    if (fs::is_directory(file_path))
      continue;

    // skip non markdown files
    if (get_file_extention(file_path) != "md")
      continue;

    const std::string file_contents = read_file(file_path);
    const std::string file_contents_with_frontmatter =
        add_frontmatter_from_template(file_contents);

    std::string updated_file_contents;
    switch (key) {
    case FrontmatterField::Tag:
      updated_file_contents =
          process_tags(file_contents_with_frontmatter, value);
      break;

    // TODO - fix this below
    case FrontmatterField::Type:
    case FrontmatterField::Subject:
      updated_file_contents =
          process_field(file_contents_with_frontmatter, key, value);
      break;
    }

    if (just_testing) {
      std::cout << "-- Final Content --" << std::endl;
      std::cout << updated_file_contents << std::endl;
    } else {
      std::string new_file_path = file_path;
      write_file(new_file_path, updated_file_contents);
    }
  }
}

std::string process_field(const std::string file_contents, FrontmatterField key,
                          const std::string value) {
  std::string updated_file_contents;

  const bool has_subject = frontmatter_contains_field(file_contents, key);
  if (!has_subject) {
    updated_file_contents = append_empty_subject(file_contents, key, value);
  } else {
    updated_file_contents = overwrite_subject(file_contents, key, value);
  }

  return updated_file_contents;
}

std::string process_tags(const std::string file_contents,
                         const std::string value) {
  std::string updated_file_contents;

  bool has_tag =
      frontmatter_contains_field(file_contents, FrontmatterField::Tag);
  if (has_tag) {
    updated_file_contents = move_tag_block(file_contents, value);
  } else {
    updated_file_contents = append_empty_tag(file_contents, value);
  }
  return updated_file_contents;
}

std::vector<std::string> remove_tag_block(std::vector<std::string> tokens) {
  std::vector<std::string> updated_tokens;

  bool tag_found = false;

  // iterate over tokens, skip the tag_block
  for (const std::string &token : tokens) {
    if (tag_found && (string_contains(token, "- "))) {
      continue;
    }
    if (tag_found && !(string_contains(token, "- "))) {
      tag_found = false;
    }

    if (string_contains(token, "tags:")) {
      tag_found = true;
      continue;
    }

    updated_tokens.push_back(token);
  }

  return updated_tokens;
}

// TODO
