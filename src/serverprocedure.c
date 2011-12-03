#include "serverprocedure.h"


int confirmId(netMessage_t message, clientCommsRelay_t *thisClient)
{
	int i;
	char *str;
	customerinfo customer; 
	int idNo;
	netMessage_t newmessage;
	
	if(message.opcode != PASSWORD_MESSAGE && message.details == 0)
	{
		printf("ERROR : not a PASSWORD_MESSAGE\n");
		return -1;
	}
	
	bzero(&customer, sizeof(customerinfo));
	bcopy(message.buffer, &customer, sizeof(customer));
	
	idNo = checkUsername(customer);
	if(idNo < 0)
	{
		bzero(&newmessage, sizeof(netMessage_t));
		newmessage.opcode = PASSWORD_MESSAGE;
		newmessage.details = -1;
		sendData(thisClient->clientId, &newmessage , sizeof(netMessage_t));
		return -2;
	}
	else
	{
		bzero(&newmessage, sizeof(netMessage_t));
		newmessage.opcode = PASSWORD_MESSAGE;
		newmessage.details = idNo;
		sendData(thisClient->clientId, &newmessage , sizeof(netMessage_t));
		thisClient->idNo = idNo;
		return idNo;
	}
	return -1;
}



int writeRequest(netMessage_t message, clientCommsRelay_t *thisClient)
{
	
	if(message.opcode  != REQUEST_WRITE)
	{
		printf("ERROR : opcode wrong REQUEST_WRITE\n");
		return -1;
	}
	
	netMessage_t newmessage;
	roomreq newroomreq;
	bzero(&newroomreq, sizeof(roomreq));
	bcopy(message.buffer, &newroomreq, sizeof(roomreq));
	int retval = newRoomRequest(thisClient->idNo, newroomreq);
	if(retval < 0)
	{
		newmessage.opcode = FAILURE_PROCESS;
		sendData(thisClient->clientId, &newmessage, sizeof(netMessage_t));
		return -2;
	}
	else
	{
		newmessage.opcode = SUCCESS_PROCESS;
		sendData(thisClient->clientId, &newmessage, sizeof(netMessage_t));
		return retval;
	}	
}

int removeRequest(netMessage_t message, clientCommsRelay_t *thisClient)
{
	int retval;
	netMessage_t newmessage;
	bzero(&newmessage, sizeof(netMessage_t));
	
	if(message.opcode != REQUEST_REMOVE)
	{
		printf("ERROR : opcode wrong REQUEST_REMOVE\n");
		return -1;
	}
	
	retval = deleteRoomRequest(thisClient->idNo, message.details);
	if(retval < 0)
	{
		newmessage.opcode = FAILURE_PROCESS;
		sendData(thisClient->clientId, &newmessage, sizeof(netMessage_t));
		return -2;
	}
	else
	{
		newmessage.opcode = SUCCESS_PROCESS;
		sendData(thisClient->clientId, &newmessage, sizeof(netMessage_t));
		return retval;
	}
	return -1;
}


int returnFile(netMessage_t message, clientCommsRelay_t *thisClient)
{
	netMessage_t newmessage;
	bzero(&newmessage, sizeof(netMessage_t));
	
	if(message.opcode != FILE_TRANSFER_CODE)
	{
		printf("ERROR : opcode wrong FILE_TRANSFER_CODE\n");
		return -1;
	}
	
	FILE *fp = returnFilePointer(thisClient->idNo, message.details);
	
	if(fp == NULL)
	{
		newmessage.opcode = FAILURE_PROCESS;
		sendData(thisClient->clientId, &newmessage, sizeof(netMessage_t));
		return -2;		
	}	

	if(sendFile(thisClient->clientId, fp) == 0)
	{
		printf("ERROR : couldnot transfer file\n");
		return -2;
	}
	else
	{
		return 0;
	}
	return -1;
}


int changeRequestStatus(netMessage_t message, clientCommsRelay_t *thisClient)
{

	netMessage_t newmessage;
	bzero(&newmessage, sizeof(netMessage_t));
	
	if(message.opcode != REQUEST_CHANGE)
	{
		printf("ERROR : wrong_opcode REQUEST_CHANGE\n");
		return -1;
	}	
	int retval = changeRoomRequest(thisClient->idNo, message.details, message.buffer[0]);
	
	if(retval < 0)
	{
		newmessage.opcode = FAILURE_PROCESS;
		sendData(thisClient->clientId, &newmessage, sizeof(netMessage_t));
		return -2;
	}
	else
	{
		newmessage.opcode = SUCCESS_PROCESS;
		sendData(thisClient->clientId, &newmessage, sizeof(netMessage_t));
		return 0;	
	}
}
