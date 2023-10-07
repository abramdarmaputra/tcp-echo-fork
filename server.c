#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

#define PORT 5000
#define MAX_CONN 5
#define BUFFER_SIZE 1024

void handle_client(int client_socket)
{
    char buffer[BUFFER_SIZE];
    ssize_t bytes_received;

    while (1)
    {
        bytes_received = recv(client_socket, buffer, sizeof(buffer), 0);
        if (bytes_received <= 0)
        {
            break;
        }
        buffer[bytes_received] = '\0';
        printf("Received: %s", buffer);

        send(client_socket, buffer, strlen(buffer), 0);
    }

    close(client_socket);
}

int main()
{
    int server_socket, client_socket;
    struct sockaddr_in server_address, client_address;
    socklen_t client_len = sizeof(client_address);
    pid_t child_pid;

    signal(SIGCHLD, SIG_IGN);

    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == -1)
    {
        perror("Error creating socket");
        exit(EXIT_FAILURE);
    }

    memset(&server_address, 0, sizeof(server_address));
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = INADDR_ANY;
    server_address.sin_port = htons(PORT);

    if (bind(server_socket, (struct sockaddr *)&server_address, sizeof(server_address)) == -1)
    {
        perror("Error binding");
        exit(EXIT_FAILURE);
    }

    if (listen(server_socket, MAX_CONN) == -1)
    {
        perror("Error listening");
        exit(EXIT_FAILURE);
    }

    printf("Server listening on port %d\n", PORT);

    while (1)
    {
        client_socket = accept(server_socket, (struct sockaddr *)&client_address, &client_len);
        if (client_socket == -1)
        {
            perror("Error accepting connection");
            continue;
        }

        child_pid = fork();

        if (child_pid == -1)
        {
            perror("Error forking");
            close(client_socket);
            continue;
        }

        if (child_pid == 0)
        {
            close(server_socket);
            handle_client(client_socket);
            exit(EXIT_SUCCESS);
        }
        else
        {
            close(client_socket);
        }
    }

    close(server_socket);

    return 0;
}
