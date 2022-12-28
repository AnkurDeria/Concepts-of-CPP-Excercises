#include "filesystem.h"

#include <algorithm>
#include <iomanip>
#include <numeric>
#include <sstream>
#include <iostream>

Filesystem::Filesystem() {}

bool Filesystem::register_file(const std::string &name,
                               const std::shared_ptr<File> &file) {
	// TODO: Something needs to be done here
	
	if (name.empty() || file == nullptr || !file->name.empty() || files.contains(name.data()))
	{
		return false;
	}

	

	// TODO: You need some checks here
	auto thisptr = this->shared_from_this();
	std::cout << "use count = " << thisptr.use_count() << std::endl;
	file->filesystem = thisptr;

	std::cout << "use count from filesystem= " << file->filesystem.use_count() << std::endl;

	// TODO: More updates you need to do!

	// TODO register a new file here
	this->files[name] = file;
	file->name = name;

	return true;
}

bool Filesystem::remove_file(std::string_view name) {
  // TODO file removal
	auto it = files.find(name.data());
	if (it != files.end()) {
		// file found
		files.erase(it);
		return true;
	}
	return false;
}

bool Filesystem::rename_file(std::string_view source, std::string_view dest) {
  // TODO file renaming
	// check if source name exists in filesystem
	auto source_it = this->files.find(source.data());
	if (source_it == this->files.end()) {
		// source name does not exist in filesystem
		return false;
	}

	// check if destination name is already taken
	if (this->files.find(dest.data()) != this->files.end()) {
		// destination name is already taken
		return false;
	}

	// update file name
	this->files[dest.data()] = source_it->second;
	source_it->second->name = dest.data();
	files.erase(source_it);
	return true;
}

std::shared_ptr<File> Filesystem::get_file(std::string_view name) const {
  // TODO
	auto it = files.find(name.data());
	if (it == files.end()) {
		return nullptr;
	}
	return it->second;
}

size_t Filesystem::get_file_count() const {
  // TODO
	return this->files.size();
}

size_t Filesystem::in_use() const {
  // TODO sum up all real file sizes
	size_t total_size = 0;
	for (const auto& file : files) {
		total_size += file.second->get_size();
	}
	return total_size;
}

// convenience function so you can see what files are stored
std::string Filesystem::file_overview(bool sort_by_size) {
  std::ostringstream output;
  // this function is not tested, but it may help you when debugging.

  output << "files in filesystem: " << std::endl;

  // for (auto&& entry : this->files) {
  //     // TODO: fix printing name, type and size
  //     output << entry.get_name << std::endl;
  // }
  return std::move(output).str();
}

std::vector<std::shared_ptr<File>>
Filesystem::files_in_size_range(size_t max, size_t min) const {
  // TODO: find the matching files and return them
	std::vector<std::shared_ptr<File>> matching_files;
	for (const auto& file : files) {
		const auto size = file.second->get_size();
		if (size >= min && size <= max) {
			matching_files.push_back(file.second);
		}
	}
	return matching_files;
}
