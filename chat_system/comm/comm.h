#pragma once

#include <iostream>
#include <stdlib.h>
#include <stdio.h>

#include <errno.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>

#define _SIZE_ 1024
#define _IP_  "127.0.0.1"
#define _PORT_  8080

void print_log(const char* err , const char* fun, int line );


