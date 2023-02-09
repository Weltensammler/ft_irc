#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <string.h>
#include <string>

int main()
{
	// Create a socket
	int listening = socket(AF_INET, SOCK_STREAM, 0); //difference INET and INET6

	// Bind the socket to a IP / Port 
	// Mark the socket for listening in 
	// Accept a call 
	// While receiving display message, echo message 
	// Close socket
}