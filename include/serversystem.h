#ifndef SERVERSYSTEM_H
#define SERVERSYSTEM_H
#include "network.h"
#include "network_utils.h"
#include "net_message.h"
#include "fileaccess.h"
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>
#include <assert.h>
#include <signal.h>
#include "clientcommsrelay.h"
#include "serverprocedure.h"

#define DAEMON_NAME "csp_ticketing_system"
#define PID_FILE "/var/run/csp_ticketing_system.pid"


void serverProcess(serverId_t *thisServer);
void *handleClient(void *in);
void signal_handler(int sig);
void createServerDaemon(int portno);

#endif
