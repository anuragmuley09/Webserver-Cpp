
#ifndef BindingSocket_hpp
#define BindingSocket_hpp

#include <stdio.h>

#include "SimpleSocket.hpp"



namespace NET{
    class BindingSocket: public SimpleSocket{

        public:
            BindingSocket(int domain, int service, int protocol, int port, u_long yourIP); // this constructor will call SimpleSocket

            // overriding connect to network
            int connect_to_network(int sock, struct sockaddr_in address);

    };
}

#endif

