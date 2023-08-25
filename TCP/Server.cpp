#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <unistd.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <string.h>
#include <string>

    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    int client_socket = socket(AF_INET, SOCK_STREAM, 0);

    int server() {
    if (serverSocket == -1) {
        std::cout << "Failed to create socket" << std::endl;
        return -1;
    }

    sockaddr_in server_address, client_address;
    socklen_t client_length = sizeof(client_address);

    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(5000); // Port number, change if needed

    bind(serverSocket, (struct sockaddr*)&server_address, sizeof(server_address));
    listen(serverSocket, 5);

    int client_socket = accept(serverSocket, (struct sockaddr*)&client_address, &client_length);
    std::cout << "Client connected"<<std::endl;

    while (true) {
    char buffer[1024];


    int bytesReceived = recv(client_socket, buffer, sizeof(buffer), 0); // the message from client
        if (bytesReceived <= 0) {
        std::cout << "Client disconnected." << std::endl;
        break;
}

    std::cout << "Client: " << buffer << std::endl;
    if (buffer=="exit") {
        std::cout << "Client requested to exit." << std::endl;
        break;
    }
    std::string response;
    std::cout << "Server: ";
    std::cin >> response;
    send(client_socket, response.c_str(), response.size(), 0);
        if (response=="exit") {
        std::cout << "Server exiting." << std::endl;
        break;
    }
}


    close(client_socket);
    close(serverSocket);

    return 0;
}

    
    int main() {


        server();


    return 0;
}
