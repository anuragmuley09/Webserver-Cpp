
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
            int connection; // do we even need this?
            struct sockaddr_in address;

        public:
            SimpleSocket(int domain, int service, int protocol, int port, u_long yourIP);
            // virtual function to connect to a network
            virtual int connect_to_network(int sock, struct sockaddr_in address) = 0; // pure virtual function
            
            // function to check if connection is properly established or not
            void test_conenction(int);

            // getter functions
            struct sockaddr_in get_address();
            int get_sock();
            int get_connection();


            // setter functions
            void set_connection(int connection); 

    };
}
#endif

