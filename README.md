
# HTTP SERVER

Understanding an HTTP server involves grasping various concepts, from basic networking and the HTTP protocol to server architecture and security considerations

### Basics of HTTP and Networking
- HTTP (HyperText Transfer Protocol): The foundation of data communication on the web. It defines how messages are formatted and transmitted, and how web servers and browsers should respond to various commands.
- TCP/IP (Transmission Control Protocol/Internet Protocol): The suite of communication protocols used to interconnect network devices on the internet. HTTP typically runs over TCP.
- Client-Server Model: The basic architecture where a client (such as a web browser) sends requests to a server, which processes these requests and returns the appropriate responses.

HTTP (HyperText Transfer Protocol) and TCP/IP (Transmission Control Protocol/Internet Protocol) are fundamental technologies that enable web communication. Understanding their relationship is crucial for grasping how data is transmitted over the internet. And this can be understood by talking about the Open Systems Interconnection model (OSI 7 Layer)

### TCP/IP Model Layers
1. Application Layer: This is called the top layer or layer 7 and it's the layer users interact with like web browsing, file transfers, mobile applications etc. This layer provides network services to the end user, the layer defines the rules of web communication, which encompasses how requests and responses are formatted and transmitted e.g HTTP
2. The Presentation Layer: This layer performs the task of converting data from one format to the other. This layer is where tasks like decryption, encryption, data translating/formatting, data compression and other adjoining stuffs take place.
3. The Session Layer: This is the layer of connections. This where connections are established, directed, authenticated and even terminated.
4. Transport Layer: This layer helps in transmitting data in packets. It determines how much data is transmitted, how fast, destination etc. The most widely used protocol for transmission is TCP(Transmission Control Protocol) and UDP (User Datagram Protocol).
5. Network Layer: This layer routes the data. Here we probe the data to determine if it has reached it's destination or not. Its able to determine this based on the IP portion of the TCP.
6. Data Link Layer: Its subdivided to Media Access Control and Logical Link Control. This layer sets up links across physical layers
7. Physical Layer: Handles the connection between devices. This layer includes transimission of data over physical stuffs like cables, switches, routers and network interface cards.


How HTTP Uses TCP/IP
HTTP relies on the underlying TCP/IP protocols to function. Here’s a step-by-step breakdown of how an HTTP request and response are transmitted using TCP/IP:

HTTP Request Creation:

When a user requests a web page, the web browser (client) constructs an HTTP request message. This message includes the method (e.g., GET, POST, DELETE etc), the URL, headers, and possibly a body (for methods like POST).
TCP Connection Establishment:

The client initiates a TCP connection to the web server using the server’s IP address and the default HTTP port (usually port 80 for HTTP or port 443 for HTTPS).
TCP performs a three-way handshake to establish a connection:
SYN: The client sends a synchronization packet to the server.
SYN-ACK: The server responds with a synchronization-acknowledgment packet.
ACK: The client sends an acknowledgment packet back to the server.
Data Transmission:

Once the TCP connection is established, the HTTP request message is sent from the client to the server through this connection.
TCP ensures the data is delivered reliably and in the correct order by dividing it into segments, sending them, and retransmitting any lost segments.
IP Packet Routing:

The TCP segments are encapsulated in IP packets. Each IP packet contains source and destination IP addresses.
The IP protocol handles the routing of these packets across the internet, ensuring they reach the correct destination.
HTTP Response:

The web server processes the HTTP request and generates an HTTP response message, which includes the status code (e.g., 200 OK), headers, and the requested content (e.g., HTML, images).
This HTTP response is sent back to the client using the same TCP connection.
TCP Connection Termination:

After the HTTP response is delivered, the TCP connection is closed using a four-way handshake:
FIN: The client sends a finish packet to the server.
ACK: The server acknowledges the finish packet.
FIN: The server sends its own finish packet to the client.
ACK: The client acknowledges the server’s finish packet.

### Components of an HTTP Server
Socket: An endpoint for sending or receiving data across a network. HTTP servers listen for requests on a specific IP address and port number.
Request Handling: HTTP servers parse incoming requests, extract necessary information (method, path, headers, body), and route them to the appropriate handlers.
Response Generation: After processing the request, the server generates a response that typically includes a status line, headers, and a body.


### HTTP Protocol Details
Methods: The most common HTTP methods include GET (retrieve data), POST (submit data), PUT (update data), DELETE (remove data), and others.
Status Codes: Indicate the result of the HTTP request. Common status codes include:
200 OK: The request was successful.
404 Not Found: The requested resource was not found.
500 Internal Server Error: A generic error message indicating a server-side problem.
Headers: Key-value pairs in both requests and responses that convey additional information such as content type, content length, cookies, caching policies, etc.
Body: The main data of the request or response. In a GET request, the body is usually empty, whereas in a POST request, it contains the data to be sent.


### Server Architecture
Single-threaded vs. Multi-threaded: Single-threaded servers handle one request at a time, while multi-threaded servers can handle multiple requests concurrently.
Event-driven vs. Blocking I/O: Event-driven (non-blocking) I/O allows a server to handle many connections simultaneously without waiting for each one to complete, improving scalability.
Load Balancing: Distributing incoming traffic across multiple servers to ensure no single server is overwhelmed, enhancing performance and reliability.
Microservices Architecture: An approach where a server consists of multiple loosely coupled services that can be developed, deployed, and scaled independently.


### Security Considerations
SSL/TLS (Secure Sockets Layer/Transport Layer Security): Protocols for encrypting data between the client and server, ensuring data integrity and confidentiality.
Authentication and Authorization: Mechanisms to verify the identity of users (authentication) and control their access to resources (authorization). Examples include OAuth, JWT, and session-based authentication.
Rate Limiting: Preventing abuse by limiting the number of requests a client can make in a given time period.
CORS (Cross-Origin Resource Sharing): A mechanism to control how resources on your server can be requested from another domain.


### Common HTTP Server Software
Apache HTTP Server: A widely used, open-source HTTP server known for its robustness and extensive feature set.
Nginx: Known for its high performance and low resource consumption, commonly used as a reverse proxy and load balancer.
Microsoft IIS (Internet Information Services): A flexible, secure, and manageable web server for hosting anything on the Web.
Lighttpd: Designed for speed-critical environments, it’s secure, fast, and consumes less CPU and memory.

### Monitoring and Logging
Access Logs: Record details of every request made to the server.
Error Logs: Record any errors encountered during request processing.
Monitoring Tools: Use tools like Prometheus, Grafana, ELK Stack (Elasticsearch, Logstash, Kibana), or proprietary services to monitor performance, detect anomalies, and analyze trends.


### Understanding TCP (Transmission Control Protocol)

TCP, or Transmission Control Protocol, is one of the core protocols of the Internet Protocol Suite. It is a connection-oriented protocol, which means it establishes a connection before data can be sent and ensures that data is delivered reliably and in the correct order. Here's a detailed look at how TCP works and its key features.
Key Features of TCP

    Connection-Oriented:
        TCP establishes a connection between the sender and receiver before data transfer begins. This is done through a process called the TCP three-way handshake.

    Reliable Delivery:
        TCP ensures that all data packets reach their destination. If any packets are lost or corrupted during transmission, TCP will retransmit them.

    Ordered Data Transfer:
        Data is transmitted and received in the same order. TCP uses sequence numbers to keep track of the order of packets.

    Error Detection and Correction:
        TCP includes mechanisms for detecting errors in transmitted data and requesting retransmission if necessary. Checksums are used for error detection.

    Flow Control:
        TCP uses flow control to manage the rate of data transmission between sender and receiver, preventing the sender from overwhelming the receiver with too much data at once.

    Congestion Control:
        TCP has built-in congestion control mechanisms to adjust the rate of data transmission based on network congestion.

How TCP Works

    TCP Three-Way Handshake:
        Before data transfer, TCP establishes a connection using a three-step process known as the three-way handshake:
            SYN: The client sends a synchronization (SYN) packet to the server to initiate a connection.
            SYN-ACK: The server responds with a synchronization-acknowledgment (SYN-ACK) packet.
            ACK: The client sends an acknowledgment (ACK) packet back to the server. The connection is now established.

    Data Transfer:
        Once the connection is established, data transfer begins. Data is broken into smaller segments, each with a sequence number for ordering.
        The receiver sends acknowledgment (ACK) packets back to the sender to confirm receipt of data segments.
        If an ACK is not received within a certain timeframe, the sender retransmits the data segment.

    Flow Control (Sliding Window Protocol):
        TCP uses a sliding window mechanism for flow control. The sender can send multiple segments before needing an ACK, but the number of unacknowledged segments is limited by the window size.
        The window size can adjust dynamically based on network conditions and receiver capacity.

    Congestion Control:
        TCP uses algorithms like Slow Start, Congestion Avoidance, Fast Retransmit, and Fast Recovery to manage congestion.
            Slow Start: Begins with a small congestion window and increases it exponentially until a threshold is reached.
            Congestion Avoidance: Increases the congestion window linearly once the threshold is reached.
            Fast Retransmit: Retransmits a segment if three duplicate ACKs are received, indicating potential packet loss.
            Fast Recovery: Temporarily increases the congestion window after fast retransmit, then reduces it to avoid further congestion.

    Connection Termination:
        Terminating a TCP connection involves a four-step process called the four-way handshake:
            FIN: The sender sends a finish (FIN) packet to terminate the connection.
            ACK: The receiver acknowledges with an ACK packet.
            FIN: The receiver sends its own FIN packet.
            ACK: The sender acknowledges with a final ACK packet, completing the termination.

Detailed TCP Segment Structure

A TCP segment consists of a header and data. The header contains several fields, including:

    Source Port and Destination Port: Identifies the sending and receiving applications.
    Sequence Number: Indicates the position of the first byte of data in this segment within the entire data stream.
    Acknowledgment Number: Indicates the next byte expected from the other party.
    Data Offset: Specifies the length of the TCP header.
    Flags: Control bits such as SYN, ACK, FIN, RST, PSH, URG for managing connection states and control information.
    Window Size: Specifies the size of the receiver's buffer (used for flow control).
    Checksum: Provides error-checking for the header and data.
    Urgent Pointer: Indicates the end of urgent data if the URG flag is set.
    Options: Additional optional fields for various purposes (e.g., Maximum Segment Size, Window Scale).

Applications of TCP

    Web Browsing: HTTP/HTTPS runs over TCP, ensuring reliable delivery of web pages and resources.
    Email: Protocols like SMTP, POP3, and IMAP use TCP for reliable email transfer and retrieval.
    File Transfer: FTP uses TCP to ensure complete and accurate file transfers.
    Remote Access: SSH and Telnet use TCP to provide secure and reliable connections to remote systems.






In C++, sockets are used to facilitate communication between computers over a network. Sockets provide an endpoint for sending and receiving data across the network using standard protocols like TCP and UDP. Sockets provide a way to establish a connection between two devices, allowing data to be exchanged..
Key Concepts of Sockets

    Socket: A socket is an endpoint for communication, defined by an IP address and a port number.
    TCP (Transmission Control Protocol): A connection-oriented protocol ensuring reliable and ordered delivery of data.
    UDP (User Datagram Protocol): A connectionless protocol, faster but less reliable than TCP.

Socket Programming in C++

Here’s a step-by-step guide to creating a simple TCP server and client in C++ using the Berkeley sockets API, which is available on Unix-like systems and Windows.
TCP Server

    Include Necessary Headers:
        <iostream> for input/output.
        <cstring> for memory operations.
        <unistd.h> for POSIX operating system API.
        <sys/types.h> and <sys/socket.h> for socket-related functions.
        <netinet/in.h> for Internet address family.
        <arpa/inet.h> for IP address conversion functions.

    Create a Socket:

    cpp

int server_fd = socket(AF_INET, SOCK_STREAM, 0);
if (server_fd == 0) {
    std::cerr << "Socket creation failed\n";
    return -1;
}

Bind the Socket to an IP/Port:

cpp

struct sockaddr_in address;
int opt = 1;
int addrlen = sizeof(address);

// Forcefully attaching socket to the port 8080
if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
    std::cerr << "setsockopt failed\n";
    close(server_fd);
    return -1;
}

address.sin_family = AF_INET;
address.sin_addr.s_addr = INADDR_ANY;
address.sin_port = htons(8080);

if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
    std::cerr << "Bind failed\n";
    close(server_fd);
    return -1;
}

Listen for Connections:

cpp

if (listen(server_fd, 3) < 0) {
    std::cerr << "Listen failed\n";
    close(server_fd);
    return -1;
}

Accept a Connection:

cpp

int new_socket;
if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
    std::cerr << "Accept failed\n";
    close(server_fd);
    return -1;
}

Read and Write Data:

cpp

char buffer[1024] = {0};
read(new_socket, buffer, 1024);
std::cout << "Message from client: " << buffer << std::endl;
const char *hello = "Hello from server";
send(new_socket, hello, strlen(hello), 0);
std::cout << "Hello message sent\n";

Close the Socket:

cpp

    close(new_socket);
    close(server_fd);

TCP Client

    Include Necessary Headers (similar to the server).

    Create a Socket:

    cpp

int sock = 0;
if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
    std::cerr << "Socket creation error\n";
    return -1;
}

Specify Server Address:

cpp

struct sockaddr_in serv_addr;
serv_addr.sin_family = AF_INET;
serv_addr.sin_port = htons(8080);

// Convert IPv4 and IPv6 addresses from text to binary form
if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
    std::cerr << "Invalid address/ Address not supported\n";
    return -1;
}

Connect to the Server:

cpp

if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
    std::cerr << "Connection failed\n";
    return -1;
}

Read and Write Data:

cpp

const char *hello = "Hello from client";
send(sock, hello, strlen(hello), 0);
std::cout << "Hello message sent\n";

char buffer[1024] = {0};
read(sock, buffer, 1024);
std::cout << "Message from server: " << buffer << std::endl;

Close the Socket:

cpp

close(sock);





The Relationship Between TCP and Sockets

TCP (Transmission Control Protocol) and sockets are integral components of network communication. Here’s how they interact:

    Sockets:
        A socket is an endpoint for sending or receiving data across a computer network. It is an abstraction provided by the operating system to facilitate network communication.
        Sockets provide a way to establish a connection between two devices, allowing data to be exchanged.

    TCP:
        TCP is a protocol that defines how to establish and maintain a reliable, ordered, and error-checked communication between two network devices.
        TCP ensures that data is delivered accurately and in the same order in which it was sent.

How TCP and Sockets Work Together
1. Creating a Socket

When you create a socket, you specify the type of communication you want:

    Stream Sockets (SOCK_STREAM): These use TCP for communication. They provide a reliable, connection-oriented communication channel.
    Datagram Sockets (SOCK_DGRAM): These use UDP for communication. They provide a connectionless communication channel.

2. Binding and Listening (Server Side)

For a server using TCP:

    Bind: The server binds the socket to a specific IP address and port number, making it available to clients.
    Listen: The server puts the socket into listening mode, waiting for client connection requests.

3. Connecting (Client Side)

For a client using TCP:

    Connect: The client creates a socket and connects it to the server’s IP address and port number.

4. Establishing a Connection

This is where TCP’s reliability features come into play:

    Three-Way Handshake: TCP establishes a connection using a three-step process:
        SYN: The client sends a synchronization packet (SYN) to the server.
        SYN-ACK: The server responds with a synchronization-acknowledgment packet (SYN-ACK).
        ACK: The client sends an acknowledgment packet (ACK) back to the server.

This handshake process ensures both the client and server are ready for communication and agree on initial parameters such as sequence numbers.
5. Data Transfer

    Send/Receive: Once the connection is established, data can be sent using send() or write() and received using recv() or read().
    TCP’s Role: TCP handles the segmentation of data into packets, ensures each packet is delivered correctly, manages retransmissions if packets are lost, and reassembles the packets in the correct order at the receiving end.

6. Connection Termination

When the communication is complete, the connection is terminated gracefully using a four-step process:

    FIN: One side (client or server) sends a finish (FIN) packet to signal the end of data transmission.
    ACK: The other side acknowledges with an acknowledgment (ACK) packet.
    FIN: The other side then sends its own FIN packet.
    ACK: Finally, the initial side acknowledges with an ACK packet, closing the connection.

    ```
    	# SERVER CODE
	#include <iostream>
	#include <cstring>
	#include <unistd.h>
	#include <arpa/inet.h>
	
	int main() {
	    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
	    if (server_fd == 0) {
	        std::cerr << "Socket creation failed\n";
	        return -1;
	    }
	
	    struct sockaddr_in address;
	    int opt = 1;
	    int addrlen = sizeof(address);
	
	    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt));
	
	    address.sin_family = AF_INET;
	    address.sin_addr.s_addr = INADDR_ANY;
	    address.sin_port = htons(8080);
	
	    bind(server_fd, (struct sockaddr *)&address, sizeof(address));
	    listen(server_fd, 3);
	
	    int new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen);
	    char buffer[1024] = {0};
	    read(new_socket, buffer, 1024);
	    std::cout << "Message from client: " << buffer << std::endl;
	
	    const char *hello = "Hello from server";
	    send(new_socket, hello, strlen(hello), 0);
	
	    close(new_socket);
	    close(server_fd);
	
	    return 0;
	}

	# CLIENT CODE
	#include <iostream>
	#include <cstring>
	#include <unistd.h>
	#include <arpa/inet.h>
	
	int main() {
	    int sock = 0;
	    struct sockaddr_in serv_addr;
	
	    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
	        std::cerr << "Socket creation error\n";
	        return -1;
	    }
	
	    serv_addr.sin_family = AF_INET;
	    serv_addr.sin_port = htons(8080);
	
	    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
	        std::cerr << "Invalid address\n";
	        return -1;
	    }
	
	    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
	        std::cerr << "Connection failed\n";
	        return -1;
	    }
	
	    const char *hello = "Hello from client";
	    send(sock, hello, strlen(hello), 0);
	    
	    char buffer[1024] = {0};
	    read(sock, buffer, 1024);
	    std::cout << "Message from server: " << buffer << std::endl;
	
	    close(sock);
	
	    return 0;
	}

```






### Simplified Explanation of Epoll API
The epoll API is used to monitor multiple file descriptors to see if I/O is possible. It can be more efficient than other similar APIs, especially when dealing with a large number of file descriptors.

### Key Concepts:
>    Epoll Instance:
        - Interest List: Contains file descriptors the process is interested in.
        - Ready List: Contains file descriptors that are ready for I/O. The kernel dynamically updates this list based on I/O activity.
    System Calls:
        - epoll_create(2): Creates a new epoll instance and returns a file descriptor for it.
        - epoll_ctl(2): Adds or removes file descriptors to/from the interest list.
        - epoll_wait(2): Waits for I/O events and fetches items from the ready list, blocking if no events are available.
    Trigger Modes:
        - Edge-triggered (ET): Only notifies when changes occur. Requires non-blocking file descriptors and careful handling to avoid missing events.
        - Level-triggered (LT): Notifies as long as a file descriptor is ready, similar to poll(2).
Example Usage:
Level-triggered:

```
#define MAX_EVENTS 10
struct epoll_event ev, events[MAX_EVENTS];
int listen_sock, conn_sock, nfds, epollfd;

epollfd = epoll_create1(0);
ev.events = EPOLLIN;
ev.data.fd = listen_sock;
epoll_ctl(epollfd, EPOLL_CTL_ADD, listen_sock, &ev);

for (;;) {
    nfds = epoll_wait(epollfd, events, MAX_EVENTS, -1);
    for (int n = 0; n < nfds; ++n) {
        if (events[n].data.fd == listen_sock) {
            conn_sock = accept(listen_sock, (struct sockaddr *) &addr, &addrlen);
            setnonblocking(conn_sock);
            ev.events = EPOLLIN | EPOLLET;
            ev.data.fd = conn_sock;
            epoll_ctl(epollfd, EPOLL_CTL_ADD, conn_sock, &ev);
        } else {
            do_use_fd(events[n].data.fd);
        }
    }
}
```

### SERVER ENTRY POINT
```
Servers::Servers(ConfigDB &configDB) : _epoll_fds(-1), _server_fds(), _domain_to_server(), _ip_to_server(), 
	_keyValues(), server_index(), server_fd_to_index(), client_to_server(), _client_amount(0),
	_client_data(), _cgi_clients_childfd(), _client_time(), configDB_(configDB)
{
	servers = this;
	stop_fd = -1;
	_cgi_clients = std::map<int, CgiClient*>();
	_keyValues = configDB_.getKeyValue();
	createServers();
	initEvents();
}

void Servers::createServers() {
    std::cout << "|" << std::string(7, ' ') << CURSIVE_GRAY << " Creating servers..." << RESET << std::string(9, ' ') << "|" << std::endl;
    std::vector<std::string> ports;
    createEpoll();
    ports = getPorts();

    const int serverNumberWidth = 15;
    const int portWidth = 20;

    for (std::vector<std::string>::iterator it2 = ports.begin(); it2 != ports.end(); it2++) {
        if (!checkSocket(*it2)) {
            if (createSocket()) {
                (!bindSocket(*it2) || !listenSocket() || !setNonBlocking(_server_fds.back()) || !combineFds(_server_fds.back()))
                    ? _server_fds.pop_back();
                    : assignDomain(*it2, _server_fds.back());
            }
        }
    }
}
```
The loop in createServers iterates over each port obtained from the configuration.
For each port, it checks if the socket is valid and available for use by calling the checkSocket function.
If the socket is available (checkSocket returns false), it proceeds to create the socket, bind it to the port, set it to listen for incoming connections, and perform other necessary setup tasks.
If any of these setup tasks fail (e.g., socket creation, binding, listening, or setting non-blocking mode), it removes the server file descriptor from _server_fds vector.
If all setup tasks succeed, it assigns domain names to the server file descriptor and prints a row indicating the server ID and its corresponding port.

### CREATING EPOLL
```
    void	Servers::createEpoll(){
        int epoll_fd = epoll_create1(0);
        this->_epoll_fds = epoll_fd;
        if (epoll_fd < 0) {
            std::cerr << "Epoll creation failed" << std::endl;
            exit(1);
        }
    }
```
The epoll_fd variable is used to store the file descriptor of the epoll instance created using epoll_create1(0). This file descriptor represents the epoll instance, which is an in-kernel data structure used for monitoring multiple file descriptors for I/O events.

Later in the code, this epoll file descriptor (epoll_fd) will be used to add file descriptors of interest (such as socket file descriptors) to the epoll instance using epoll_ctl() with the EPOLL_CTL_ADD command. This allows the program to monitor these file descriptors for specific I/O events, such as readiness for reading or writing.

Additionally, the epoll file descriptor will be used in the epoll_wait() function to wait for I/O events on the monitored file descriptors. When I/O events occur, epoll_wait() will return, providing information about the file descriptors that are ready for I/O operations. This allows the program to efficiently handle I/O events on multiple file descriptors without the need for polling or blocking on individual file descriptors.

### Check and Validating Socket

The checkSocket function is likely used to check whether a particular port is already in use by another process. It typically involves attempting to create a socket and bind it to the specified port. If the binding fails with an error indicating that the port is already in use, the function returns true, indicating that the port is unavailable.

Input: The function takes the port number as input.

Socket Creation: It attempts to create a socket using the socket() function. This creates a communication endpoint and returns a file descriptor.

Address Binding: It tries to bind the socket to the specified port using the bind() function. If the port is already in use, this step will fail, returning an error code.

Check Result: If the binding fails with an error indicating that the port is already in use, the function returns true, indicating that the port is unavailable. Otherwise, it returns false, indicating that the port is available.

```
    int Servers::checkSocket(std::string ip){
        std::string ip_string;
        std::string port_string;
        if (ip.find(":") == std::string::npos)
            return checkSocketPort(ip);
        else{
            std::stringstream ss_ip;
            std::stringstream ss_port;
            ss_ip << ip;
            getline(ss_ip, ip_string, ':');
            ss_ip >> port_string;
            if (checkSocketPort(port_string) == 1)
                return 1;
        }
        struct sockaddr_in sa;
        int result = inet_pton(AF_INET, ip_string.c_str(), &(sa.sin_addr));
        if (result == 0) {
            std::cerr << "Invalid address" << std::endl;
            return 1;
        }
        else if (result == -1) {
            std::cerr << "Address conversion failed" << std::endl;
            return 1;
        }
        return 0;
    }
```

In our implementation, The Servers::checkSocket function is designed to check whether a given IP address or IP address and port combination is already in use.

Input Handling: The function takes an IP address as a string input. If the input contains a port (i.e., it is in the format "ip
"), it extracts the IP address and port separately.

Check Port: If the input does not contain a port (i.e., it is just an IP address), the function calls checkSocketPort to check whether the port is already in use.

IP Address Validation: The function then attempts to convert the IP address string to a binary representation using inet_pton (presentation to network). The inet_pton function: is part of the POSIX socket API and is used to convert an IPv4 or IPv6 address from its presentation format (such as a string) to its network format (a binary representation).

Function Signature: The inet_pton function has the following signature:

int inet_pton(int af, const char *src, void *dst);
    - af: Address family, which can be AF_INET for IPv4 or AF_INET6 for IPv6.
    - src: A pointer to the string containing the IPv4 or IPv6 address in presentation format.
    - dst: A pointer to a buffer where the binary representation of the address will be stored.
    - Return Value:

If the conversion is successful, inet_pton returns 1.
If the input string does not contain a valid IPv4 or IPv6 address, it returns 0.
If an error occurs, it returns -1, and the errno variable is set to indicate the error.

```
    int Servers::createSocket(){
        int server_fd = socket(AF_INET, SOCK_STREAM, 0);
        if (server_fd == -1) {
            std::cerr << "Socket creation failed" << std::endl;
            return (0);
        }
        _server_fds.push_back(server_fd);
        return (1);
    }
```

This createSocket function is responsible for creating a new socket for the server to listen for incoming connections.

### Socket Creation:

The function calls the socket system call to create a new socket.
The socket function takes three arguments:
    - AF_INET: Specifies the address family, in this case, IPv4.
    - SOCK_STREAM: Specifies the type of socket, in this case, a stream socket for TCP communication.
    - 0 (or IPPROTO_IP): Specifies the protocol to be used. In this case, the default protocol for the given socket type and address family is used.
If the socket call fails (returns -1), an error message is printed, and the function returns 0 to indicate failure.

Server File Descriptor:

Upon successful creation of the socket, a file descriptor (server_fd) is returned, representing the socket.
This file descriptor is a unique identifier for the socket within the process and is used to refer to the socket in subsequent operations.
Saving File Descriptor:

The server_fd is then added to the _server_fds vector.
_server_fds is a member variable of the Servers class, likely declared as std::vector<int> _server_fds, where it stores the file descriptors of all created server sockets.
Return Value:

If the socket creation is successful, the function returns 1 to indicate success.
If the socket creation fails, the function returns 0 to indicate failure.
In summary, createSocket creates a new socket for the server, adds its file descriptor to a vector for later reference, and returns a status indicating whether the operation was successful or not. The file descriptor is crucial for subsequent operations on the socket, such as binding, listening, and accepting connections.


### Binding Socket

```
    int Servers::bindSocket(std::string s_port){
        if (_server_fds.back() == -1)
        {
            std::cerr << "Socket binding impossible!" << std::endl;
            return (0);
        }
        std::stringstream ss;
        ss << s_port;
        int port;
        std::string ip_string;
        const char *c_ip = NULL;
        if (s_port.find(":") == std::string::npos)
        {
            port = std::atoi(s_port.c_str());
            _ip_to_server[_server_fds.back()] = "127.0.0.1:" + s_port;
        }
        else
        {
            _ip_to_server[_server_fds.back()] = s_port;
            getline(ss, ip_string, ':');
            ss >> port;
            c_ip = ip_string.c_str();
        }
        int opt = 1;
        setsockopt(_server_fds.back(), SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(int));
        struct sockaddr_in address;
        std::memset(&address, 0, sizeof(address));
        address.sin_family = AF_INET;
        if (c_ip != NULL)
            address.sin_addr.s_addr = inet_addr(c_ip);
        else
            address.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
        address.sin_port = htons(port);
        if (bind(_server_fds.back(), (struct sockaddr *)&address, sizeof(address)) == -1) {
            std::cerr << "Bind failed" << std::endl;
            return (0);
        }
        for (std::map<int, std::vector<std::string> >::iterator it = server_index.begin(); it != server_index.end(); it++){
            for (std::vector<std::string>::iterator it2 = it->second.begin(); it2 != it->second.end(); it2++){
                if (*it2 == s_port)
                    server_fd_to_index[_server_fds.back()] = it->first;
            }
        }
        return (1);
    }
```

The bindSocket function is responsible for binding a socket to a specific IP address and port number. Let's break down how it works:

Error Checking:

The function first checks if the last server socket file descriptor _server_fds.back() is valid. If it's -1, it indicates that socket creation failed, and the function prints an error message and returns 0 to indicate failure.
Parsing IP Address and Port:

The function parses the input s_port to extract the IP address and port number. If s_port does not contain a colon (":"), it assumes that only the port number is provided, and the IP address is set to the loopback address "127.0.0.1". Otherwise, it extracts the IP address and port from the input string.
It sets c_ip to point to the extracted IP address as a C-style string.
Setting Socket Options:

It sets the SO_REUSEADDR socket option to allow reusing the same port number if the socket is in the TIME_WAIT state.
This option enables multiple sockets to bind to the same address and port number, which can be useful for server applications that need to restart quickly after a shutdown.
Preparing Address Structure:

It initializes a sockaddr_in structure address and sets its fields:
sin_family to AF_INET to indicate IPv4.
sin_addr to the parsed IP address (c_ip) or the loopback address if no IP address is provided.
sin_port to the parsed port number (port), converted to network byte order using htons().
Binding the Socket:

It calls the bind function to bind the socket to the specified address and port.
If the bind call fails, the function prints an error message and returns 0 to indicate failure.
Associating Server Index:

After successful binding, the function iterates over a map server_index, which likely maps server indexes to lists of port numbers.
For each entry in server_index, it checks if the current port number s_port matches any port number in the list. If it finds a match, it associates the server socket file descriptor _server_fds.back() with the corresponding server index.
Return Value:

If the binding is successful, the function returns 1 to indicate success.
In summary, the bindSocket function binds a server socket to a specified IP address and port number, sets socket options for reusing the address, and associates the socket with a server index




### setsockopt(_server_fds.back(), SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(int))

The line setsockopt(_server_fds.back(), SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(int)); sets a socket option on the server socket file descriptor _server_fds.back() to enable the reuse of local addresses. Let's break down each parameter and how it works:

_server_fds.back(): This is the file descriptor of the server socket. It refers to the most recently created server socket.

SOL_SOCKET: This parameter specifies the level at which the option is defined. In this case, it indicates that the option applies to the socket layer.

SO_REUSEADDR: This parameter specifies the particular socket option being set. SO_REUSEADDR allows the reuse of local addresses. When this option is enabled, it allows other sockets to bind to the same address and port number, even if the socket that originally bound to that address is still in the TIME_WAIT state.

&opt: This is a pointer to the value that specifies whether to enable or disable the SO_REUSEADDR option. In this case, it points to the variable opt, which is presumably set to 1, indicating that the option should be enabled.

sizeof(int): This parameter specifies the size of the option value. Since opt is an int, sizeof(int) ensures that the correct size of the option value is passed to the setsockopt function.

By calling setsockopt with SO_REUSEADDR set to 1, the server socket is configured to allow the reuse of local addresses, which can be beneficial for server applications that need to quickly restart and bind to the same address and port.

inet_addr(c_ip) and htonl(INADDR_LOOPBACK) are both functions used for converting IP addresses between different formats. Here's what each does:

inet_addr(c_ip):

This function converts the string representation of an IPv4 address c_ip into its 32-bit binary representation in network byte order (big-endian).
c_ip is a pointer to a null-terminated string containing the IPv4 address in dotted-decimal notation (e.g., "127.0.0.1").
It returns the binary representation of the IPv4 address. If the input string is not a valid IPv4 address, INADDR_NONE is returned.
In the provided code, c_ip is assigned the string representation of the IP address extracted from s_port.
htonl(INADDR_LOOPBACK):

This function converts the 32-bit IPv4 address INADDR_LOOPBACK from host byte order to network byte order (big-endian).
INADDR_LOOPBACK is a constant defined in <netinet/in.h> representing the loopback address 127.0.0.1.
htonl stands for "host to network long".
It returns the 32-bit IPv4 address in network byte order.
In the provided code, INADDR_LOOPBACK is used as the address for binding the socket to the loopback interface.
In summary, inet_addr converts a string IP address to its binary representation, while htonl converts a 32-bit IPv4 address from host to network byte order. They are used here to set the IP address of the server socket.
The function htons(port) is used to convert a 16-bit unsigned short integer from host byte order to network byte order (big-endian).

port: This is the port number in host byte order that you want to convert to network byte order.

Return Value: The function returns the 16-bit port number converted to network byte order.

Purpose: Network protocols, including TCP/IP, often require data to be transmitted in network byte order, which is big-endian. The htons function ensures that port numbers are correctly represented in the required byte order when passed to network functions like bin.d, connect, etc.

### bind(_server_fds.back(), (struct sockaddr *)&address, sizeof(address))
The bind function is used to associate a socket with a specific IP address and port number. Here's how it works:

_server_fds.back(): This retrieves the file descriptor of the socket that you want to bind.

(struct sockaddr *)&address: This is a pointer to a sockaddr_in structure that contains the IP address and port number to bind to. The sockaddr_in structure is cast to a generic sockaddr structure pointer because bind expects a pointer to a sockaddr structure. This is a common practice in C and C++ to handle different types of socket addresses (sockaddr and its derivatives) using a single function.

sizeof(address): This specifies the size of the sockaddr_in structure pointed to by (struct sockaddr *)&address.

Return Value: The bind function returns 0 on success, and -1 if an error occurs.

Purpose: Binding a socket allows you to specify the local address and port that the socket will use for communication. It's typically done for server sockets to specify the address and port on which the server will listen for incoming connections.

```
int Servers::listenSocket(){
	if (listen(_server_fds.back(), SOMAXCONN) == -1) {
		std::cerr << "Listen failed" << std::endl;
		return (0);
	}
	return (1);
}
```
The listenSocket function is responsible for configuring the server socket to listen for incoming connections. Here's a breakdown of its purpose:

Socket Listening: The function calls the listen system call, which configures the socket referenced by _server_fds.back() to listen for incoming connections.

Backlog Parameter: The SOMAXCONN constant specifies the maximum length for the queue of pending connections. It's a system-defined value indicating the maximum number of pending connections that can wait to be accepted by the server.

Error Handling: If the listen call fails (returns -1), the function prints an error message indicating that listening failed, usually due to a system resource limit or another issue. Then it returns 0 to indicate failure.

Success: If the listen call succeeds, meaning the socket is successfully configured for listening, the function returns 1 to indicate success.

In summary, the purpose of the listenSocket function is to set up the server socket so that it can accept incoming connections from clients, enabling the server to communicate with them.


```
int Servers::setNonBlocking(int fd){
	int flags = fcntl(fd, F_GETFL);
	if (flags == -1)
	{
		std::cerr << "Fcntl failed" << std::endl;
		return (0);
	}
	if (fcntl(fd, F_SETFL, flags | O_NONBLOCK) == -1)
	{
		std::cerr << "Fcntl failed" << std::endl;
		return (0);
	}
	if (fcntl(fd, F_SETFD, FD_CLOEXEC) == -1)
    {
        std::cerr << "Fcntl failed" << std::endl;
        return (0);
    }
	return (1);
}
```

The setNonBlocking function is responsible for setting a file descriptor to non-blocking mode. Let's break down how it works:

Getting Current Flags: The function first retrieves the current flags associated with the file descriptor fd using the fcntl function with the F_GETFL command. If this operation fails (returns -1), it prints an error message and returns 0 to indicate failure.

Setting Non-blocking Mode: If the retrieval of flags succeeds, the function then sets the O_NONBLOCK flag using bitwise OR with the retrieved flags. This flag indicates that I/O operations on the file descriptor should be non-blocking. The fcntl function with the F_SETFL command is used for this purpose. If setting the non-blocking mode fails, it prints an error message and returns 0.

Setting FD_CLOEXEC: Additionally, the function sets the FD_CLOEXEC flag using the fcntl function with the F_SETFD command. This flag ensures that the file descriptor is automatically closed when executing a new program via one of the exec family of functions. If setting this flag fails, it prints an error message and returns 0.

Success: If all operations succeed, the function returns 1 to indicate that the file descriptor has been successfully set to non-blocking mode and configured to close on execution of a new program.

In summary, the setNonBlocking function ensures that the specified file descriptor operates in non-blocking mode, which is essential for asynchronous I/O operations, and configures it to close automatically when executing a new program.


```
int Servers::combineFds(int socket_fd){
	struct epoll_event event;
	std::memset(&event, 0, sizeof(event));
	event.events = EPOLLIN;
	event.data.fd = socket_fd;
	if (epoll_ctl(this->_epoll_fds, EPOLL_CTL_ADD, socket_fd, &event) == -1) {
		std::cerr << "Epoll_ctl failed" << std::endl;
		return (0);
	}
	return (1);
}
```

The combineFds function is responsible for adding a file descriptor to the epoll instance for monitoring. Let's go through how it works:

Creating an epoll_event: The function starts by creating an epoll_event structure named event and initializes it using memset to ensure all its members are set to 0. This structure represents the event to be monitored by epoll.

Setting Event Type and File Descriptor: It then sets the events member of the event structure to EPOLLIN, indicating that the file descriptor will be monitored for incoming data readiness. Additionally, it sets the data.fd member to the specified socket_fd, indicating the file descriptor to monitor.

Adding File Descriptor to epoll Instance: The function calls epoll_ctl with the EPOLL_CTL_ADD command to add the specified socket_fd to the epoll instance associated with _epoll_fds. If this operation fails (returns -1), it prints an error message and returns 0 to indicate failure.

Success: If the addition of the file descriptor to epoll succeeds, the function returns 1 to indicate success.

In summary, the combineFds function facilitates the integration of a file descriptor into the epoll instance, allowing it to be monitored for events such as incoming data readiness.

```
void Servers::assignDomain(std::string port, int server_fd){
	if (port == "80")
		assignLocalDomain(server_fd);
	std::map<std::string, std::vector<std::string> > config = getKeyValue();
	for (std::map<std::string, std::vector<std::string> >::iterator it = config.begin(); it != config.end(); it++)
	{
		for (std::vector<std::string>::iterator it2 = it->second.begin(); it2 != it->second.end(); it2++)
		{
			if (*it2 == port){
				std::string server_name = it->first;
				std::size_t pos = server_name.find("]");
				server_name = server_name.substr(0, pos + 1);
				std::string domain = server_name + ".server_name";
				std::map<std::string, std::vector<std::string> >::iterator it_domain = config.find(domain);
				if (it_domain != config.end()){
					for (std::vector<std::string>::iterator it3 = it_domain->second.begin(); it3 != it_domain->second.end(); it3++){
						if (std::find(_domain_to_server[server_fd].begin(), _domain_to_server[server_fd].end(), *it3) == _domain_to_server[server_fd].end())
							_domain_to_server[server_fd].push_back(*it3);
					}
				}
				else{
					if (std::find(_domain_to_server[server_fd].begin(), _domain_to_server[server_fd].end(), "localhost") == _domain_to_server[server_fd].end())
						_domain_to_server[server_fd].push_back("localhost");
				}
			}
		}
	}
}

void Servers::assignLocalDomain(int server_fd){
	std::map<std::string, std::vector<std::string> > config = getKeyValue();
	for (std::map<std::string, std::vector<std::string> >::iterator it_domain = config.begin(); it_domain != config.end(); it_domain++){
		if (it_domain->first.find("server_name") != std::string::npos){
			std::string server_name = it_domain->first;
			std::size_t pos = server_name.find("]");
			server_name = server_name.substr(0, pos + 1);
			std::string domain = server_name + ".listen";
			std::map<std::string, std::vector<std::string> >::iterator it_domain_listen = config.find(domain);
				if (it_domain_listen == config.end()){
					for (std::vector<std::string>::iterator it = it_domain->second.begin(); it != it_domain->second.end(); it++){
					if (std::find(_domain_to_server[server_fd].begin(), _domain_to_server[server_fd].end(), *it) == _domain_to_server[server_fd].end())
						_domain_to_server[server_fd].push_back(*it);
				}
			}
		}
	}
}
```

These two functions, assignLocalDomain and assignDomain, are responsible for assigning domain names to server file descriptors based on the configuration settings.

Here's how they work:

assignLocalDomain(int server_fd)
Retrieve Configuration Settings: The function retrieves the configuration settings using the getKeyValue function, which returns a map containing various server configurations.

Iterate Through Configuration: It then iterates through the configuration map to find entries related to server names (server_name).

Extract Server Name and Domain: For each server entry found, it extracts the server name and constructs a domain name from it by appending ".listen".

Check for Existing Assignment: It checks if the domain name has already been assigned to the server file descriptor. If not, it adds the domain name to the _domain_to_server map associated with the server_fd.

assignDomain(std::string port, int server_fd)
Check Port Number: If the port number is "80", it calls the assignLocalDomain function to handle the assignment of local domains.

Retrieve Configuration Settings: Similar to the previous function, it retrieves the configuration settings using getKeyValue.

Iterate Through Configuration: It iterates through the configuration settings to find entries related to the specified port.

Extract Server Name and Domain: For each port entry found, it extracts the server name and constructs a domain name from it by appending ".server_name".

Check for Existing Assignment: It checks if the domain name has already been assigned to the server file descriptor. If not, it adds the domain name to the _domain_to_server map associated with the server_fd. If no domain name is found in the configuration settings, it defaults to assigning "localhost" as the domain.

These functions essentially map domain names to server file descriptors based on the configuration settings provided. This mapping is useful for handling requests directed to specific domains on the server.




The main goal of the CGI (Common Gateway Interface) handling in this code is to manage the interaction between a web server and external CGI scripts. The code handles the setup, execution, and response handling of CGI scripts.

Key Components
Servers::handleIncomingCgi(int child_fd)
CgiClient class
CgiHandle class
1. Servers::handleIncomingCgi(int child_fd)
This function manages incoming data from CGI processes. It performs several tasks:

Finding the corresponding client_fd:

The child_fd is the file descriptor (FD) of the child process (the CGI process).
The function looks up the client_fd (the FD of the client connection) associated with this child_fd in _cgi_clients_childfd.
Handling null CGI clients:

If the _cgi_clients[client_fd] is NULL, the function removes the CGI process from the epoll instance, deletes the client, and cleans up related mappings.
Processing the CGI response:

If the CGI client is valid, HandleCgi() is called on the CgiClient object.
Depending on the CGI process's status code, it either prepares and sends the HTTP response back to the client or handles errors.
2. CgiClient Class
This class encapsulates the logic for managing CGI processes. Here's a breakdown of its key functions:

Constructor and Destructor:

The constructor initializes the CgiClient with a Client object and an epoll_fd. It sets up various configurations and initializes the CgiHandle object.
The destructor cleans up by deleting the CGI handle, closing pipes, and terminating the CGI process.
HandleCgi():

Reads data from the CGI process's output.
Parses headers if they haven't been parsed yet.
Sets the HTTP response status code and content length.
toCgi():

Sends the request body to the CGI process via its input pipe.
fromCgi():

Reads the response from the CGI process via its output pipe and appends it to the response body.
Handles the parsing of headers if they haven't been parsed yet.
Helper functions:

Functions like setCgiPipe, closeParentCgiPipe, and deleteChild manage file descriptors and pipes associated with the CGI process.
parseCgiHeaders and handleCgiHeaders handle parsing the headers from the CGI response.
getResponseString and getResponse retrieve the HTTP response.
3. CgiHandle Class
This class handles the creation and management of the actual CGI process.

Constructor and Destructor:

Initializes environment variables and sets up pipes for communication.
Executes the CGI script by forking a new process and using execve.
Environment Setup:

initEnv() sets up the necessary environment variables for the CGI script.
Pipe Management:

setPipe() sets up the pipes for inter-process communication.
closePipe() closes these pipes.
Executing the CGI Script:

execCgi() handles the forking of the process and executing the CGI script with the correct arguments and environment.
Helper functions:

setPath, setArgv, and createEnvArray help prepare the execution environment for the CGI script.
combineFds adds the CGI process's output pipe to the epoll instance to monitor it for readability.
Detailed Flow
Receiving and Handling CGI Responses:

Servers::handleIncomingCgi receives data from the CGI process (child_fd).
It identifies the associated client connection (client_fd).
Processing the CGI Output:

The CgiClient::HandleCgi method is called, which reads data from the CGI process and updates the HTTP response.
Sending the Response Back to the Client:

If the CGI process completes successfully (status 200 or 500), the response is prepared and sent back to the client using write.
The client is then cleaned up, and relevant file descriptors are removed from monitoring.
Managing CGI Execution:

CgiHandle sets up the environment, pipes, and executes the CGI script.
Handles reading from and writing to the CGI process through its pipes.
This flow ensures that the server can correctly handle CGI requests, process their responses, and deliver them back to the client, maintaining the overall HTTP communication process.