#include "serversystem.h"


void *handleClient(void *in)
{
	clientCommsRelay_t *clientRelay = (clientCommsRelay_t *)in;
	netMessage_t message;
				
	while(clientRelay->clientId->isDisconnect == 0)
	{
		bzero(&message, sizeof(netMessage_t));
		if( recieveData(clientRelay->clientId, &message, sizeof(netMessage_t)) == 0)
		{
			continue;		
		}
		
		if(message.opcode == PASSWORD_MESSAGE)
		{
			if(confirmId(message, clientRelay) != -1)
			{
				continue;
			}
		}	
		
		if(message.opcode == REQUEST_WRITE)
		{
			if(writeRequest(message, clientRelay) != -1)
			{
				continue;
			}
		}	
		if(message.opcode == REQUEST_REMOVE)
		{
			if(removeRequest(message, clientRelay) == -1)
			{
				continue;
			}
		}
		if(message.opcode == REQUEST_CHANGE)
		{
			if(changeRequestStatus(message, clientRelay) == -1)
			{
				continue;
			}
		}

		if(message.opcode == FILE_TRANSFER_CODE)
		{
			if(returnFile(message, clientRelay) == -1)
			{
				continue;
			}
		}		
	}
}


void serverProcess(serverId_t *thisServer)
{
	clientCommsRelay_t *tempRelay ;
	clientId_t *tempId = NULL;
	
	while(thisServer->closeAlloperations == 0)
	{
		tempId = isNewClient(thisServer);
		if(tempId != NULL)
		{
			tempRelay = (clientCommsRelay_t *)malloc(sizeof(clientCommsRelay_t));
			tempRelay->idNo = 0;	
			tempRelay->clientId = tempId;
			tempRelay->closeAlloperations = 0;
			pthread_create(&tempRelay->clientThread, NULL, handleClient,(void *) tempRelay);
			tempId = NULL;
		}		
	}
}



void signal_handler(int sig)
{
	switch(sig)
	{
		case SIGHUP:
			syslog(LOG_WARNING, "Recived SIGHUP signal\n");
		case SIGTERM:
			syslog(LOG_WARNING, "Recived SIGTERM signal\n");
		default :
			syslog(LOG_WARNING, "UNhandled signal  %s",strsignal(sig));
	}
}



void createServerDaemon(int portno)
{

	char cwd[1024];
	if(getcwd(cwd,sizeof(cwd)) == NULL)
	{
		printf("ERROR : current working directory unknown\n");
		exit(0);
	}
	
	#if defined(DEBUG)
		int daemonize = 0;
	#else
		int daemonize = 1;
	#endif
	
	signal(SIGHUP, signal_handler);
	signal(SIGTERM, signal_handler);
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, signal_handler);
	
	syslog(LOG_INFO, "%s daemon starting up", DAEMON_NAME);
	
	#if defined(DEBUG)
		setlogmask(LOG_UPTO(LOG_DEBUG));
		openlog(DAEMON_NAME, LOG_CONS | LOG_NDELAY | LOG_PERROR | LOG_PID ,LOG_USER);
	#else
		setlogmask(LOG_UPTO(LOG_INFO));
		openlog(DAEMON_NAME, LOG_CONS, LOG_USER);
	#endif
	
	pid_t pid, sid;
	
	if(daemonize)
	{
		syslog(LOG_INFO ,"Starting the daemon process");
		pid = fork();
		if(pid < 0)
		{
			exit(EXIT_FAILURE);
		}
		if(pid > 0)
		{
			exit(EXIT_SUCCESS);
		}
		umask(0);
		sid = setsid();
		if(sid < 0)
		{
			exit(EXIT_FAILURE);
		}

		if((chdir("/")) < 0)
		{
			exit(EXIT_FAILURE);
		}

		close(STDIN_FILENO);
		close(STDOUT_FILENO);
		close(STDERR_FILENO);
	}
	chdir(cwd);
	
	serverId_t *thisServer = createServer(portno);
	serverProcess(thisServer);
		
	syslog(LOG_INFO," %s Daemon exiting", DAEMON_NAME);
	exit(0);
}

