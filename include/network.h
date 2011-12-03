#ifndef NETWORK_H
#define NETWORK_H
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <pthread.h>
#include "net_message.h"


typedef struct
{
	int sockfd;
	
	pthread_t clientThread;
	pthread_mutex_t *inputMutex;
	pthread_mutex_t *outputMutex;
	
	char outbuffer[256];
	char inputbuffer[256];
	int newinput;
	int newoutput;
	
	char isDisconnect;// a flag to tell if it is disconnected or not
}clientId_t;


typedef struct
{
	int portno;
	int	sockfd;
	
	char isNewClient;// Flag to Indiacte a new client is recieved
	clientId_t *newClientId;
	
	pthread_t acceptClientThread;
	pthread_mutex_t *clientThreadMutex;
	char closeAlloperations;// Flag to Close all opeartions
}serverId_t;



void *doCommsInput(void *clientdet);
void *doComms(void *clientdet);
void *acceptClient(void *servdet);
serverId_t *createServer(int portno);
clientId_t *createClient(int portno, char *hostname);
clientId_t *isNewClient(serverId_t *thisServer);
int recieveData(clientId_t *thisClient,void *in, int sizelen);
int sendData(clientId_t *thisClient, void *out, int sizelen);
void disconnectClient(clientId_t *thisClient);
void closeServer(serverId_t *thisServer);

#endif
