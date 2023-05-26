/*
Implementing a TCP server-client chat application using C/C++ involves the following steps:

Create a TCP socket: The first step is to create a TCP socket using the socket() function. This socket will be used to establish a connection between the server and client.

Bind the socket to an IP address and port number: After creating the socket, you need to bind it to a specific IP address and port number using the bind() function. This will enable the server to listen for incoming connections on the specified port.

Listen for incoming connections: Once the socket is bound, the server can start listening for incoming connections using the listen() function.

Accept incoming connections: When a client tries to connect to the server, the accept() function is used to accept the incoming connection and create a new socket for communication with the client.

Send and receive messages: After the connection is established, both the client and server can send and receive messages using the send() and recv() functions respectively.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

#define PORT 8080

int main(int argc, char const *argv[]) {
    int sock = 0, valread;
    struct sockaddr_in serv_addr;
    char *hello = "Hello from client";
    char buffer[1024] = {0};
    
    // Create socket
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("\n Socket creation error \n");
        return -1;
    }
   
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
       
    // Convert IPv4 and IPv6 addresses from text to binary form
    if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0) {
        printf("\nInvalid address/ Address not supported \n");
        return -1;
    }
   
    // Connect to server
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        printf("\nConnection Failed \n");
        return -1;
    }
   
    // Send and receive messages
    send(sock , hello , strlen(hello) , 0 );
    printf("Hello message sent\n");
    valread = read( sock , buffer, 1024);
    printf("%s\n",buffer );
    return 0;
}
