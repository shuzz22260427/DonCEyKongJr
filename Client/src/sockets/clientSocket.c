#include "clientSocket.h"

int send_Message(char ip_addr [] ,int port,char *msg){
    int sock = 0;
    struct sockaddr_in serv_addr;
    char *out_Data = msg;

    // Linux && MacOS
    /*if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("%d")
        printf("\n Socket creation error \n");
        goto end;
    }*/

    // Windows
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) != INVALID_SOCKET)
    {
        printf("\n Socket creation error \n");
        goto end;
    }
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(port);
    serv_addr.sin_addr.s_addr = inet_addr(ip_addr);

    // Convert IPv4 and IPv6 addresses from text to binary form

    // Linux & MacOS
    /*if(inet_pton(AF_INET, ip_addr, &serv_addr.sin_addr)<=0)
    {
        printf("\nInvalid address/ Address not supported \n");
        goto end;
    }*/

    //Windows
    /*if(inet_pton(AF_INET, ip_addr, &serv_addr.sin_addr)<=0)
    {
        printf("\nInvalid address/ Address not supported \n");
        goto end;
    }*/

    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        printf("\nConnection Failed \n");
        goto end;
    }
    send(sock , out_Data , strlen(out_Data) , 0 );
    printf("Message sent succesfully\n");

    //Finally closes the connections
    close(sock);
    return 0;

    end:
    return -1;
}


char* recv_Message(int port){
    int server_fd, new_socket, valread;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    char *buffer = {0};

    // Creating socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // Forcefully attaching socket to the port 8080

    //For Unix OS -> Linux and MACOS
    /*if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,
                   &opt, sizeof(opt)))*/
    // For WindowsOS, the SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT is SO_REUSEADDR
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR,
                   (const char *) &opt, sizeof(opt)))
    {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons( port );

    // Forcefully attaching socket to the port 8080
    if (bind(server_fd, (struct sockaddr *)&address,
             sizeof(address))<0)
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    if (listen(server_fd, 3) < 0)
    {
        perror("listen");
        exit(EXIT_FAILURE);
    }
    if ((new_socket = accept(server_fd, (struct sockaddr *)&address,
                             (socklen_t*)&addrlen))<0)
    {
        perror("accept");
        exit(EXIT_FAILURE);
    }
    valread = read( new_socket , buffer, 1024);
    printf("%s\n",buffer );

    close(new_socket);
    close(server_fd);
    return buffer;
}