#include "document.h"


Document::Document(FileContent &&content) : File{std::move(content)} {}

// TODO provide file type
std::string_view Document::get_type() const
{
    return "DOC";
}

size_t Document::get_raw_size() const {
	 // TODO get the document size
	return get_content().get_size();
}

unsigned Document::get_character_count() const {
	// TODO count non whitespace characters
    unsigned count = 0;
    for (auto c : std::string_view(get_content().get().get()->data(), get_raw_size()))
    {
        if (!std::isspace(c))
        {
            ++count;
        }
    }
    return count;
}

// TODO content update function
void Document::update(FileContent&& new_content)
{
    File::update(std::make_unique<FileContent>(std::move(new_content)));
}