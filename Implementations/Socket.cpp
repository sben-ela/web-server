/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Socket.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sben-ela <sben-ela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 17:12:03 by aybiouss          #+#    #+#             */
/*   Updated: 2023/10/12 11:03:24 by sben-ela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/Socket.hpp"
#include "../Includes/Response.hpp"

void Socket::setnonblocking(int *sock)
{
	int opts;

	opts = fcntl(*sock,F_GETFL);
	if (opts < 0) {
		perror("fcntl(F_GETFL)");
		exit(EXIT_FAILURE);
	}
	opts = (opts | O_NONBLOCK);
	if (fcntl(*sock,F_SETFL,opts) < 0) {
		perror("fcntl(F_SETFL)");
		exit(EXIT_FAILURE);
	}
	return ;
}

int Socket::function() {
    int server_fd;
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) <= 0) {
        perror("Cannot create socket");
        // fprintf(stderr, "socket() failed. (%d)\n", GETSOCKETERRNO());
        return 1;
    }
    int opt = 1;
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0) {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }

    //It creates a socket using socket() with the address family (AF_INET for IPv4) and socket type (SOCK_STREAM for a TCP socket). If socket() fails, it prints an error message using perror() and returns 0.
    struct sockaddr_in address; // is defined to store socket address information.
    memset((char *)&address, 0, sizeof(address));
    address.sin_family = AF_INET; //address family (sin_family) to AF_INET for IPv4
    address.sin_addr.s_addr = htonl(INADDR_ANY); //sin_addr.s_addr) to INADDR_ANY to listen on all available network interfaces
    address.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("Bind failed");
        // fprintf(stderr, "bind() failed. (%d)\n", GETSOCKETERRNO());
        return 1;
    } // binds the socket to the IP address and port defined in address
    setnonblocking(&server_fd);
    if (listen(server_fd, MAX_CLIENTS) < 0) {
        perror("Listen failed");
        // fprintf(stderr, "listen() failed. (%d)\n", GETSOCKETERRNO());
        exit(EXIT_FAILURE);
    } // listens for incoming connections on the server socket (server_fd).
    
    int client_socket[MAX_CLIENTS] = {0}; // store client socket descriptors. It is initialized to all zeros.
    fd_set read_fds; //fd_set is a data structure used to manage file descriptors for I/O operations.
    // Fill up a fd_set structure with the file descriptors you want to know when data comes in on.
    int max_sd; //will store the maximum file descriptor value for use in select()

    while (1) {
        FD_ZERO(&read_fds); // clears all file descriptors in the read_fds set.
        FD_SET(server_fd, &read_fds); // adds the server socket server_fd to the read_fds set.
        max_sd = server_fd;

        for (int i = 0; i < MAX_CLIENTS; i++) {
            if (client_socket[i] > 0) { //indicates an open socket
                FD_SET(client_socket[i], &read_fds);
                if (client_socket[i] > max_sd) {
                    max_sd = client_socket[i];
                }
            }
        }

        int activity = select(max_sd + 1, &read_fds, NULL, NULL, NULL);
        
        if ((activity < 0) && (errno != EINTR)) {
            perror("Select error");
        }

        if (FD_ISSET(server_fd, &read_fds)) {  //checks if the server socket (server_fd) is ready for reading, which means there's an incoming connection request from a client.
            int new_socket;
            socklen_t addrlen = sizeof(address);
            if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen)) < 0) {
                perror("Accept error");
                exit(EXIT_FAILURE);
            } // is used to accept this incoming connection. It creates a new socket descriptor (new_socket) for this specific client connection. The client's address information is stored in address.
            setnonblocking(&new_socket);
            for (int i = 0; i < MAX_CLIENTS; i++) {
                if (client_socket[i] == 0) {
                    client_socket[i] = new_socket;
                    break;
                }
            }
        }
        for (int i = 0; i < MAX_CLIENTS; i++) {
            int sd = client_socket[i];
            if (FD_ISSET(sd, &read_fds))
            {
                char buffer[1024] = {0};
                Response response;
                int valread = recv(sd, buffer, 1024, 0);
                if (valread <= 0) {
                    perror("Read error");
                }
                // response.parseHttpRequest(buffer, sd);
                // std::cout << request.getMethod()<< std::endl;
                // std::cout << request.getPath() << std::endl;
                // std::cout << request.getHttpVersion() << std::endl;
                const char *hello = "HTTP/1.1 200 OK\nContent-Type: text/plain\nContent-Length: 12\n\nHello world!";
                write(sd, hello, strlen(hello));
                // std::cout << " IN COCKET.CPP" << std::endl;
                ft_close(sd);
                // std::cout << response.getResponseStatus() << std::endl;
                std::cout << "--------------------" << std::endl;
                response.Function();
                std::cout << "--------------------" << std::endl;
                client_socket[i] = 0;
            }
        }
    }
    return 0;
}
// It uses select() to efficiently manage multiple client connections, and it maintains an array of client socket descriptors to keep track of active connections. When a client sends a request, it is parsed and processed, and a response is sent back to the client.

//page 76 !!!! chapter 2
//page 215 !!! chapter 7

// https://www.ibm.com/docs/en/i/7.2?topic=designs-example-nonblocking-io-select


