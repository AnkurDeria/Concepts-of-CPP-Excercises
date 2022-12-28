#include "audio.h"

Audio::Audio(FileContent &&content, unsigned duration)
    : File{std::move(content)}, duration{duration} {}

// TODO provide file type
std::string_view Audio::get_type() const
{
    return "AUD";
}
size_t Audio::get_raw_size() const {
    return get_duration() * 2 * 2 * 48000;  // TODO calculate raw size
}

unsigned Audio::get_duration() const{ return this->duration; }

// TODO content update function
void Audio::update(FileContent&& new_content, unsigned new_duration)
{
    File::update(std::make_unique<FileContent>(std::move(new_content)));
    this->duration = new_duration;
}