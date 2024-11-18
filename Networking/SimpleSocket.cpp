
#include "SimpleSocket.hpp"

// default constructor

NET::SimpleSocket::SimpleSocket(int domain, 
                                int service, 
                                int protocol, 
                                int port,
                                u_long yourIP)
    {
    // define address structure
    address.sin_family = domain;
    address.sin_port = htons(port); //host-to-network short
    address.sin_addr.s_addr = htonl(yourIP);

    // establashing socket
    sock = socket(domain, service, protocol);
    test_conenction(sock);

    // establish network connection
    // function declared in SimpleSocket.hpp and defined in BindingSocket 
    // connection = connect_to_network(sock, address);
    // test_conenction(connection);
}

/* Function declarations */

// this is test connection 
void NET::SimpleSocket::test_conenction(int item_to_test){
    // confirm that the connection is properly establisted or not.
    if(item_to_test < 0){
        perror("failed to establish conenction...");
        exit(EXIT_FAILURE);
    }
}

/* Getter fucntions */

struct sockaddr_in NET::SimpleSocket::get_address(){
    return address;
}

int NET::SimpleSocket::get_sock(){
    return sock;
}

int NET::SimpleSocket::get_connection(){
    return connection;
}

/* Defining Setter functions */

void NET::SimpleSocket::set_connection(int connection){
    this->connection = connection;
}
