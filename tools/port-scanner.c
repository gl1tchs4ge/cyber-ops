#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>

in_port_t to_network_byte(in_port_t port) {
	
	// Turn host port byte into networ byte
	in_port_t network_port = htons(port);

	return network_port;
}

int main (int argc, char *argv[]) {

	// Print the given IP address
	printf("%s\n", argv[1]);

	// Create sockaddr for IPv4
	struct sockaddr_in address_sockaddr;

	// Convert the string  into binary IP address and send it to its respective holder
	inet_pton( AF_INET, argv[1], &address_sockaddr.sin_addr);

	// Set the type of address
	address_sockaddr.sin_family = AF_INET; 
	
	// main for loop for scanning
	for (in_port_t port = 22; port <= 80; port++) {
		
			// Calling the port function
			address_sockaddr.sin_port = to_network_byte(port);
			
			// Creating the socket
			int sock = socket(AF_INET, SOCK_STREAM, 0); 
			
			// Testing if socket was created
			if (sock == -1) {
				printf("Socket failed to be created");
				perror(""); 
				return 1;
			}

			// Connect to the socket
			int	connection =  connect(sock, (struct sockaddr *)&address_sockaddr, sizeof(address_sockaddr));
				
			// Connection Succeded 
			if (connection == 0) {
				printf("Connection to port %i succeded\n", port); 
			}
			
			//Close the socket
			close(sock);
				
	}
	return 0; 	
}
