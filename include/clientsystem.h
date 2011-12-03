#ifndef CLIENTSYSTEM_H
#define CLIENTSYSTEM_H
#include "network_utils.h"
#include "net_message.h"
#include "network.h"
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "gtk_menu.h"
#include <gtk/gtk.h>

void clientProcess(int portno, char *servername,int argc, char *argv[]);

#endif
