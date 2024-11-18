
#ifndef SimpleSocket_hpp
#define SimpleSocket_hpp

#include <stdio.h>
#include <winsock2.h>
#include <iostream>
// #include <netinet/in.h>

namespace NET{
    class SimpleSocket{
        private:
            int sock;
            int connection;
            struct sockaddr_in address;

        public:
            SimpleSocket(int domain, int service, int protocol, int port, u_long yourIP);
            // virtual function to connect to a network
            virtual int connect_to_network(int sock, struct sockaddr_in address) = 0; // pure virtual function
            
            // function to check if connection is properly established or not
            void test_conenction(int);

            // getters
            struct sockaddr_in get_address();
            int get_sock();
            int get_conenction();
            void test();

    };
}
#endif

