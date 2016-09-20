#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdbool.h> // bool, true, false
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <math.h>
#include <string.h> // memset()
#include <sys/socket.h>
#include <termios.h>
#include <pthread.h>
#include <errno.h>
#include "piActuator.h"
#include "uart_api.h"

int main()
{
    pthread_t p_thread;
    int tid;
    int status;

    tid = pthread_create(&p_thread, NULL, thread_recvDeviceInfoFromClient, NULL);
    if (tid < 0)
    {
        perror("thread_recvDeviceInfoFromClient() create error");
        exit(1);
    }

    pthread_join(p_thread, (void **)&status);

    return 0;
}

void *thread_recvDeviceInfoFromClient(void *tData)
{
    int fd;
    int client_fd;
    int server_fd;
    struct sockaddr_in client_addr;
    struct sockaddr_in server_addr;
    int timeout = 0;
    Sensor sensor;

    if ((server_fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
    {
        printf("> Fail work to create socket fd!\n");
        exit(1);
    }

    printf("> Create server socket fd: %d\n", server_fd);

    memset((void *)&server_addr, 0x00, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr.sin_port = htons(12122);

    bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr));
    listen(server_fd, 5);

    socklen_t client_size = sizeof(client_addr);
    client_fd = accept(server_fd, (struct sockaddr *)&client_addr, &client_size);

    if (client_fd == -1)
    {
        perror("> Accept error");
    }

    openDevice(&fd);
    while (true)
    {
        char level[2];

        if (read(client_fd, &sensor, sizeof(Sensor)) > 0)
        {
            timeout = 0;
            printf("> Client(%s) is connected\n", inet_ntoa(client_addr.sin_addr));
            printf("  Ultrasonic\t: %03d\t\t IR\t\t: %d\n", sensor.ultrasonic, sensor.ir);
            printf("  Humidity\t: %02d\t\t Temperature\t: %02d\n", sensor.humidity, sensor.temperature);
            printf("  Heatindex\t: %02.2f\t\t Light\t\t: %03d\n", sensor.heatindex, sensor.light);
            printf("  Gas\t\t: %04d\n", sensor.gas);

            // TODO: Modify actuate condition.
            // BEGIN
            if (sensor.light > 800)
            {
                strcpy(level, "4");
            }
            else if (sensor.light > 600)
            {
                strcpy(level, "3");
            }
            else if (sensor.light > 400)
            {
                strcpy(level, "2");
            }
            else if (sensor.light > 200)
            {
                strcpy(level, "1");
            }
            else
            {
                strcpy(level, "0");
            }
            // END

            // TCIFLUSH	 수신했지만 읽어들이지 않은 데이터를 버립니다.
            // TCOFLUSH	 쓰기응이지만 송신하고 있지 않는 데이터를 버립니다.
            // TCIOFLUSH 수신했지만 읽어들이지 않은 데이터, 및 쓰기응이지만 송신하고 있지 않는 데이터의 양쪽 모두를 버립니다.
            tcflush(fd, TCIOFLUSH);
            user_uart_write(fd, (unsigned char *)level, 2);
            printf("  %d, %s\n", fd, level);
        }
        else
        {
            if (errno != EINTR)
            {
                printf("  Client(%s) Timeout Count: %d\n", inet_ntoa(client_addr.sin_addr), ++timeout);

                if (timeout > 60)
                {
                    printf("> Client(%s) is closed..\n", inet_ntoa(client_addr.sin_addr));
                    close(client_fd);
                    return 0;
                }

                delay(1);
            }
        }
    }
}

void openDevice(int *fd)
{
    if (access(USB_SERIAL, R_OK & W_OK) == 0)
    {
        printf("> %s is accessable\n", USB_SERIAL);

        *fd = user_uart_open(USB_SERIAL);
        if (*fd != -1)
        {
            user_uart_config(*fd, 115200, 8, 0, 1);

            printf("> %s is opened\n", USB_SERIAL);
            printf("> Configure UART: baud rate %d, data bit %d, stop bit %d, parity bit %d\n", BAUD_RATE, DATA_BIT, STOP_BIT, PARITY_BIT);
        }
        else
        {
            printf("> %s is not openned.\nPlease, check device!\n", USB_SERIAL);
            exit(1);
        }
    }
    else
    {
        printf("> %s is not accessable.\nPlease, check device!\n", USB_SERIAL);
        exit(1);
    }
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
