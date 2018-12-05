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

int main(int argc, char* argv[])
{
	if (argc < 2) {
		printf("\n\tusage: ./device file.txt [ip]\n");
		return 1;
	}

    int sockfd;
    struct sockaddr_in server_addr;
    char send_data[1024];
    struct hostent *host = (struct hostent *)gethostbyname((argc > 2) ? argv[2] : "localhost");
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) == -1) {
        perror("socket");
        exit(1);
    }
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(5000);
    server_addr.sin_addr = *((struct in_addr *)host->h_addr);
    bzero(&(server_addr.sin_zero), 8);
    

/*
	// send file
	FILE *f;
    f = fopen(argv[1],"r");		// open file given in terminal
	// read data from file
	int bytes_read;
    while (!feof(f)) {
        bytes_read = fread(&send_data,1,sizeof(send_data),f);
    }
*/
	sendto(sockfd, send_data, bytes_read, 0, (struct sockaddr *)&server_addr, sizeof(struct sockaddr));
    fclose(f);

    return 0;
}
