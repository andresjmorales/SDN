#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include "firewall.h"
#define LIMIT 1000
#define NUMROUTERS 2000

int main(void)
{
    int sockfd;
    char recv_data[1024];
    struct sockaddr_in server_addr, client_addr;
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) == -1)
    {
        perror("Socket");
        exit(1);
    }
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(5015);
    server_addr.sin_addr.s_addr = INADDR_ANY;
    bzero(&(server_addr.sin_zero), 8);
    if (bind(sockfd,(struct sockaddr *)&server_addr, sizeof(struct sockaddr)) == -1)
    {
        perror("Bind");
        exit(1);
    }
    socklen_t addr_len = sizeof(struct sockaddr);
    srand(time(0));
    int routerid = rand()%NUMROUTERS;
    printf("router with id %d initialized\n", routerid);//generate id used for dijkstra
    printf("waiting for values...\n");
    fflush(stdout);
    while (1)
    {
        ssize_t bytes_read = recvfrom(sockfd,recv_data,1024,0,
                              (struct sockaddr *)&client_addr, &addr_len);
        recv_data[bytes_read] ='\0';
	firewall(recv_data, LIMIT);//call firewall to check values
        fflush(stdout);
    }
    
    return 0;
}
