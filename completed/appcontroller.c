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
#include "auth.h"
#define LIMIT 1000

int main(void)
{
    int sockfd;
    struct sockaddr_in server_addr;
    char send_data[1024];
    struct hostent *host = (struct hostent *)gethostbyname((char *)"127.0.0.1");
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) == -1)
    {
        perror("socket");
        exit(1);
    }
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(5015);
    server_addr.sin_addr = *((struct in_addr *)host->h_addr);
    bzero(&(server_addr.sin_zero), 8);
    printf("you are the application: enter your key, type 'auth' to randomly generate a key, or press q to quit\n"); //print out command message
    while (1)
    {
        
        fgets(send_data, 1024, stdin);
        send_data[strlen(send_data) - 1] = '\0';
        if ((strcmp(send_data, "q") == 0) || strcmp(send_data, "Q") == 0){//check for quit command
            break;
	}
	else if((strcmp(send_data, "auth") == 0)){//check if auth is requested
		char autharr[10];
		auth(LIMIT, autharr);
		printf("auth requested. key generated and sent to routers:%s\n",autharr);
		sendto(sockfd, autharr, strlen(send_data), 0, (struct sockaddr *)&server_addr, sizeof(struct sockaddr));
	}
        else{
	    printf("Cool! Key sent.\n");//confirm key is sent
            sendto(sockfd, send_data, strlen(send_data), 0, (struct sockaddr *)&server_addr, sizeof(struct sockaddr));
	}
    }
    
    return 0;
}
