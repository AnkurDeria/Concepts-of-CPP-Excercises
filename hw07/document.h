#pragma once

#include "file.h"

/**
 * Derived class for text documents.
 */
class Document : public File {
public:
  Document(FileContent &&content = {});
  // TODO: more member functions

  virtual std::string_view get_type() const;

  virtual size_t get_raw_size() const;

  /**
   * Return the number of non-whitespace characters in the file content.
   */
  unsigned get_character_count() const;

  void update(FileContent &&new_content);
};
