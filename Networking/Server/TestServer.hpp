
#ifndef TestServer_hpp
#define TestServer_hpp

#include "SimpleServer.hpp"

namespace NET{

    class TestServer : public SimpleServer{
        private:
            char buffer[30000] = {0};
            int new_socket;

            void accept_request();
            void handle_request();
            void respond_request();
        public:
            TestServer();

            void start_loop();
    };

}

#endif