#include <stdio.h>
#include <netdb.h>
#include <strings.h>
#include <unistd.h>
#include <pthread.h>

// Global constants
#define SERVER_PORT 3233
#define BUFFER_SIZE 256
#define CONNECTION_ESTABLISHED "Connection established!\n"

void *handle_connection(void *socket);


int main(void)
{
    // 1. create a socket
    int socket_fd;

    if ((socket_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        fprintf(stderr, "Could not create socket");
        return 1;
    }

    // 2. bind the socket
    struct sockaddr_in server;

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = htonl(INADDR_ANY);
    server.sin_port = htons(SERVER_PORT);
    if (bind(socket_fd, (struct sockaddr *) &server, sizeof(server)) == -1) {
        fprintf(stderr, "Could not bind to port %u", SERVER_PORT);
        return 1;
    }

    // 3. listen on the socket
    int max_connection = 1;

    if (listen(socket_fd, max_connection) == -1) {
        fprintf(stderr, "Failed to listen");
        return 1;
    }
    fprintf(stdout, "Start listening on port %u...\n", SERVER_PORT);

    // 4. accept connection
    struct sockaddr_in client;
    int client_socket_fd, client_size;

    client_size = sizeof(struct sockaddr_in);
    while (1) {
        client_socket_fd = accept(
            socket_fd,
            (struct sockaddr *) &client,
            (socklen_t *) &client_size
        );

        if (client_socket_fd == -1) {
            fprintf(stderr, "Failed to accept new connection");
            return 1;
        }

        // create new thread for handling the client connection
        pthread_t client_thread;

        if (pthread_create(
                &client_thread,
                NULL,
                handle_connection,
                &client_socket_fd) == -1) {
            fprintf(stderr, "Could not create thread");
            return 1;
        }
    }

    // close the socket
    close(socket_fd);
}

void *handle_connection(void *socket)
{
    int client_socket_fd = *((int *) socket);
    char message[BUFFER_SIZE + 3], *error_message;

    // 5. send/receive data
    char buffer[BUFFER_SIZE];
    int read_size;

    strcpy(message, "Connection established!\n");
    write(client_socket_fd, message, strlen(message));

    bzero(buffer, BUFFER_SIZE);
    while ((read_size = recv(client_socket_fd, buffer, BUFFER_SIZE, 0)) > 0) {
        fprintf(stdout, "-- Received: %s", buffer);

        strcpy(message, "-- ");
        strcat(message, buffer);
        if (write(client_socket_fd, message, strlen(message)) == -1) {
            error_message = "Error: could not write to socket";

            fprintf(stderr, "%s", error_message);
            pthread_exit(error_message);
        }
    }

    if (read_size == 0) {
        fprintf(stderr, "Client disconnected!\n");
    }
    else if (read_size == -1) {
        error_message = "Error: could not read data from socket";

        fprintf(stderr, "%s", error_message);
        pthread_exit(error_message);
    }

    close(client_socket_fd);
    pthread_exit(0);
}
