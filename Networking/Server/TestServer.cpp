#include "TestServer.hpp"
#include <ws2tcpip.h>
#include <winsock2.h>
#include <sstream>

NET::TestServer::TestServer() : 
                SimpleServer(AF_INET, SOCK_STREAM, 0, 80, INADDR_ANY, 10)
{
    start_loop(); // launching server
}

void NET::TestServer::accept_request() {
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

void NET::TestServer::handle_request() {
    if (strlen(buffer) > 0) {
        // Log the entire HTTP request
        std::cout << "Received HTTP Request:\n" << buffer << std::endl;

        // Extract the requested path from the HTTP request
        requested_path = extract_path_from_request(buffer);
        std::cout << "Extracted Path: " << requested_path << std::endl;
    } else {
        std::cerr << "No data received or buffer is empty." << std::endl;
    }
}

void NET::TestServer::respond_request() {
    std::string response;

    // Check if the requested path exists in the URLs set
    if (urls.find(requested_path) != urls.end()) {
        response = "You have reached the " + requested_path + " page!";
    } else {
        response = "URL Not Found";
    }

    // Create HTTP response
    std::string http_response = "HTTP/1.1 200 OK\r\nContent-Length: " + 
                                std::to_string(response.size()) + "\r\n\r\n" + response;
    send(new_socket, http_response.c_str(), http_response.size(), 0);
    closesocket(new_socket);
}

void NET::TestServer::start_loop() {
    while (true) {
        std::cout << "<-------------Waiting for connection------------->" << std::endl;
        add_urls(); // Load available URLs
        accept_request(); // Accept the client request
        handle_request(); // Process the request
        respond_request(); // Send the appropriate response
        std::cout << "<-------------Execution Done------------->" << std::endl;
    }
}

/* Changes required:
    1. Use map to implement url endpoint + respective html source code.
    2. check how to render html source code. 
*/
void NET::TestServer::add_urls() {
    urls.insert("/home");
    urls.insert("/about");
    urls.insert("/hello");
    urls.insert("/contact");
}

// Helper function to extract the path from the HTTP request
std::string NET::TestServer::extract_path_from_request(const char buffer[]) {
    std::string request(buffer);
    std::istringstream request_stream(request);
    std::string method, path;

    request_stream >> method; // Extract the HTTP method (e.g., GET)
    request_stream >> path;   // Extract the requested path (e.g., /favicon.ico)

    return path; // Return the extracted path
}