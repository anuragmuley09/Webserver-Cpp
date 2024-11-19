/*
This class should implement a call to connect() function
of socket as a defination to connect_to_network() virtual function from
SimpleSocket.
*/

#ifndef ConnectingSocket_hpp
#define ConnectingSocket_hpp

#include <iostream>
#include <stdio.h>
#include <winsock2.h>
#include "SimpleSocket.hpp"

namespace NET{

    class ConnectingSocket : public SimpleSocket{
        public:
            ConnectingSocket(int domain, int service, int protocol, int port, u_long yourIP);

            int connect_to_network(int sock, struct sockaddr_in address);

    };
}

#endif

