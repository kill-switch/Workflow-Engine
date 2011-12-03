#include "fileaccess.h"


FILE *getFileAccess(char *filelocation, char *accessMethod)
{
	int i;
	FILE *fp;
	char tempstring[10];
	bzero(tempstring, 10*sizeof(char));
	int j = 0;

	int depthinstruct = 0;
		
	for(i = 0 ; ; i++)
	{
		if(filelocation[i] == '/')
		{
			tempstring[j] = '/';
			if(chdir(tempstring) != 0)
			{
				printf("ERROR : couldnt open the directory\n");
				return NULL;
			}
			bzero(tempstring, 10*sizeof(char));
			j = 0;
			depthinstruct++;
			continue;
		}
		if(filelocation[i] == '\0')
		{
			fp = fopen(tempstring, accessMethod);
			for(j = 0; j< depthinstruct; j++)
			{
				chdir("../");
			
			}
			return fp;
		}
		else
		{
			tempstring[j] = filelocation[i];
			j++;
		}
	}
}



int makeFileAccess(char *filelocation)
{
	int i;
	FILE *fp;
	char tempstring[10];
	bzero(tempstring, 10*sizeof(char));
	int j = 0;

	int depthinstruct = 0;
		
	for(i = 0 ; ; i++)
	{
		if(filelocation[i] == '/')
		{
			tempstring[j] = '/';
			if(chdir(tempstring) != 0)
			{
				if(mkdir(tempstring, S_IRWXU) != 0)
				{
					printf("ERROR : couldnt CREATE the directory\n");
					return -1;	
				}
			}
			bzero(tempstring, 10*sizeof(char));
			j = 0;
			depthinstruct++;
			continue;
		}
		if(filelocation[i] == '\0')
		{
			fp = fopen(tempstring, "w");
			fprintf(fp,"");
			fclose(fp);
			for(j = 0; j< depthinstruct; j++)
			{
				chdir("../");
			
			}
			return 0;
		}
		else
		{
			tempstring[j] = filelocation[i];
			j++;
		}
	}
}


int deleteFileAccess(char *filelocation)
{
	int i;
	FILE *fp;
	char tempstring[10];
	bzero(tempstring, 10*sizeof(char));
	int j = 0;

	int depthinstruct = 0;
		
	for(i = 0 ; ; i++)
	{
		if(filelocation[i] == '/')
		{
			tempstring[j] = '/';
			if(chdir(tempstring) != 0)
			{
				printf("ERROR : couldnt CREATE the directory\n");
				return -1;	
			}
			bzero(tempstring, 10*sizeof(char));
			j = 0;
			depthinstruct++;
			continue;
		}
		if(filelocation[i] == '\0')
		{
			if(remove(tempstring) == -1)
			{
				printf("ERROR : couldnt delete file\n");
				return -1;
			}
			for(j = 0; j< depthinstruct; j++)
			{
				chdir("../");
			}
			return 0;
		}
		else
		{
			tempstring[j] = filelocation[i];
			j++;
		}
	}
}

