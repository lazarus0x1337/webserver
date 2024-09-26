#include <sys/socket.h> // socket functions
#include <netinet/in.h> // For sockaddr_in
#include <cstdlib> // For exit() and EXIT_FAILURE
#include <iostream> // For cout
#include <unistd.h> // For read
#include <cerrno>  // for errno

int main()
{
    /*
    Create a socket (IPv4 -> use AF_INET, TCP -> use SOCK_STREAM)
    socket (domain, type, protocol)
    if protocol == 0 -> usually allows the system to choose 
    the default protocol based on the socket type
    the default protocol is TCP (IPPROTO_TCP).
    */
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    std::cout << "create socket done "<< std::endl;

  /*
  Why htons() is needed:
    When sending data over the network (e.g., a port number)
    the data needs to be in network byte order
    If the host machine uses little-endian byte ordering
    this would not match the required big-endian ordering used by the network.
  */
    // uint16_t port = 8080;  // Port in host byte order
    // uint16_t net_port = htons(36895);  // Convert to network byte order

    // std::cout << "Host byte order port: " << port << std::endl;
    // std::cout << "Network byte order port: " << net_port << std::endl;

    sockaddr_in sockaddr;
    sockaddr.sin_family = AF_INET;
    sockaddr.sin_addr.s_addr = INADDR_ANY;
    sockaddr.sin_port = htons(1337);

    /*
        Once we have the socket,
        we need to use bind to assign an IP address and port to the socket.
        int bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen);
        A pointer to a sockaddr structure that contains the local address 
        (IP address and port number) to which the socket should be bound.
        * AF_INET (ipv4)
        -> sin_family specifies the address family of the socket.
        * INADDR_ANY (which resolves to 0.0.0.0)
         -> This allows the socket to accept connections on any IP address
        *htons 
        -> htons(1337): Specifies that the server will listen on port 1337
    */
    if (bind(sockfd, (struct sockaddr*)&sockaddr, sizeof(sockaddr)) < 0)
    {
        std::cout << "Failed to bind to port 1337. errno: " << errno << std::endl;
        exit(EXIT_FAILURE);
    }
        std::cout << "bind done "<< std::endl;


    /*
        Start listening. Hold at most 10 connections in the queue
        The listen() function applies only to stream sockets. 
        It indicates a readiness to accept client connection requests,
        and creates a connection request queue of length backlog to queue incoming connection requests. 
        Once full, additional connection requests are rejected.
    
        the queue refers to a temporary holding area where pending client 
        connection requests are stored while the server is not yet ready to accept them

        Without this queue, the server would only be able to handle one client connection at a time
        and any additional clients would be immediately rejected if the server was busy.

        the connection is placed in the queue until the server is ready to process it via the accept()
        Once the server calls accept(), it removes a connection request from the queue and starts interacting with that client.
    
        listen(sockfd , backlog);
        backlog: we can use macro : SOMAXCONN
        Use the SOMAXCONN statement to specify the maximum number 
        of connection requests queued for any listening socket.
        https://ibm.com/docs/en/zos/2.4.0?topic=statements-somaxconn-statement
    */

    if (listen(sockfd, 10) < 0)
    {
        std::cout << "Failed to listen on socket. errno: " << errno << std::endl;
        exit(EXIT_FAILURE);
    } 
    

    /*source IBM 
        accept() call is used by a server to accept a connection request from a client. When a connection is available
        The accept() call creates a new socket descriptor with the same properties as socket and returns it to the caller
        The new socket descriptor cannot be used to accept new connections. The original socket,
        remains available to accept more connection requests.
    */
    ssize_t addrlen = sizeof(sockaddr);
    int connection = accept(sockfd, (struct sockaddr*)&sockaddr, (socklen_t*)&addrlen);
    if (connection < 0)
    {
        std::cout << "Failed to grab connection. errno: " << errno << std::endl;
        exit(EXIT_FAILURE);
    }

    // Read from the connection
    char buffer[100];
    ssize_t bytesRead = read(connection, buffer, 100);
    buffer[bytesRead] = 0;
    std::cout << "The message was: " << buffer;

    // Send a message to the connection
    std::string response = "Good talking to you\n";
    send(connection, response.c_str(), response.size(), 0); // this for send response to client 

    // Close the connections
    close(connection);
    close(sockfd);

    /*
        One thing I discovered while creating this server is 
        that when I did this and tried to restart the server right away 
        I got an error: Failed to bind to port 9999. errno: 98

        After some research, I found that even after we call close, 
        the tcp connection is not immediately freed. 
        This is part of the TCP protocol definition. 
        Before being closed, a socket transitions to TIME_WAIT state. 
        This is done to give time to the socket to cleanly shutdown. 
        After some time, the address will be released by the OS. 
    */
}