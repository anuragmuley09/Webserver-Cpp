#include "TestServer.hpp"
#include <ws2tcpip.h>
#include <winsock2.h>
#include <sstream>


/*
Potential weakness.
What am i doing now is, each time client is hitting some endpoint, then iam rendering html info.
what if i render all of this just once and store the rendered html in some key value pair like?


i can use map, like {endpoint: respective rendered html file} like this?


*/


/* 
Changes required:
    1. Use map to implement url endpoint + respective html source code.
    2. check how to render html source code. 
Updates:
    1. I need to work on maps.
    2. Iam able to render html code now, but idk if its supposed to be this way, or now. Research.
*/


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

    std::string file_path;
    // Check if the requested path exists in the URLs set
    if (urls.find(requested_path) != urls.end()) {
        // response = "You have reached the " + requested_path + " page!";
        std::cout<<requested_path<<std::endl;
        file_path = "HTMLFiles"+requested_path + ".html";
        response = url_mapping[requested_path];
    } else {
        file_path = "HTMLFiles/fileNotFound.html"; 
        response = render_html(file_path); 
    }

    // response = render_html(file_path);

    // Create HTTP response
    std::string http_response = "HTTP/1.1 200 OK\r\nContent-Length: " + 
                                std::to_string(response.size()) + "\r\n\r\n" + response;
    send(new_socket, http_response.c_str(), http_response.size(), 0);
    closesocket(new_socket);
}


/* render html file */
/* idk if this is correct method or not, but as of now its works! */
std::string NET::TestServer::render_html(std::string file_path){
    std::string response;
    std::ifstream html_file(file_path);
    if (html_file) {
        std::stringstream buffer;
        /* sometime we use >> and sometimes << ...whyyy? */
        /* its same in context with cin and cout */
        /*
        << for inserting in stream and >> for extracting from stream!
        */
        buffer << html_file.rdbuf(); // Read the entire file into the buffer, 
        response = buffer.str();
        // std::cout<<"here"<<std::endl;
    } else {
        // if file is not found
        // this will not execute, cause i have "fileNotFound.html" ... cause why not :)
        response = "<html><body><h1>404 requested file Not Found</h1></body></html>";
    }
    return response;
}


void NET::TestServer::start_loop() {
    add_urls(); 
    while (true) {
        std::cout << "<-------------Waiting for connection------------->" << std::endl;
        accept_request(); // Accept the client request
        handle_request(); // Process the request
        respond_request(); // Send the appropriate response
        std::cout << "<-------------Execution Done------------->" << std::endl;
    }
}

void NET::TestServer::add_urls() {
    urls.insert("/home");
    urls.insert("/about");
    urls.insert("/hello");
    urls.insert("/contact");
}


// extract the path from the HTTP request
std::string NET::TestServer::extract_path_from_request(const char buffer[]) {
    std::string request(buffer);
    std::istringstream request_stream(request);
    std::string method, path;

    request_stream >> method; // Extract the HTTP method (e.g., GET)
    request_stream >> path;   // Extract the requested path (e.g., /favicon.ico), favicon stands for fav icon...the one which we see on left side of tab bar.

    return path; // Return the extracted path
}

/* testing this new concept */
void NET::TestServer::add_url_in_map() {
    for (const auto& url : urls) {
        std::string file_path = "HTMLFiles" + url + ".html";
        url_mapping[url] = render_html(file_path); // Cache rendered HTML
    }
}
