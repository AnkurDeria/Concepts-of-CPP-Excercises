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
		std::ostringstream oss;
		oss << data.rdbuf();

		std::string strConst = oss.str();
		const char* pStr = strConst.c_str();

		::send(fd(), pStr, strConst.length(), 0);
	}

	/// Receive data from the underlying socket, and write it to the `std::ostream`.
	ssize_t Connection::receive(std::ostream& stream) const {
		char buf[129];
		int valread = recv(fd(), buf, 128, 0);
		buf[valread] = '\0';
		stream << buf;
		return valread;
	}

	/// Receive all data from the socket
	ssize_t Connection::receive_all(std::ostream& stream) const {
		ssize_t valread{ 0 }, read;
		char buf[129];
		do {
			read = recv(fd(), buf, 128, 0);
			buf[read] = '\0';
			valread += read;
			stream << buf;
		} while (read == 128);

		return valread;
	}

	/// Return the underlying file descriptor
	int Connection::fd() const {
		return fd_.unwrap();
	}

}
