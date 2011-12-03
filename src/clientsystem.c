#include "clientsystem.h"



void clientProcess(int portno, char *servername,int argc, char *argv[])
{
	client_state_t client;
	
	bzero(&client, sizeof(client_state_t));
	client.thisClient = createClient(portno, "Ubuntu");
	
	gtk_init(&argc, &argv);
	welcomeScreen(&client);
	gtk_main();
		
}


