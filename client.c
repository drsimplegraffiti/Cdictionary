#include
#include
#include
#include
#include <arpa/inet.h>

#define PORT 8080
#define BUFFER_SIZE 1024

int main() {
  int sock_fd;
  struct sockaddr_in server_address;
  char buffer[BUFFER_SIZE] = {0};
  char *message = "Hello from client";

  // 1. create socket
  sock_fd = socket(AF_INET, SOCK_STREAM, 0);
  if (sock_fd < 0) {
    perror("socket failed");
    return 1;
  }

  // 2. set server address
  server_address.sin_family = AF_INET;
  server_address.sin_port = htons(PORT);

  // convert "127.0.0.1" string to binary
  if (inet_pton(AF_INET, "127.0.0.1", &server_address.sin_addr) <= 0) {
    perror("invalid address");
    return 1;
  }

  // 3. connect to server
  if (connect(sock_fd, (struct sockaddr *)&server_address,
              sizeof(server_address)) < 0) {
    perror("connection failed");
    return 1;
  }

  printf("connected to server\n");

  // 4. send message
  send(sock_fd, message, strlen(message), 0);
  printf("message sent: %s\n", message);

  // 5. read response
  read(sock_fd, buffer, BUFFER_SIZE);
  printf("server says: %s\n", buffer);

  // 6. close socket
  close(sock_fd);

  return 0;
}
