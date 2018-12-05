#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <firewall.h>
#define LIMIT 1000

int auth(){
	srand(time(0)); 
	int auth = rand();
	return auth;
	
}

char helpText[] = "Usage:\n\t./udp_server2 output_file_name\n";

int main(int argc, char* argv[]) {
	if(argc != 2) {
		fprintf(stderr, "%s", helpText);
		exit(0);
	}

	// Initialize variables.
	int sockfd, addr_len, bytes_read;
	char recv_data[1000];
	struct sockaddr_in server_addr , client_addr;

	// Error with creation of socket.
	if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) == -1) {
		perror("Socket");
		exit(1);
	}
	
  // Initializing server address information.
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(5000);
	server_addr.sin_addr.s_addr = INADDR_ANY;
	bzero(&(server_addr.sin_zero),8);

	// Error in binding address to socket.
	if (bind(sockfd,(struct sockaddr *)&server_addr, sizeof(struct sockaddr)) == -1) {
		perror("Bind");
		exit(1);
	}
	// Waiting messages.
	addr_len = sizeof(struct sockaddr);
	printf("UDPServer Waiting for client on port 5000...\n");
	fflush(stdout);
	// Server stays open until program terminated.
	while (1) {
		// Read bytes from socket.
		bytes_read = recvfrom(sockfd,recv_data,1024,0,
						   (struct sockaddr *)&client_addr, &addr_len);
		// Add null terminating character to string created.
		recv_data[bytes_read] = '\0';

		// Write recieved characters to the specified file.
		//FILE * ofp = fopen(argv[1], "w");
		firewall(recv_data, LIMIT);
		//if(!ofp) {
				//printf("Can't open file.");
			//return;
		//}

		//fwrite(recv_data, bytes_read, 1, ofp);
		//fclose(ofp);

		// Display characters read (for confirmation).
		printf("\n(%s , %d) said : ",inet_ntoa(client_addr.sin_addr),
						                  ntohs(client_addr.sin_port));
		printf("%s", recv_data);
		fflush(stdout);
	} 

}

