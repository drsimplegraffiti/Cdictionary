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
