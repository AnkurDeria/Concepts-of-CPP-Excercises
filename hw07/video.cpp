#include "video.h"

Video::Video(FileContent &&content, resolution_t resolution, double duration)
    : File{std::move(content)}, resolution{resolution}, duration{duration} {}

// TODO provide file type
std::string_view Video::get_type() const
{
    return "VID";
}
size_t Video::get_raw_size() const {
  // TODO size of raw 30 FPS RGB color video
    return 3 * get_resolution()[0] * get_resolution()[1] * static_cast<size_t>(30 * get_duration());
}

auto Video::get_resolution() const -> resolution_t { return this->resolution; }

double Video::get_duration() const { return this->duration; }

// TODO content update function
void Video::update(FileContent&& new_content, resolution_t new_resolution, double new_duration)
{
    content = std::move(new_content);
    resolution = new_resolution;
    duration = new_duration;
}