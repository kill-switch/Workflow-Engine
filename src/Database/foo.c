#include "foo.h"


int checkUsername(customerinfo customer)
{
	FILE *fp;
	char c = '1';
	char buffer[sizeof(customerinfo)];
	int i;
	customerinfo temp;
	
	/*
	fp = fopen("users","r");
	if(fp == NULL)
	{
		return -1;
	}
	
	while(c != EOF)
	{
		i =0;
		bzero(&temp, sizeof(customerinfo));
		bzero(buffer, sizeof(customerinfo));
		while((c= getc(fp)) != '\n')
		{
			buffer[i] = c;
			i++;
		}
		bcopy(buffer, &temp, sizeof(customerinfo));
		if(strcmp(temp.userId, customer.userId) == 0)
		{
			if(strcmp(temp.pass, customer.pass) == 0)
			{
				printf("%d",temp.idNo);
				return temp.idNo; 
			}
			return -1;
		}
	}
	*/
	return 1;
}

int newRoomRequest(int idNo, roomreq req2)
{
	static int w = 0;
	FILE *fp = fopen("request","a");
	pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
	pthread_mutex_lock(&mutex);
	int i = 0;
	char buffer[256];
	bzero(buffer, 256);
	request temp;
	temp.reqno = w;
	w++;
	temp.cinf.idNo = idNo;
	temp.reqs = req2;
	
	bcopy(&temp, buffer, sizeof(request));
	for(i = 0; i < sizeof(request); i++)
	{
		fprintf(fp,"%c",buffer[i]);
	}
	fprintf(fp, "\n");
	pthread_mutex_unlock(&mutex);
	return 0;
}

int deleteRoomRequest(int idNo, int reqno)
{
	return 0;
}

FILE *returnFilePointer(int idNo, int no)
{
	FILE *fp;
	fp = fopen("request", "w");
	return fp; 
}

int changeRoomRequest(int idNo, int reqno, char status)
{
	return 0;
}
