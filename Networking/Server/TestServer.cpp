
#include "TestServer.hpp"
#include <ws2tcpip.h>
#include <winsock2.h>

NET::TestServer::TestServer() : 
                SimpleServer(AF_INET, SOCK_STREAM, 0, 80, INADDR_ANY, 10)
{
    start_loop(); // launching server
}


void NET::TestServer::accept_request(){
    // struct sockaddr_in address = get_socket()->get_address();
    // int addrlen = sizeof(address);
    // new_socket = accept(get_socket()->get_sock(), (struct sockaddr*)&address, (socklen_t* )&addrlen);
    // read(new_socket, buffer, sizeof(buffer)); 

    struct sockaddr_in address = get_socket()->get_address();
    int addrlen = sizeof(address);
    new_socket = accept(get_socket()->get_sock(), (struct sockaddr*)&address, (socklen_t*)&addrlen);

    if (new_socket < 0) {
        std::cerr << "Failed to accept connection: " << WSAGetLastError() << std::endl;
        return;
    }

    memset(buffer, 0, sizeof(buffer)); // Clear buffer before use
    int bytes_read = recv(new_socket, buffer, sizeof(buffer) - 1, 0);
    if (bytes_read < 0) {
        std::cerr << "Failed to read from socket: " << WSAGetLastError() << std::endl;
    } else {
        buffer[bytes_read] = '\0'; // Null-terminate the buffer
    }

}

void NET::TestServer::handle_request(){
    if (strlen(buffer) > 0) {
        std::cout << "Received HTTP Request:\n" << buffer << std::endl;
    } else {
        std::cerr << "No data received or buffer is empty." << std::endl;
    }
}

void NET::TestServer::respond_request(){
    char* hello = "Server says Hello!";
    send(new_socket, hello, strlen(hello), 0);
    closesocket(new_socket);
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

