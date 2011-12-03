#ifndef NETWORK_UTILS_H
#define NETWORK_UTILS_H
#include "network.h"
#include "net_message.h"
#include <stdio.h>
#include <unistd.h>

int sendFile(clientId_t *thisClient, FILE *fp);
int downloadFile(clientId_t *thisClient, netMessage_t *message, FILE *fp);
int confirmConnectionStatus(clientId_t *thisClient, char *safetyBuffer, int sizeofbuff);

#endif
