
#include "TestServer.hpp"
#include <ws2tcpip.h>
#include <winsock2.h>

int main(){
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cerr << "Winsock initialization failed." << std::endl;
        return 1;
    }
    NET::TestServer ts;

    WSACleanup();
}   