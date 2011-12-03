#ifndef NET_MESSAGE_H
#define NET_MESSAGE_H
#include <unistd.h>
#include <stdio.h>

typedef struct
{
	char opcode;
	int details;
	char buffer[100];
}netMessage_t;

/*
*********************************************************
				Message opcode Def
*********************************************************
*/

#define FILE_TRANSFER_CODE 'f'
#define FILE_TRANSFER_START 'g'
#define FILE_TRANSFER_END 'h'
#define FILE_TRANSFER_RECIEVED 'i'

#define EXISTANCE_CHECK 'e'
#define DISCONNECT_SIG 'd'
#define EXISTANCE_CONFIRM 'c'
#define EXIT_DAEMON_PROCESS 'm'

#define PASSWORD_MESSAGE 'a'

#define REQUEST_WRITE 'r'
#define REQUEST_REMOVE 'q'
#define REQUEST_CHANGE 'p'

#define SUCCESS_PROCESS 's'
#define FAILURE_PROCESS 't'

#define UPDATE_FILE 'u'

#endif
