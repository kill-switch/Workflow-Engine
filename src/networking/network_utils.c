#include "network_utils.h"

int sendFile(clientId_t *thisClient, FILE *fp)
{
	int i = 0;
	char buffer[256];
	int n;
	char c = '1';
	netMessage_t temp;
	
	bzero(&temp, sizeof(netMessage_t));
	temp.opcode = FILE_TRANSFER_CODE;
	
	if(sendData(thisClient, &temp, sizeof(netMessage_t)) == 0)
	{
		printf("ERROR : in sending file transfer code\n");
		return 0;
	
	}
	bzero(&temp, sizeof(netMessage_t));
	if(recieveData(thisClient, &temp, sizeof(netMessage_t)) == 0)
	{
		printf("ERROR : reciciving file start code\n");
		return 0;
	}
	if(temp.opcode != FILE_TRANSFER_START)
	{
		printf("ERROR : the client didnot send a file start code\n");
		return 0;
	}
	
	bzero(buffer,256);
	
	while((c = getc(fp))  != EOF)
	{
		
		buffer[i] = c;		
		i++;
		if(i == 255)
		{
			buffer[256] = '\0';
			i = 0;
			if(sendData(thisClient, buffer, 256) == 0)
			{
				printf("ERROR : IN FILE SENDING\n");
				return 0;
			}
				printf("\n%s\n",buffer);
			bzero(buffer, 256);
		}
	}

	if(i < 256)
	{
		if(sendData(thisClient, buffer, 256) == 0)
		{
			printf("ERROR : IN FILE SENDING\n");
			return 0;
		}

	}
	
	bzero(&temp, sizeof(netMessage_t));
	temp.opcode = FILE_TRANSFER_END;
	if(sendData(thisClient, &temp, sizeof(netMessage_t)) == 0)
	{
		printf("ERROR : In sending fileend confirm\n");
		return 0;
	}
	bzero(&temp, sizeof(netMessage_t));
	if(recieveData(thisClient, &temp, sizeof(netMessage_t)) == 0)
	{
		printf("ERROR : reciciving file start code\n");
		return 0;
	}
	if(temp.opcode != FILE_TRANSFER_RECIEVED)
	{
		printf("ERROR : recieving confirmation not given\n");
		return 0;
	}
	return 1;
}




int downloadFile(clientId_t *thisClient, netMessage_t *message, FILE *fp)
{
	int i;
	char buffer[256];
	int n;
	netMessage_t temp;
	
	if(message->opcode != FILE_TRANSFER_CODE)
	{
		printf("ERROR : WRONG OPCODE SENT\n");
		return 1;
	}
	if(fp == NULL)
	{
		printf("ERROR : FILE SENT IS NULL\n");
		return 2;
	}
	
	
	bzero(&temp, sizeof(netMessage_t));
	temp.opcode = FILE_TRANSFER_START;
	
	if(sendData(thisClient, &temp, sizeof(netMessage_t)) == 0)
	{
		printf("ERROR : TRANSFER START COULDNT BE SENT\n");
		return 3;
	}
	
	
	// details here refer to file packet that it will recieve
	while(1)
	{
		bzero(buffer, 256);
		n = recieveData(thisClient, buffer, 256);
		printf("\n%s\n",buffer);
		if(n == sizeof(netMessage_t))
		{
			bcopy(buffer, &temp, sizeof(netMessage_t));
			if(temp.opcode == FILE_TRANSFER_END)
			{
				bzero(&temp, sizeof(netMessage_t));
				temp.opcode = FILE_TRANSFER_RECIEVED;
				if(sendData(thisClient, &temp, sizeof(netMessage_t)) == 0)
				{
					printf("ERROR : TRANSFER RECIEVED COULDNT BE SENT\n");
					return 4;
				}
				break;
			}
		}
		if(n <= 0)
		{
			printf("ERROR : FILE_TRANSFER recieved a zero or negative paket size\n");
			return 5;
		}
		else
		{
			fprintf(fp ,"%s", buffer);					
		}
	}
	return 0;
}


int confirmConnectionStatus(clientId_t *thisClient, char *safetyBuffer, int sizeofbuff)
{
	netMessage_t message;
	char buffer[256];
	int n;
				
	if(thisClient == NULL)
	{
		return 0;	
	}
	
	if(thisClient->isDisconnect == 1)
	{
		return 0;
	}
	message.opcode = EXISTANCE_CHECK;
	if(sendData(thisClient, &message, sizeof(netMessage_t)) == 0)
	{
		printf("ERROR : COULDNT WRITE to THIS CLIENT\n");
		return -1;	
	}
	sleep(20);
	bzero(buffer,256);
	if(thisClient->newinput <= 0)
	{
		disconnectClient(thisClient);
		return 0;
	}
	n = recieveData(thisClient, buffer, 256);
	if(n == 0)
	{
		disconnectClient(thisClient);
		return 0;
	}
	if(n == sizeof(netMessage_t))
	{
		bcopy(buffer, &message, sizeof(netMessage_t));
		if(message.opcode == EXISTANCE_CONFIRM)
		{
			return 1;
		}
	}
	if(n > 0)
	{
		bzero(safetyBuffer, sizeofbuff);
		bcopy(buffer, safetyBuffer, sizeofbuff);
		return 2;
	}		
}
