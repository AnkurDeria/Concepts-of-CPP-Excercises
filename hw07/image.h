#pragma once

#include "file.h"

#include <array>

/**
 * Derived class for images.
 * Additionally stores the image resolution.
 */
class Image : public File {
public:
  using resolution_t = std::array<size_t, 2>;

  Image(FileContent &&content = {}, resolution_t res = {0, 0});
  // TODO: more member functions
  virtual std::string_view get_type() const;

  virtual size_t get_raw_size() const;

  resolution_t get_resolution() const;

  void update(FileContent &&new_content, resolution_t size);

protected:
  resolution_t resolution;
  bool colored;
};
