#ifndef ROOMREQUEST_H
#define ROOMREQUEST_H
#include "wftime.h"
#include "requirements.h"
typedef struct { //invariant details of request
	int req_no;
	int noofpeople; //It is request no. a primary key making each request unique
				//we limit hereby the maximum no. of total requests by size of int
	wftime start_time; //start time of room booking
	wftime end_time; //ending time of room booking
	requirements roomspecs; //room specifications are specified hereby
	int costumerNo; //0 if anonymous as registration no. of registered customer
} roomreq;
#endif
