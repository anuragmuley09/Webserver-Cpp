
#include "ListeningSocket.hpp"
#include "BindingSocket.hpp"
#include <winsock2.h>
#include <ws2tcpip.h>

int main(){
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cerr << "Winsock initialization failed." << std::endl;
        return 1;
    }

    std::cout<<"starting socket"<<std::endl;
    
    // NET::SimpleSocket ss = NET::SimpleSocket(AF_INET, SOCK_STREAM, 0, 80, INADDR_ANY);

    std::cout<<"Binding socket"<<std::endl;
    NET::BindingSocket bs = NET::BindingSocket(AF_INET, SOCK_STREAM, 0, 81, INADDR_ANY);

    std::cout<<"Listeining socket"<<std::endl;
    NET::ListeningSocket ls = NET::ListeningSocket(AF_INET, SOCK_STREAM, 0, 80, INADDR_ANY, 10);

    std::cout<<"great success!"<<std::endl;


    return 0;
}