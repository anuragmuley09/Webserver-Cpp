
#ifndef TestServer_hpp
#define TestServer_hpp

#include <iostream>
#include "SimpleServer.hpp"
#include <unordered_set>
#include <fstream>

namespace NET{

    class TestServer : public SimpleServer{
        private:
            char buffer[30000] = {0};
            int new_socket;
            std::string requested_path;
            std::unordered_set<std::string> urls;

            void accept_request();
            void handle_request();
            void respond_request();
        public:
            TestServer();

            void start_loop();
            void add_urls();
            std::string extract_path_from_request(const char buffer[]);
            std::string render_html(std::string file_path);
    };

}

#endif