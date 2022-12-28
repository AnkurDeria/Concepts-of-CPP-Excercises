#pragma once

#include <cstdint>
#include <memory>
#include <string>


/**
 * Stored file content.
 * Read-only storage of memory representing contents of a file.
 *
 * Once you constructed a FileContent, you can no longer change the file contents.
 * The data in the string is wrapped so multiple files can point to the same content.
 */

class FileContent {
public:
    FileContent() = default;
    FileContent(const std::string& content) : content_(std::make_shared<std::string>(content)) {}
    FileContent(std::string&& content) : content_(std::make_shared<std::string>(std::move(content))) {}
    FileContent(const char* content) : content_(std::make_shared<std::string>(content)) {}

    /** what's the actual storage size of the file content? */
    size_t get_size() const { return this->content_->size(); }

    /** get a read-only handle to the data */
    std::shared_ptr<const std::string> get() const { return std::const_pointer_cast<const std::string>(this->content_); }

    // add automatic comparisons
    bool operator ==(const FileContent &) const = default;

protected:
    // TODO store shareable file content
    std::shared_ptr<std::string> content_;
};
