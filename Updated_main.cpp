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

int server() {
    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == -1) {
        std::cout << "Failed to create socket" << std::endl;
        return -1;
    }

    sockaddr_in server_address, client_address;
    socklen_t client_length = sizeof(client_address);

    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(5000); // Port number, change if needed
    server_address.sin_addr.s_addr = INADDR_ANY;

    bind(serverSocket, (struct sockaddr*)&server_address, sizeof(server_address));
    listen(serverSocket, 5);

    int client_socket = accept(serverSocket, (struct sockaddr*)&client_address, &client_length);

    while (true) {
        char buffer[1024];
        memset(buffer, 0, sizeof(buffer));

        // Receive message from client
        recv(client_socket, buffer, sizeof(buffer), 0);
        std::cout << "Client: " << buffer << std::endl;

        // Send response to client
        std::string response;
        std::cout << "Enter your response: ";
        std::getline(std::cin, response);
        send(client_socket, response.c_str(), response.size(), 0);
    }

    close(client_socket);
    close(serverSocket);

    return 0;
}

int client() {
    int client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket == -1) {
        std::cout << "Failed to create socket" << std::endl;
        return -1;
    }

    struct sockaddr_in server_address;

    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(5000);
    server_address.sin_addr.s_addr = inet_addr("127.0.0.1"); // Change to the server's IP

    connect(client_socket, (struct sockaddr*)&server_address, sizeof(server_address));

    while (true) {
        std::string message;
        std::cout << "Enter a message to send: ";
        std::getline(std::cin, message);
        send(client_socket, message.c_str(), message.size(), 0);

        char buffer[1024];
        memset(buffer, 0, sizeof(buffer));

        // Receive response from server
        recv(client_socket, buffer, sizeof(buffer), 0);
        std::cout << "Server: " << buffer << std::endl;
    }

    close(client_socket);

    return 0;
}

int main() {


        server();
        client();


    return 0;
}
