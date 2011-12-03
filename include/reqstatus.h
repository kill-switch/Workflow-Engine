#ifndef REQSTATUS_H
#define REQSTATUS_H
#include "roomrequest.h"
#include "customerinfo.h"
#include "roomrequest.h"
#include "customerinfo.h"
#include "roominfo.h"

typedef struct {//structure to store current status of a request
	int reqno;//request no. of concerned request
	customerinfo cinf;
	roomreq reqs;
	char num[5];//0 if not alloted o.w. alloted value
	char currstat;//'0' if denied '1' if approved '2' if waiting
}request;
#endif
