

#include "ListeningSocket.hpp"

NET::ListeningSocket::ListeningSocket(int domain, int service, int protocol, int port, u_long yourIP, int backlog) : 
                        BindingSocket(domain, service, protocol, port, yourIP)
{
    set_backlog(backlog);
    start_listening();
    test_conenction(listening);
}



void NET::ListeningSocket::start_listening(){
    std::cout<<get_sock()<<std::endl;
    listening = listen(get_sock(), backlog); 
}

void NET::ListeningSocket::set_backlog(int backlog){
    this->backlog = backlog;
}

int NET::ListeningSocket::get_backlog(){
    return backlog;
}
