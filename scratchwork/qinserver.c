#include<netinet/in.h>    
#include<stdio.h>    
#include<stdlib.h>    
#include<sys/socket.h>    
#include<sys/types.h>    
#include<unistd.h>
#include<string.h>
#include<stdbool.h>

// use -std=c11 to compile this since i used c++ style comments
// change the port number or any of the defs below
#define BUFSIZE 4096 // a relatively large buffer size
#define PORT 18888 // arbitrarily picked port number
#define LISTEN_BACKLOG 128 // large enough for our purposes

int int_len(int n) {
    int len = 0;
    while(n > 0) {
        n /= 10;
        ++len;
    }
    return len;
}

int main() {
    int listensd, connsd; // listen and connection socket descriptors
    socklen_t addrlen; // size of our socket address
    struct sockaddr_in address; // structure for our socket address
    char buffer[BUFSIZE]; // all purpose buffer of BUFSIZE

    // create the OS data structure for a socket
    // AF_INET basically tells that its IP
    // and SOCK_STREAM basically says TCP
    if ((listensd = socket(AF_INET, SOCK_STREAM, 0)) >= 0){
        printf("socket %d created...\n", listensd);
    } else {
        perror("socket() system call error.");
        exit(1);
    }

    address.sin_family = AF_INET; // IP or internet protocol
    address.sin_addr.s_addr = INADDR_ANY; // is 0 in most cases, can bind to localhost or actual ip
    address.sin_port = htons(PORT);

    // this step will makes our socket a server socket and not a client socket
    // os updates the underlying socket with more information including server address information
    if (bind(listensd, (struct sockaddr *)&address, sizeof(address)) == 0){
        printf("socket %d bound...\n", listensd);
    } else {
        perror("bind() system call error.");
        exit(1);
    }

    while (true) {
        // listensd is now waiting for tcp/ip connection requests
        if (listen(listensd, LISTEN_BACKLOG) < 0) {
            perror("listen() system call error.");
            exit(1);
        } else
            printf("socket %d listening...\n", listensd);

        // accept() combines with listen() to complete a tcp/ip connection
        // and creates a new socket for the accepted client to communicate
        // with the server
        // client address information is received
        if ((connsd = accept(listensd, (struct sockaddr *)&address, &addrlen)) < 0) {
            perror("accept() system call error.");
            exit(1);
        } else
            printf("socket %d connected with client (%d.%d.%d.%d)...\n",
                    connsd,
                    (char)address.sin_addr.s_addr,
                    (char)(address.sin_addr.s_addr >> 8),
                    (char)(address.sin_addr.s_addr >> 16),
                    (char)(address.sin_addr.s_addr >> 24));

        // note that various members of the address struct which are transmitted
        // through the network protocol are big endian as dictated by the protocol

        // print data received from client,
        // we assume its an http GET request although it needn't be =)
        // we don't have to hard exit() at this point, life goes on
        if(recvfrom(connsd, buffer, BUFSIZE, 0, NULL, NULL) < 0)
            perror("recv() system call error.");
        else
            printf("socket %d received:\n%s\n", connsd, buffer);

        // format response which will be a
        // http header followed by simple html
        sprintf(buffer, "HTTP/1.1 200 OK\n\
Content-length: %d\n\
Content-Type: text/html\n\n\
<html><body><H1>Server socket %d: Qin!</H1></body></html>", 55+int_len(connsd), connsd);

        // send the http response
        int sent = 0;
        int tosend = (int)strlen(buffer);
        while(sent < tosend) {
            int written = write(connsd, buffer, tosend-sent);
            if (written > 0) {
                sent += written;
                printf("socket %d has written %d bytes...\n", connsd, sent);
            } else {
                perror("write() system call error.");
                break;
            }
        }

        if(close(connsd) == -1)
            perror("close() system call error connection descriptor.");    
    } 

    // in this simplistic example this code will never be reached
    // i just put it here for good measure
    if(close(listensd) == -1)
        perror("close() system call error listening descriptor.");    

    return 0;    
}

