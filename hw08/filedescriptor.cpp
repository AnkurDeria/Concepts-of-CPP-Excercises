#include "filedescriptor.h"
#include <unistd.h>

namespace net {

    FileDescriptor::FileDescriptor(int fd) : fd_{ fd } {}

    FileDescriptor::~FileDescriptor() {
        if (fd_.has_value()) {
            ::close(fd_.value());
        }
    }

    FileDescriptor::FileDescriptor(FileDescriptor&& other) noexcept : fd_{ std::move(other.fd_) } {
        other.fd_ = std::nullopt;
    }

    FileDescriptor& FileDescriptor::operator=(FileDescriptor&& other) noexcept {
        if (fd_.has_value()) {
            ::close(fd_.value());
        }
        fd_ = std::move(other.fd_);
        other.fd_ = std::nullopt;
        return *this;
    }

    int FileDescriptor::unwrap() const {
        if (fd_.has_value()) {
            return fd_.value();
        }
        else {
            return -1;
        }
    }
} // namespace net