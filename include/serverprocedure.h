#ifndef SERVERPROCEDURE_H
#define SERVERPROCEDURE_H
#include "network.h"
#include "network_utils.h"
#include "net_message.h"
#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include "systemlog.h"
#include "customerinfo.h"
#include "clientcommsrelay.h"
#include "roomrequest.h"
#include "foo.h"


int confirmId(netMessage_t message, clientCommsRelay_t *thisClient);
int writeRequest(netMessage_t message, clientCommsRelay_t *thisClient);
int removeRequest(netMessage_t message, clientCommsRelay_t *thisClient);
int returnFile(netMessage_t message, clientCommsRelay_t *thisClient);
int changeRequestStatus(netMessage_t message, clientCommsRelay_t *thisClient);


#endif
