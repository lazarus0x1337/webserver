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
  if (sockfd < 0) {
    std::cout << "Failed to create socket. errno: " << errno << std::endl;
    exit(EXIT_FAILURE);
  }
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
    */

    if (listen(sockfd, 10) < 0)
    {
        std::cout << "Failed to listen on socket. errno: " << errno << std::endl;
        exit(EXIT_FAILURE);
    } 
    

    ssize_t addrlen = sizeof(sockaddr);
    int connection = accept(sockfd, (struct sockaddr*)&sockaddr, (socklen_t*)&addrlen);
    if (connection < 0)
    {
        std::cout << "Failed to grab connection. errno: " << errno << std::endl;
        exit(EXIT_FAILURE);
    }

    // Read from the connection
    char buffer[10];
    ssize_t bytesRead = read(connection, buffer, 10);
    std::cout << "The message was: " << buffer;

    // Send a message to the connection
    std::string response = "Good talking to you\n";
    send(connection, response.c_str(), response.size(), 0); // this for send response to client 

    // Close the connections
    close(connection);
    close(sockfd);
}