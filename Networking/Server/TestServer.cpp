
#include "TestServer.hpp"
#include <ws2tcpip.h>
#include <winsock2.h>

NET::TestServer::TestServer() : 
                SimpleServer(AF_INET, SOCK_STREAM, 0, 80, INADDR_ANY, 10)
{
    start_loop(); // launching server
}


void NET::TestServer::accept_request(){
    struct sockaddr_in address = get_socket()->get_address();
    int addrlen = sizeof(address);
    new_socket = accept(get_socket()->get_sock(), (struct sockaddr*)&address, (socklen_t* )&addrlen);

    read(new_socket, buffer, sizeof(buffer)); 
}

void NET::TestServer::handle_request(){
    std::cout<<buffer<<std::endl;
}

void NET::TestServer::respond_request(){
    char* hello = "Server says Hello!";
    write(new_socket, hello, strlen(hello));
    close(new_socket);
}


void NET::TestServer::start_loop(){
    while(true){
        std::cout<<"<-------------Waiting for connection------------->"<<std::endl;
        accept_request();
        handle_request();
        respond_request();
        std::cout<<"<-------------Execution Done------------->"<<std::endl;
    }
}

