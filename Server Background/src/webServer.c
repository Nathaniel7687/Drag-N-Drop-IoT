#include "webServer.h"
#include "buildProgram.h"
#include "recvDeviceInfo.h"
#include <math.h>

int main()
{
    pthread_t p_thread[MAX_THREAD];
    int tid;
    int status;

    tid = pthread_create(&p_thread[0], NULL, thread_recvDeviceInfoFromClient, NULL);
    if (tid < 0) {
        perror("thread_recvDeviceInfoFromClient() create error");
        exit(1);
    }

    tid = pthread_create(&p_thread[1], NULL, thread_buildProgramFromServer, NULL);
    if (tid < 0) {
        perror("thread_buildProgramFromServer() create error");
        exit(1);
    }

    for (int i = 0; i < MAX_THREAD; i++) {
        pthread_join(p_thread[i], (void**)&status);
    }

    return 0;
}

void delay(float time)
{
    struct timespec req = { 0 };
    double s;
    double ms;
    ms = modf(time, &s) * 1000000000;

    req.tv_sec = s;
    req.tv_nsec = ms;
    nanosleep(&req, NULL);
}

void printfln()
{
    printf("\n");
}
