#ifndef FILEACCESS_H
#define FILEACCESS_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>


FILE *getFileAccess(char *filelocation, char *accessMethod);
int makeFileAccess(char *filelocation);
int deleteFileAccess(char *filelocation);

#endif
