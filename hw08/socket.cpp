#include "socket.h"
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <iostream>
#include <memory.h>
#include <netdb.h>
#include <errno.h>
#include <functional>

namespace net {
	bool is_listening(int fd) {
		int val;
		socklen_t len = sizeof(val);

		// getsocketopt will return socket status for SO_ACCEPTCONN
		if (getsockopt(fd, SOL_SOCKET, SO_ACCEPTCONN, &val, &len) == -1) {
			// fd is not a valid socket
			return false;
		}

		if (val)
		{
			return true;
		}
		return false;
	}

	Socket::Socket() {
		int sockfd = ::socket(AF_INET, SOCK_STREAM, 0);
		fd_ = FileDescriptor(sockfd);
	}

	// Bind and then listen on the given port. Listen on any incoming address.
	void Socket::listen(uint16_t port) const {
		int server_fd = fd();

		if (server_fd < 0)
			return;

		struct sockaddr_in address;
		int opt = 1;
		int addrlen = sizeof(address);

		// Forcefully attaching socket to the port
		if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0) {
			std::cout << "you can't use this port for now." << std::endl;
		};

		address.sin_family = AF_INET;
		address.sin_addr.s_addr = INADDR_ANY;
		address.sin_port = htons(port);
		memset(&(address.sin_zero), 0, 8);

		if ((bind(server_fd, (struct sockaddr*)&address, sizeof(sockaddr))) < 0)
			return;
		if (::listen(server_fd, port) < 0)
			return;

		std::cout << "start listening on port " << port << std::endl;
	}

	/// Wait for a connection to appear, and then return the newly created connection.
	Connection Socket::accept() const {
		Connection connection(FileDescriptor(-1));
		if (fd() < 0)
			return connection;

		if (fd() < 0 || !is_listening(fd())) {
			throw std::runtime_error("the socket is invalid to call accept");
		}


		std::cout << "waiting for a client ..." << std::endl;

		struct sockaddr_in address;
		int addrlen = sizeof(struct sockaddr);

		int new_socket;
		do {
			new_socket = ::accept(fd(), (struct sockaddr*)&address, (socklen_t*)&addrlen);
		} while (new_socket == -1);

		std::cout << "connected (fd: " << new_socket << ")" << std::endl;
		connection.fd_ = FileDescriptor(new_socket);
		return connection;
	}

	/// Connect to the destination on the given port (be sure of endianness!).
	Connection Socket::connect(std::string destination, uint16_t port) {
		struct sockaddr_in serv_addr;
		int sock = fd();
		Connection connection(FileDescriptor(-1));
		if (sock < 0) {
			throw std::runtime_error("socket is not ready!");
		}
		
		struct hostent* host = gethostbyname(destination.c_str());

		serv_addr.sin_family = AF_INET;
		serv_addr.sin_port = htons(port);
		serv_addr.sin_addr = *((struct in_addr*)host->h_addr);
		bzero(&(serv_addr.sin_zero), 8);

		if (::connect(sock, (struct sockaddr*)&serv_addr, sizeof(struct sockaddr)) < 0) {
			// can't connect
			std::cout << "Error in connection, code: " << errno << std::endl;
			return connection;
		}

		///connection.fd_ = FileDescriptor(sock);
		connection.fd_ = std::move(fd_);
		return connection;
	}

	/// Connect to localhost on the given port, see the other overload
	Connection Socket::connect(uint16_t port) {
		return connect("localhost", port);

	}


	/// Return the int to the file descriptor
	int Socket::fd() const {
		return fd_.unwrap();
	}

}
