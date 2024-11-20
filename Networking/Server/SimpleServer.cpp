
#include "SimpleServer.hpp"


NET::SimpleServer::SimpleServer(int domain, int service, int protocol, int port, u_long yourIP, int backlog){

    socket = new ListeningSocket(domain, service, protocol, port, yourIP, backlog);
    // to avoid memory leak, make sure you delete the ListeningSocket after every use.


}

NET::ListeningSocket* NET::SimpleServer::get_socket(){
    return socket;
}