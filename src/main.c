#include "clientsystem.h"
#include "serversystem.h"

int main(int argc, char *argv[])
{
	#if defined (CLIENT)
		clientProcess(atoi(argv[1]),argv[2], argc, argv);
	#else
		createServerDaemon(atoi(argv[1]));
	#endif
}

