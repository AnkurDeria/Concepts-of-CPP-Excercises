#pragma once

#include "connection.h"
#include "socket.h"

namespace net {

/**
 * TCP socket client. Can connect to a server given a destination IP address and a port.
 */
class Client {
  public:
   Client();

   // connect to a port on the localhost
   Connection connect(int port);

   //Giving 2 arguments for test case
   // connect to a port on the address and port
   Connection connect(std::string destination, int port);
   //Connection connect (port, socket);

  private:
   Socket socket;
};

} // namespace net
