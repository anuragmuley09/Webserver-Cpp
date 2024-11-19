
#include "ConnectingSocket.hpp"

NET::ConnectingSocket::ConnectingSocket(int domain, int service, int protocol, int port, u_long yourIP) : 
                        SimpleSocket(domain, service, protocol, port, yourIP)
{
    set_connection(connect_to_network(get_sock(), get_address()));
    test_conenction(get_connection());
}


/* implementation/def here*/

int NET::ConnectingSocket::connect_to_network(int sock, struct sockaddr_in address){
    return connect(sock, (struct sockaddr*)& address, sizeof(address)) < 0; // check < 0 once
}