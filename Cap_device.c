#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>
#include <unistd.h>
#include <bool.h>
#include <firewall.h>

#define SORT_PORT 1719
#define LINESIZE 80
int main(int argc,char *argv[]){
    struct sockaddr_in server;
    struct hostent *host_info;
    int sock, count;

    int key_buff;
    int lim_buff;


    char inlin[LINESIZE]; /*buffer to copy from user to server*/
    char outline[LINESIZE + 1];/*buffer to copy from server to user*/
    char *server_name;
    /*get server name from command line. if none, use'local host'*/
    server_name =(argc>1) ? argv[1] :"localhost";
    /*create the socket*/
    sock=socket(AF_INET,SOCK_STREAM,0);
    if(sock<0) {
        perror("creating stream socket");
        exit(1);
    }
    host_info=gethostbyname(server_name);
    if(host_info==NULL){
        fprintf(stderr,"%s:unknown host: %s\n",argv[0],server_name);
        exit(2);
    }
    /*set up the server's socket address, then connect*/
    server.sin_family=host_info->h_addrtype;
    memcpy((char *)&server.sin_addr,host_info->h_addr,host_info->h_length);
    server.sin_port=htons(SORT_PORT);
    if(connect(sock,(struct sockaddr *)&server,sizeof (server))<0){
        perror("connecting to server");
        exit(3);
    }
    int wordIndex = 0;
    printf("\nClient: connect to server %s\n",server_name);
    //printf("Client: Write word %d to sort at server:\n", ++wordIndex);

    int data = recv(*(int*s)s, &key_buff,LINESIZE,0);
    int data = recv(*(int*s)s, &lim_buff,LINESIZE,0);

    if(firewall(key_buff,lim_buff) == true)
    {
        printf("Accepted packet with value %d \n", key);
    }

    if(firewall(key_buff,lim_buff) == false)
    {
        printf("Blocked packet with value %d \n", key);
    }

/*
    while((count=read(0, outline,LINESIZE))>0)
    {
        //printf("Client: count = %d\n",count);

        outline[count]='\0';



        if(write(sock, outline,count + 1)<0)
            printf("writing to server failed\n");
        if(outline[0]=='0')
            break;
        printf("Client: sending word to server: %s",outline);
        printf("\nClient: Write word %d to sort at server:\n", ++wordIndex);
    }
    printf("Client: results are...\n");
    while ((count=read(sock,inlin,LINESIZE)) > 0) {
        //printf("Client:");
        write(1,inlin,count);
        printf("\n");
    }
    return (0);
*/
}