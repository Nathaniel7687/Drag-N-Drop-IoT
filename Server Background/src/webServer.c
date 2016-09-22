#include "webServer.h"
#include "sendProgram.h"
#include "recvDeviceInfo.h"
#include <errno.h>
#include <math.h>

int main()
{
    pthread_t p_thread[MAX_THREAD];
    int tid;
    int status;

    tid = pthread_create(&p_thread[0], NULL, thread_recvDeviceInfoFromClient, NULL);
    if (tid < 0)
    {
        perror("thread_recvDeviceInfoFromClient() create error");
        exit(1);
    }

    tid = pthread_create(&p_thread[1], NULL, thread_sendProgramToClient, NULL);
    if (tid < 0)
    {
        perror("thread_sendProgramToClient() create error");
        exit(1);
    }

    for (int i = 0; i < MAX_THREAD; i++)
    {
        pthread_join(p_thread[i], (void **)&status);
    }

    return 0;
}

void delay(float time)
{
    struct timespec req = {0};
    double s;
    double ms;
    ms = modf(time, &s) * 1000000000;

    req.tv_sec = s;
    req.tv_nsec = ms;
    while (nanosleep(&req, NULL) && errno == EINTR);
}

void printfln()
{
    printf("\n");
}
