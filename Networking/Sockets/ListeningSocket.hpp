
#ifndef ListeningSocket_hpp
#define ListeningSocket_hpp

#include <stdio.h>
#include "BindingSocket.hpp"

namespace NET{

    class ListeningSocket : public BindingSocket{
        private:
            int backlog; // number of people waiting in line to get served. (people after fixed window size)
            int listening;
        public:
            ListeningSocket(int domain, int service, int protocol, int port, u_long yourIP, int backlog);

            void set_backlog(int backlog);
            int get_backlog();

            void start_listening();
    };

}


#endif