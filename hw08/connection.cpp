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
		char buffer[128];
		data.read(buffer, 128);
		while (data) {
			auto read = data.gcount();
			::send(fd_.unwrap(), buffer, read, 0);
			data.read(buffer, 128);
		}
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
		int valread = 0, read;
		char buf[1025];
		do {
			read = recv(fd(), buf, 1024, 0);
			buf[read] = '\0';
			valread += read;
			stream << buf;
		} while (read == 1024);

		return valread;
	}

	/// Return the underlying file descriptor
	int Connection::fd() const {
		return fd_.unwrap();
	}

}
