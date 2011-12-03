#ifndef SERVERCOMMSRELAY_H
#define SERVERCOMMSRELAY_H

typedef struct 
{
	int idNo;
	pthread_t clientThread;
	clientId_t *clientId;
	//directoryStruct *thisStruct;
	char closeAlloperations;
}clientCommsRelay_t;

#endif
