#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

#define SORT_PORT 1719
#define LINESIZE 80
#define NUMWORDS 50

void sort(char *str[],int n){
	int i, j;
	char temp[LINESIZE];
	for(i = n; i >= 0; i--) {
		for(j = 0; j < i - 1; j++) {
			if(strcmp(str[j], str[j + 1]) > 0) {
				strcpy(temp, str[j]);
				strcpy(str[j], str[j + 1]);
				strcpy(str[j + 1], temp);
			}
		}
	}
}

void* func (void *s)		// function to send all the words
{

	int i = 0;
	char buffer[LINESIZE];
	char *words[NUMWORDS]; //array of words
	struct sockaddr_in server,client;

	while(1)
	{			//
		int word_len = recv(*(int*)s, &buffer, LINESIZE, 0);
		if (strcmp(buffer, "0\n") == 0) {
			break;
		} else {
			words[i] = (char *) malloc(word_len);
			strcpy(words[i], buffer);
			printf("word added to words array: %s\n", buffer);
			printf("word spot: %d\n", i);
			i++;
		}
	}
	sort(words, i);
	int j;
	for (j = 0; j < i; j++) {
		int bytes_sent = send(*(int*)s, words[j], strlen(words[j]) + 1, 0);
	}

	close (*(int *) s);
	free(s);

}

int main (int argc, char *argv[])
{

	struct sockaddr_in server,client;
	int word_len, client_len, sockfdListen;

	int *sockfd;
	pthread_t thread; // creating storage

	if((sockfdListen = socket(AF_INET,SOCK_STREAM,0)) < 0)   {
		  perror("creating stream socket error!\n");
		  exit(1);
	}
	server.sin_family=AF_INET;
	server.sin_port=htons(SORT_PORT);
	server.sin_addr.s_addr=htonl(INADDR_ANY);   

	if(bind(sockfdListen,(struct sockaddr *)&server,sizeof(server)) < 0){
		  perror("error in binding!");
		  exit(1);
	}
	if(listen(sockfdListen,3)<0){
		  perror("error in listening!");
		  exit(1);
	}
	while(1)
	{
		client_len = sizeof(client);
		sockfd = malloc(sizeof(int));
		if((*sockfd=accept(sockfdListen,(struct sockaddr*)&client,&client_len))<0){
		     perror("error in binding!");
		     exit(1);
		}
		pthread_create(&thread, NULL, func, sockfd);

	}
	printf("\n\n");
	exit(0);
	return 0;
}














