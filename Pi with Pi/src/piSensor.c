#include <arpa/inet.h>
#include <stdbool.h> // bool, true, false
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h> // memset()
#include <math.h>
#include <sys/socket.h>
#include <termios.h>
#include <pthread.h>
#include <time.h>
#include <unistd.h>
#include <errno.h>
#include "piSensor.h"
#include "uart_api.h"
int main()
{
    pthread_t p_thread;
    int tid;
    int status;

    tid = pthread_create(&p_thread, NULL, thread_sendDeviceInfoToServer, NULL);
    if (tid < 0)
    {
        perror("thread_sendDeviceInfoToServer() create error");
        exit(1);
    }

    pthread_join(p_thread, (void **)&status);

    return 0;
}
void *thread_sendDeviceInfoToServer(void *tData)
{
    int fd;
    unsigned char data[SERIAL_MAX_BUFF] = {0};

    int server_fd;
    struct sockaddr_in server_addr;
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("> Fail work to create socket fd!\n");
        exit(1);
    }
    printf("> Create server socket fd: %d\n", server_fd);

    memset((void *)&server_addr, 0x00, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
		server_addr.sin_addr.s_addr = inet_addr("192.168.0.2");server_addr.sin_port = htons(12122);
    while (connect(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1)
    {
        perror("> Connect to server error");
        delay(1);
    }

    Sensor sensor;

    openDevice(&fd);
    while (true)
    {
        readPacket(fd, data);
        setDataFromPacket(&sensor, data);
        write(server_fd, &sensor, sizeof(Sensor));
        delay(1);
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
    }
    else
    {
        printf("> %s is not accessable.\nPlease, check device!\n", USB_SERIAL);
        exit(1);
    }
}

void readPacket(int fd, unsigned char *data)
{
    int readSize;
    int readTotalSize;
    unsigned char buff[SERIAL_MAX_BUFF] = {0};
    unsigned char temp_buff[SERIAL_MAX_BUFF] = {0};
    bzero(data, SERIAL_MAX_BUFF);

    tcflush(fd, TCIFLUSH);
    printf("> Read packet data of sensor.\n");

    for (readTotalSize = 0; readTotalSize < SERIAL_MAX_BUFF; readTotalSize += readSize)
    {
        if ((readSize = user_uart_read(fd, temp_buff, SERIAL_MAX_BUFF)) == -1)
        {
            readSize = 0;
            continue;
        }

        strncat_s(buff, temp_buff, readTotalSize, readSize);
    }

    processPacket(data, buff, readTotalSize);
}

void processPacket(unsigned char *data, unsigned char *buff, int buff_size)
{
    int index_start = 0;
    int index_end = 0;
    bool start = false;

    for (int i = 0; i < buff_size; i++)
    {
        if (buff[i] == START_BIT1 &&
            buff[i + 1] == START_BIT2 &&
            !start)
        {
            start = true;
            index_start = i;
        }
        else if (buff[i] == END_BIT1 &&
                 buff[i + 1] == END_BIT2 &&
                 start)
        {
            start = false;
            index_end = i + 1;
        }

        if ((index_end - index_start) == 5 ||
            (index_end - index_start) == 19)
        {
            break;
        }
        else
        {
            continue;
        }
    }

    for (int i = 0, j = index_start; j <= index_end; i++, j++)
    {
        data[i] = buff[j];
    }
}

void setDataFromPacket(Sensor *sensor, unsigned char data[SERIAL_MAX_BUFF])
{
    printf("> Set sensing data from packet.\n");
    if (data[S_START_COL1] == START_BIT1 &&
        data[S_START_COL2] == START_BIT2 &&
        data[S_ULTRASONIC_COL] == SENSOR_BIT_USD &&
        data[S_IR_COL] == SENSOR_BIT_IR &&
        data[S_HT_COL] == SENSOR_BIT_DHT &&
        data[S_LIGHT_COL] == SENSOR_BIT_PTR &&
        data[S_GAS_COL] == SENSOR_BIT_GAS &&
        data[S_END_COL1] == END_BIT1 &&
        data[S_END_COL2] == END_BIT2)
    {
        sensor->ultrasonic = data[S_ULTRASONIC_COL + 1] * 100 + data[S_ULTRASONIC_COL + 2];
        sensor->ir = data[S_IR_COL + 1];
        sensor->humidity = data[S_HT_COL + 1];
        sensor->temperature = data[S_HT_COL + 2];
        sensor->heatindex = data[S_HT_COL + 3] + data[S_HT_COL + 4] * 0.01;
        sensor->light = data[S_LIGHT_COL + 1] * 100 + data[S_LIGHT_COL + 2];
        sensor->gas = data[S_GAS_COL + 1] * 100 + data[S_GAS_COL + 2];

        showData(SENSOR_PACKET_SIZE, data);
        printf("  Ultrasonic\t: %03d\t\t IR\t\t: %d\n", sensor->ultrasonic, sensor->ir);
        printf("  Humidity\t: %02d\t\t Temperature\t: %02d\n", sensor->humidity, sensor->temperature);
        printf("  Heatindex\t: %02.2f\t\t Light\t\t: %03d\n", sensor->heatindex, sensor->light);
        printf("  Gas\t\t: %04d\n", sensor->gas);
    }
}

void strncat_s(unsigned char *data, unsigned char *buff, int data_size, int buff_size)
{
    int i, j;

    for (i = 0, j = data_size; j < SERIAL_MAX_BUFF && i < buff_size; i++, j++)
    {
        data[j] = buff[i];
        // printf("%02X ", buff[i]);
    }
}

void showData(int size, unsigned char data[SERIAL_MAX_BUFF])
{
    printf("  ");
    for (int i = 0; i < size; i++)
    {
        printf("%02X ", data[i]);
    }
    printfln();
}

void TEST_setSensorStruct(Sensor *sensor)
{
    printf("> Set sensor data from packet.\n");

    sensor->ultrasonic = rand() % 100 + 1;
    sensor->ir = rand() % 1 + 1;
    sensor->humidity = rand() % 70 + 30;
    sensor->temperature = rand() % 20 + 20;
    sensor->heatindex = rand() % 20 + 20 + (rand() % 100) * 0.01;
    sensor->light = rand() % 800 + 100;
    sensor->gas = rand() % 700 + 300;

    printf("  Ultrasonic\t: %03d\t\t IR\t\t: %d\n", sensor->ultrasonic, sensor->ir);
    printf("  Humidity\t: %02d\t\t Temperature\t: %02d\n", sensor->humidity, sensor->temperature);
    printf("  Heatindex\t: %02.2f\t\t Light\t\t: %03d\n", sensor->heatindex, sensor->light);
    printf("  Gas\t\t: %04d\n", sensor->gas);
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