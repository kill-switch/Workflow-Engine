#ifndef FOO_H
#define FOO_H
#include "roominfo.h"
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
#include "reqstatus.h"


int checkUsername(customerinfo customer);
int newRoomRequest(int idNo, roomreq req);
int deleteRoomRequest(int idNo, int reqno);
FILE *returnFilePointer(int idNo, int no);
int changeRoomRequest(int idNo, int reqno, char status);


#endif
