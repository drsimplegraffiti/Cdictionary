#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>


#define PORT 8080
#define BUFFER_SIZE 1024

int main() {
  int server_fd, client_fd;
  struct sockaddr_in address;
  int addrlen = sizeof(address);
  char buffer[BUFFER_SIZE] = {0};
  char *response = "Hello from server";

  // 1. create socket
  server_fd = socket(AF_INET, SOCK_STREAM, 0);
  if (server_fd == 0) {
    perror("socket failed");
    return 1;
  }

  // optional: reuse port immediately after restart
  int opt = 1;
  setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

  // 2. bind to port
  address.sin_family = AF_INET;
  address.sin_addr.s_addr = INADDR_ANY; // listen on all interfaces
  address.sin_port = htons(PORT);       // host to network byte order

  if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
    perror("bind failed");
    return 1;
  }

  // 3. listen for connections
  if (listen(server_fd, 3) < 0) {
    perror("listen failed");
    return 1;
  }

  printf("server listening on port %d\n", PORT);

  // 4. accept a connection
  client_fd =
      accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen);
  if (client_fd < 0) {
    perror("accept failed");
    return 1;
  }

  printf("client connected\n");

  // 5. read message from client
  read(client_fd, buffer, BUFFER_SIZE);
  printf("client says: %s\n", buffer);

  // 6. send response
  send(client_fd, response, strlen(response), 0);
  printf("response sent\n");

  // 7. close sockets
  close(client_fd);
  close(server_fd);

  return 0;
}
