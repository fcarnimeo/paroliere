#ifndef INCLUDES_H
#define INCLUDES_H

#include <ctype.h>
#include <fcntl.h>
#include <getopt.h>
#include <limits.h>
#include <pthread.h>
#include <signal.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/mman.h>
#include <sys/select.h>
#include <sys/stat.h>
#include <sys/socket.h>

#include "init.h"
#include "matrix.h"
#include "serverState.h"

#define MATRIX_SIZE 4

#endif // INCLUDES_H