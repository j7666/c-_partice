#ifndef PUB_H
#define PUB_H

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "unistd.h"
#include <string.h>
#include <errno.h>
#include <signal.h>

#include <sys/socket.h>
#include <arpa/inet.h>


void setdaemon();

int signal1(int signo, void (*func)(int));

void catch_Signal(int Sign);

int socket_creat(int port);



#endif // PUB_H
