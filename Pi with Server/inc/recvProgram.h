#include <arpa/inet.h>
#include <errno.h>
#include <math.h>
#include <netinet/in.h>
#include <pthread.h>
#include <stdbool.h> // bool, true, false
#include <stdio.h>
#include <stdlib.h>
#include <string.h> // memsest()
#include <sys/socket.h>
#include <sys/stat.h>
#include <unistd.h> // read(), write(), access(), R_OK, W_OK

#define MILLISECOND 100000
#define MAX_FILE_BUFF_SIZE 512

void delay(float);
void printfln();

void* thread_recvProgramFromServer(void* data);
