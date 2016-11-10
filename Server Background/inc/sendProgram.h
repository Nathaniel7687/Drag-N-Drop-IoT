#include <arpa/inet.h>
#include <errno.h>
#include <math.h>
#include <netinet/in.h>
#include <pthread.h>
#include <stdbool.h> // bool, true, false
#include <stdio.h>
#include <stdlib.h>
#include <string.h> // memset()
#include <sys/socket.h>
#include <time.h>
#include <unistd.h> // read(), write(), access(), R_OK, W_OK

#define MILLISECOND 100000
#define MAX_FILE_BUFF_SIZE 512

void delay(float);
void printfln();
void* thread_sendProgramToClient(void* data);
