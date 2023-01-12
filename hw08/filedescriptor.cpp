#include "filedescriptor.h"
#include <unistd.h>

namespace net {
    FileDescriptor::FileDescriptor() {
    }
    FileDescriptor::FileDescriptor(int fd) : fd_{ fd } {}

    FileDescriptor::~FileDescriptor() {
        if (fd_.has_value()) {
            close(fd_.value());
        }
    }

	FileDescriptor::FileDescriptor(const FileDescriptor& other) {
		// Copy the fd_ from the source object.
		fd_ = other.fd_;
	}

	FileDescriptor& FileDescriptor::operator = (const FileDescriptor& other) {
		// Copy the fd_ from the source object.
		fd_ = other.fd_;
		return *this;
	}

	FileDescriptor::FileDescriptor(FileDescriptor&& other) {
		// Copy the fd_ from the source object.
		fd_ = other.fd_;

		other.fd_ = {};
	}

	FileDescriptor& FileDescriptor::operator=(FileDescriptor&& other) {
		// Copy the fd_ from the source object.
		fd_ = other.fd_;

		other.fd_ = {};
		return *this;
	}

	int FileDescriptor::unwrap() const {
		if (fd_.has_value())
			return fd_.value();
		return -1;
	}
} // namespace net