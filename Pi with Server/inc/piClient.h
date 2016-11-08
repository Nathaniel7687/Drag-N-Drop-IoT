#include <pthread.h>
#include <stdbool.h> // bool, true, false
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h> // read(), write(), access(), R_OK, W_OK

#define MAX_THREAD 2
#define MILLISECOND 100000

void delay(float);
void printfln();
