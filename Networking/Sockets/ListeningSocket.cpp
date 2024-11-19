

#include "ListeningSocket.hpp"

NET::ListeningSocket::ListeningSocket(int domain, int service, int protocol, int port, u_long yourIP, int bklog) : 
                        BindingSocket(domain, service, protocol, port, yourIP)
{
    set_backlog(bklog);
    start_listening();
    test_conenction(listening);
}



void NET::ListeningSocket::start_listening(){
    std::cout<<get_connection()<<std::endl;
    listening = listen(get_sock(), backlog); // get_connection()..?


}

void NET::ListeningSocket::set_backlog(int bklog){
    backlog = bklog;
}

int NET::ListeningSocket::get_backlog(){
    return backlog;
}
