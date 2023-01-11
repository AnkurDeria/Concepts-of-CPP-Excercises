#include "connection.h"
#include <sys/socket.h>
#include <iostream>
#include <stdlib.h>
#include <sstream>

namespace net {
	Connection::Connection(FileDescriptor&& fd) :
		fd_(std::move(fd))
	{
	}

	/// Send data from a string_view to the given file descriptor.
	void Connection::send(std::string_view data) const {
		if (fd() < 0)
			return;
		::send(fd(), data.data(), data.size(), 0);
	}

	/// Send data from an `std::istream` to the given file descriptor
	void Connection::send(std::istream& data) const {
		if (fd() < 0)
			return;
		data.seekg(0, std::ios::end);
		auto size = data.tellg();
		data.seekg(0, std::ios::beg);
		std::string buffer(size, 0);
		data.read(&buffer[0], size);
		::send(fd_.unwrap(), buffer.data(), buffer.size(), 0);
	}

	/// Receive data from the underlying socket, and write it to the `std::ostream`.
	ssize_t Connection::receive(std::ostream& stream) const {
		char buffer[128];
		auto read = ::recv(fd_.unwrap(), buffer, 128, 0);
		if (read > 0) {
			stream.write(buffer, read);
		}
		return read;
	}

	/// Receive all data from the socket
	ssize_t Connection::receive_all(std::ostream& stream) const {
		ssize_t count = 0;
		char buffer[128];
		while (true) {
			auto received = ::recv(fd_.unwrap(), buffer, sizeof(buffer), MSG_DONTWAIT);
			if (received <= 0) break;
			stream.write(buffer, received);
			count += received;
		}
		return count;
	}

	/// Return the underlying file descriptor
	int Connection::fd() const {
		return fd_.unwrap();
	}

}
