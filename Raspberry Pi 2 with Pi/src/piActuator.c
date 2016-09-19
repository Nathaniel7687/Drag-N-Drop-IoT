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
#include "piActuator.h"
#include "uart_api.h"

int main()
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
        if (read(client_fd, &sensor, sizeof(Sensor)) > 0)
        {
            printf("> Client(%s) is connected\n", inet_ntoa(client_addr.sin_addr));
            printf("  Ultrasonic\t: %03d\t\t IR\t\t: %d\n", sensor.ultrasonic, sensor.ir);
            printf("  Humidity\t: %02d\t\t Temperature\t: %02d\n", sensor.humidity, sensor.temperature);
            printf("  Heatindex\t: %02.2f\t\t Light\t\t: %03d\n", sensor.heatindex, sensor.light);
            printf("  Gas\t\t: %04d\n", sensor.gas);

            
        }
        else
        {
            printf("  Client(%s) Timeout Count: %d\n", inet_ntoa(client_addr.sin_addr), timeout++);

            if (timeout > 60)
            {
                printf("> Client(%s) is closed..\n", inet_ntoa(client_addr.sin_addr));
                close(client_fd);
            }

            delay(1);
        }
    }

    return 0;
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
    nanosleep(&req, NULL);
}

void printfln()
{
    printf("\n");
}
