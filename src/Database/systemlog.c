#include "systemlog.h"

int systemLogRecord(char *message, int mode)
{
	static pthread_mutex_t logfilemutex = PTHREAD_MUTEX_INITIALIZER;
	static FILE *fp = NULL;
	
	pthread_mutex_lock(&logfilemutex);
	if(mode == 1)
	{
		fp = fopen(message, "w");
		if(fp == NULL)
		{
			pthread_mutex_unlock(&logfilemutex);
			return -1;
		}
		pthread_mutex_unlock(&logfilemutex);
		return 0;
	}	
	if(mode == 0)
	{
		if(fp == NULL)
		{
			return -1;
		}
		fprintf(fp ,"%s\n",message);
		pthread_mutex_unlock(&logfilemutex);
		return 0;
	}
	if(mode == 2)
	{
		if(fp == NULL)
		{
			return -1;
		}
		fclose(fp);
		pthread_mutex_unlock(&logfilemutex);
		return 0;
	}
}

