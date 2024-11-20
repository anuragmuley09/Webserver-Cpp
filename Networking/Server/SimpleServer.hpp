
#ifndef SimpleServer_hpp
#define SimpleServer_hpp

#include <unistd.h>
#include <iostream>
#include "../netlibc-networking.hpp"

// assuming simple server has a socket and not simple server is a socket 
namespace NET{
    class SimpleServer{
        private:
            ListeningSocket* socket; // to reserve memeory without instansiating it

            virtual void accept_request() = 0;  // to accept the incomming requests 
            virtual void handle_request() = 0;  // handle incomming requests
            virtual void respond_request() = 0; // respond to incomming request


        public:
            SimpleServer(int domain, int service, int protocol, int port, u_long yourIP, int backlog);

            // we cant create object of this class.
            // The basic idea is, a infinite while loop will call these 3 functions
            // accept...handle...respond...
            // The problem is, that will call base class functions...which is an issue.
            // Thus, to avoid that, we can create a new function to do that, which we will implement later
            virtual void start_loop() = 0; // while(true) 

            // getters
            ListeningSocket* get_socket();
    };

}

#endif