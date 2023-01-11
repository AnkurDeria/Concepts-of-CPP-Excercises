#include "server.h"

namespace net {
    Server::Server(int port) {
        socket.listen(port);
    }

    Connection Server::accept() {
        return socket.accept();
    }
}
