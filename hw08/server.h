#pragma once
#include "connection.h"
#include "socket.h"


namespace net {

 /**
  * TCP socket server. Listens for your request to deliver you juicy data!
  */
 class Server {
 public:
  /// Create a server on a port
  Server(uint16_t  port);

  Connection accept();

 private:
  Socket socket;
 };

} // namespace net
