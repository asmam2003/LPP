    #include <iostream>
    #include <stdio.h>
    #include <stdlib.h>
    #include <sys/types.h>
    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <unistd.h>
    #include <netdb.h>
    #include <netdb.h>
    #include <arpa/inet.h>
    #include <string.h>
    #include <string>



    int SocketTest = socket(AF_INET, SOCK_STREAM, 0);
    sockaddr_in server_address, client_address;
    int client_socket = socket(AF_INET, SOCK_STREAM, 0);


    int server () {

    if (SocketTest==-1){
    std:: cout << "failed to find protocal";
    return -1;
    }
    else
    std::cout << "succusfully found protocal" << std::endl ; // creation of socket

    // might need to close SocketTest after transmission. 0 if success, -1 if not, but the if statement might do that anyways

    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(5000); // port number, change if needed


    std::cout<<server_address.sin_port << std:: endl;


    bind(SocketTest, (struct sockaddr *)&server_address, sizeof(server_address));
    listen(SocketTest, 5);




    int client_length = sizeof(client_address);

    client_socket = accept(SocketTest, (struct sockaddr *)&client_address,(socklen_t*)&client_length); //Accepting call


    char buffer [4094];
    read(client_socket, buffer, sizeof(buffer));

    std::cout << buffer << std::endl;



    close(client_socket);
    close(SocketTest);


    return 0;
    }





    int client () {

    int client_socket;
    sockaddr_in server_address;


    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(5000);
    server_address.sin_addr.s_addr = inet_addr("10.5.61.50");

    connect(SocketTest, (struct sockaddr *)&server_address, sizeof(server_address));


        char buffer[0];
        buffer [1]='!';


    write(SocketTest, buffer, sizeof(buffer));




    return 0;
    }

    int main () {
    client();

    return 0;

    }
