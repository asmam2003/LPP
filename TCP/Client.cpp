  int client() {
    int client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket == -1) {
        std::cout << "Failed to create socket" << std::endl;
        return -1;
    }

    struct sockaddr_in server_address;

    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(5000);
    server_address.sin_addr.s_addr = inet_addr("10.5.61.50");

    connect(client_socket, (struct sockaddr*)&server_address, sizeof(server_address));

    while (true) {
    std::string message;
    std::cout << "Enter a message to send: ";
    std::cin >> message;
    send(client_socket, message.c_str(), message.size(), 0);

    if (message == "exit") {
        close(client_socket);
        std::cout << "exiting" << std::endl;
        break;
    }

    char buffer[1024];

    int bytesReceived = recv(client_socket, buffer, sizeof(buffer), 0);

    if (bytesReceived <= 0) {
        std::cout << "Server disconnected." << std::endl;
        break;
    }

    std::cout << "Server: " << buffer << std::endl;
}


    close(client_socket);

    return 0;
}
