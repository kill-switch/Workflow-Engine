#ifndef SYSTEMLOG_H
#define SYSTEMLOG_H
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

int systemLogRecord(char *message, int mode);

#endif
