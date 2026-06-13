## Client Server Socket in C

### server.c
```c
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
    client_fd = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen);
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
```

---

### client.c
```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
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
    if (connect(sock_fd, (struct sockaddr *)&server_address, sizeof(server_address)) < 0) {
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
```

---

### Makefile
```makefile
all: server client

server: server.c
	gcc server.c -o server

client: client.c
	gcc client.c -o client

clean:
	rm -f server client
```

---

### Run

```bash
make

# terminal 1 - start server first
./server

# terminal 2 - run client
./client
```

### Expected output

```bash
# server terminal
server listening on port 8080
client connected
client says: Hello from client
response sent

# client terminal
connected to server
message sent: Hello from client
server says: Hello from server
```

---

### How it works

```
socket()    create a socket file descriptor
bind()      attach socket to a port (server only)
listen()    mark socket as passive - wait for connections (server only)
accept()    block and wait for a client to connect (server only)
connect()   initiate connection to server (client only)
send()      send data through socket
read()      receive data from socket
close()     close the connection
```

### Socket flow

```
SERVER                          CLIENT
socket()                        socket()
bind()
listen()
accept() ←——————————————————— connect()
read()   ←——————————————————— send("Hello from client")
send()   ———————————————————→ read()
close()                         close()
```

### Key concepts

```
AF_INET         IPv4
SOCK_STREAM     TCP (reliable, ordered)
SOCK_DGRAM      UDP (fast, no guarantee) - different setup
INADDR_ANY      listen on all network interfaces (0.0.0.0)
htons()         host to network byte order (endianness)
inet_pton()     convert IP string "127.0.0.1" to binary
127.0.0.1       loopback - talks to yourself (same machine)
```
