#include "file.h"

#include "filesystem.h"

size_t File::get_size() const { return this->content.get_size(); }

bool File::rename(std::string_view new_name)
{
  // TODO: file renaming
   // check if file is registered in a filesystem
    if (this->name.empty() || new_name.empty() || new_name.compare(this->name) == 0)
    {
        return false;
    }

    // update file name
    if (auto lock = this->filesystem.lock(); lock.get() != nullptr)
    {
        lock->rename_file(this->name, new_name);
        return true;
    }
    return false;
}

void File::update(std::unique_ptr<FileContent> new_content)
{
    this->content = std::move(*new_content);
}

const std::string &File::get_name() const { return this->name; }

const FileContent &File::get_content() const { return this->content; }

// TODO file constructor

File::File(FileContent&& content, std::string_view name)
    : content(std::move(content))
    , name(name) {}