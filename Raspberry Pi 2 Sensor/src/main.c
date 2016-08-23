#include "main.h"
#include "manageProgram.h"
#include "sendDeviceInfo.h"
#include "uart_api.h" // UART Serial Communication API

int main()
{
    pthread_t p_thread[MAX_THREAD];
    int tid;
    int status;

    tid = pthread_create(&p_thread[0], NULL, thread_sendDeviceInfoToServer, NULL);
    if (tid < 0) {
        perror("thread_sendDeviceInfoToServer() create error\n");
        exit(0);
    }

    tid = pthread_create(&p_thread[1], NULL, thread_manageProgramFromServer, NULL);
    if (tid < 0) {
        perror("thread_manageProgramFromServer() create error\n");
        exit(0);
    }

    for (int i = 0; i < MAX_THREAD; i++) {
        pthread_join(p_thread[i], (void**)&status);
    }

    return 0;
}

void delay_millisecond(int ms)
{
    struct timespec req = { 0 };
    req.tv_sec = 0;
    req.tv_nsec = ms * 10000000;
    nanosleep(&req, NULL);
}

void printfln()
{
    printf("\n");
}
