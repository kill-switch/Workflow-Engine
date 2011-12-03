#include "network.h"


void *doCommsInput(void *clientdet)
{
	clientId_t *thisClient = (clientId_t *)clientdet;
		
	int n;
	char tempbuff[256];
	while(thisClient->isDisconnect == 0)
	{
		n = 0;
		n = read(thisClient->sockfd,tempbuff , 256);
		if(n < 0)
		{
			printf("ERROR : coulnt read socket\n");
			continue ;	
		}
		if(n > 0)
		{
			while(thisClient->newinput > 1)
			{
				// wait
			}
			bzero(thisClient->inputbuffer, 256);
			bcopy(tempbuff, thisClient->inputbuffer, 256);
			pthread_mutex_lock(thisClient->inputMutex);
			thisClient->newinput = n;
			pthread_mutex_unlock(thisClient->inputMutex);
		}
	}
	printf("SYSTEM LOG : DISCONNECTING\n");
}


void *doComms(void *clientdet)
{
	clientId_t *thisClient = (clientId_t *)clientdet;
	
	pthread_mutex_t inputmutex = PTHREAD_MUTEX_INITIALIZER;
	thisClient->inputMutex = &inputmutex;
	
	pthread_mutex_t outputMutex = PTHREAD_MUTEX_INITIALIZER;
	thisClient->outputMutex = &outputMutex;	
	pthread_t doCommsInputthread;
	
	int iret = pthread_create(&doCommsInputthread , NULL, doCommsInput, (void *) thisClient);
	if(iret < 0)
	{
		printf("ERROR : docomms Input Thread Couldnot be created\n");
		exit(1);
	}
	
	int n;
	while(thisClient->isDisconnect == 0)
	{
		if(thisClient->newoutput > 0)
		{
			n = 0;
			n = write(thisClient->sockfd, thisClient->outbuffer, thisClient->newoutput);
			if(n < 0)
			{
				printf("ERROR : Couldnot transmit data\n");
				pthread_mutex_lock(thisClient->outputMutex);		
				thisClient->newoutput = -1;
				pthread_mutex_unlock(thisClient->outputMutex);
			}
			else
			{
				pthread_mutex_lock(thisClient->outputMutex);	
				thisClient->newoutput = 0;
				pthread_mutex_unlock(thisClient->outputMutex);
			}
		}	
	}
	pthread_join(doCommsInputthread, NULL);
	printf("SYSTEM LOG: disconnecting 2\n");	
}



void *acceptClient(void *servdet)
{
	serverId_t *thisServer = (serverId_t *)servdet;
	int tempsock;
	clientId_t *tempId;
	struct sockaddr_in cli_addr;
	int clilen = sizeof(cli_addr);
	int iret;
	
	while(thisServer->closeAlloperations == 0)
	{
		listen(thisServer->sockfd, 5);
		tempsock = accept(thisServer->sockfd, (struct sockaddr *) &cli_addr, &clilen);
		
		if(tempsock < 0)
		{
			printf("ERROR : client couldnot be accepted\n");
		
		}
		else
		{
			while(thisServer->isNewClient == 1)
			{
				// wait 
			}
			tempId = (clientId_t *)malloc(sizeof(clientId_t));
	
			tempId->sockfd = tempsock;
			bzero((char *)&tempId->outbuffer,256);
			bzero((char *)&tempId->inputbuffer,256);
			tempId->newinput = 0;
			tempId->newoutput = 0;
			tempId->isDisconnect = 0;
	
			iret = pthread_create(&tempId->clientThread, NULL, doComms, (void *)tempId);
			if(iret < 0)
			{
				printf("ERROR : Couldnt create a doComms Thread\n");
				exit(1);
			}
	
			pthread_mutex_lock(thisServer->clientThreadMutex);
			thisServer->isNewClient = 1;
			thisServer->newClientId = tempId;
			pthread_mutex_unlock(thisServer->clientThreadMutex);
			
		}
	}
}


serverId_t *createServer(int portno)
{
	serverId_t *thisServer = (serverId_t *)malloc(sizeof(serverId_t));
	thisServer->portno = portno;
	int iret;
	struct sockaddr_in serv_addr;
	
	
	pthread_mutex_t servMutex = PTHREAD_MUTEX_INITIALIZER;
	thisServer->clientThreadMutex = &servMutex;
	
	thisServer->sockfd = socket(AF_INET, SOCK_STREAM, 0);
	
	thisServer->isNewClient = 0;
	thisServer->closeAlloperations =0;
	
	// Creating a Tcp Socket
	if(thisServer->sockfd < 0)
	{
		printf("ERROR : Couldnot create socket\n");
		exit(1);
		//return NULL;
	}
	
	bzero((char *) &serv_addr , sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	serv_addr.sin_port = htons(thisServer->portno);
	
	// binding Socket to a portno
	if( bind(thisServer->sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
	{
		printf("ERROR : Couldnot bind the socket\n");
		exit(1);
		//return Null;
	}
	
	// Creating thread for accepting clients;
	iret = pthread_create(&thisServer->acceptClientThread, NULL, acceptClient,(void *)thisServer);
	if(iret < 0)
	{
		printf("ERROR : Unable to create accept client thread\n");
		exit(1);	
	}
	return thisServer;
}


clientId_t *createClient(int portno, char *hostname)
{
	clientId_t *thisClient = (clientId_t *)malloc(sizeof(clientId_t));
	int iret;
	struct sockaddr_in serv_addr;
	struct hostent *server;
	thisClient->sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(thisClient->sockfd  < 0)
	{
		printf("ERROR : client couldnt make the socket\n");
		exit(1);
	}
	
	server = gethostbyname(hostname);
	bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr,server->h_length);
    serv_addr.sin_port = htons(portno);
   
    while(connect(thisClient->sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0)
    {
    	printf(" jumping\n");
    }
    
	bzero((char *)&thisClient->outbuffer,256);
	bzero((char *)&thisClient->inputbuffer,256);
	thisClient->newinput = 0;
	thisClient->newoutput = 0;
	thisClient->isDisconnect = 0;
    iret = pthread_create(&thisClient->clientThread, NULL, doComms , (void *)thisClient);
    if(iret < 0)
    {
    	exit(1);   
    }   
    return 	thisClient;
}

clientId_t *isNewClient(serverId_t *thisServer)
{
	clientId_t *temp;
	if(thisServer->isNewClient == 1)
	{
		temp = thisServer->newClientId;
		pthread_mutex_lock(thisServer->clientThreadMutex);
		thisServer->isNewClient = 0;		
		pthread_mutex_unlock(thisServer->clientThreadMutex);
		return temp;
	}
	return NULL;
}


int recieveData(clientId_t *thisClient,void *in, int sizelen)
{
	char *buffer = (char *)	in;
	bzero(buffer, sizelen);
	int temp;
	if(thisClient->isDisconnect == 1)
	{
		printf("ERROR : send DATA this client has disconnected\n");
		return 0;
	}
	while(thisClient->newinput == 0)
	{
		// wait could also be made to do something else
	}
	if(thisClient->newinput > 0)
	{
		temp = thisClient->newinput;
		bcopy(thisClient->inputbuffer,buffer,sizelen);
		pthread_mutex_lock(thisClient->inputMutex);
		thisClient->newinput = 0;
		pthread_mutex_unlock(thisClient->inputMutex);
		return temp;
	}
	return 0;
}

int sendData(clientId_t *thisClient, void *out, int sizelen)
{
	char *buffer = (char *) out;
	int temp;
	if(thisClient->isDisconnect == 1)
	{
		printf("ERROR : send DATA this client has disconnected\n");
		return 0;
	}
	while(thisClient->newoutput > 0)
	{
		// wait for prev output to to be send		
	}
	if(thisClient->newoutput == 0)
	{
		while(thisClient->outputMutex == 0)
		{
		}
		bzero(thisClient->outbuffer, 256);
		bcopy(buffer, thisClient->outbuffer,sizelen);	
		pthread_mutex_lock(thisClient->outputMutex);
		thisClient->newoutput = sizelen;
		pthread_mutex_unlock(thisClient->outputMutex);
		return 1;
	}
	return 0;
}

void disconnectClient( clientId_t *thisClient )
{
	//sendData() any last messages	
	thisClient->isDisconnect = 1;
	pthread_join(thisClient->clientThread, NULL);
	shutdown(thisClient->sockfd, 2);
	free(thisClient);	
}

void closeServer(serverId_t *thisServer)
{
	thisServer->closeAlloperations = 1;
	pthread_join(thisServer->acceptClientThread, NULL);
	free(thisServer);
}
