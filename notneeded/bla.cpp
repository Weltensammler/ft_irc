#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <iostream>

/*
- socket = node that wants to communicate with another socket
int sockfd(domain, type, protocol) : is basically a filedescriptor for the socket
-> - domain: -AF_LOCAL: communication between processes on same host;
			 -AF_INET: for communication between processes on different hosts;
   - type: the type of communication;
	-> - SOCK_STREAM: for TCP (is most reliable, so chose always because SOCK_DGRAM uses UDP)
   - protocol: - we use internetprotocol which has th evalue of 0;
   - returns <0 if creating socket failed;


binding socket to address and port number:
- int bind(int sockfd, const struct sockaddr* addr, socklen_t addrlen)
	-> address and port for binding are in the struct


put a socket(node) into listening (= receiving mode):
- int listen(int sockfd, int backlog)
	-> - bcklog is the max. length of the queue of pending connections (= defines max size of waiting line for new connections)

establishing a connection with first client in queue:
- int new_socket = accept(int sockfd, struct sockaddr* addr, socklen_t* addrlen);
	-> - establishes a connection for the sockefd defined by sockfd, with the first 
		client waiting in queue
		- accept creates a new socket that is connected to that client and returns its sockfd
		  

*/


int main(int ac, char** av)
{
	if (ac != 2)
	{
		std::cout << "wrong number of arguments\n";
	}
	else
	{
		int portnum = atoi(av[1]);

				int new_sockfd;
		
		socklen_t clilen;
		char buffer[256];
		// creating a socket
		int sockfd = socket(AF_INET6, SOCK_STREAM, 0);
		if (sockfd < 0)
		{
			std::cerr << "error: sockets was not created\n";
		}


		struct sockaddr_in server_addy; /* sockaddr_in contains struct in_addr which
										   has only field for the for the address (unsigned long) */
		bezero(&server_addy, sizeof(server_addy)); // set all members to 0;
		server_addy.sin_family = AF_INET6; // setting domain AF_INET6 can take IPV4 and IPV6
		server_addy.sin_addr = in6_addr; /* is like INADDR_ANY but for both ipv4 and ipv6 addresses
											field for the Ip address of the host */
		server_addy.sin_port = htons(portnum); // htons(): converts pornumber from hostbyte order into network byte order;


		struct sockaddr_in client_addy;
		bzero(&client_addy, sizeof(client_addy);

		

		// binding socket to the address of the server
		if (bind (sockfd, (struct sockaddr*) &server_addy, sizeof(server_addy)) < 0 )
		{
			std::cerr << "error: binding failed\n";
		}

		// listening/waiting for conncection to the socket
		listen(sockfd, 3); /* the socket now waits for clients to request a connection to the server
							  3 is the max. of other clients waiting in queue */
		
		// accepting a connection

		// send and receive data

	}




	return (0);
}
