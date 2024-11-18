
#include "BindingSocket.hpp"
#include "SimpleSocket.hpp"


// Constructor.
// whenever BindingSocket will be called, it will also call SimpleSocket constructor
// ofc we need to create socket before binding and connecting it right?
NET::BindingSocket::BindingSocket(int domain, int service, int protocol, int port, u_long yourIP) :
                    SimpleSocket(domain, service, protocol, port, yourIP)
{
    set_connection(connect_to_network(get_sock(), get_address()));
    test_conenction(get_connection()); // connection < 0 --> error creating socket


}


// defination of connect_to_network virtual function
int NET::BindingSocket::connect_to_network(int sock, struct sockaddr_in address){
    return bind(sock, (struct sockaddr*)&address, sizeof(address)) < 0; // check  < 0 once
}