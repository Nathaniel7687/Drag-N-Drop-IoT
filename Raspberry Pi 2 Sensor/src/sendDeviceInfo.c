#include "sendDeviceInfo.h"
#include "main.h"
#include "uart_api.h"
#include <termios.h>

void* thread_sendDeviceInfoToServer(void* data)
{
    printf("> Create sendDeviceInfoToServer thread\n");

    sensor = (Sensor*)malloc(sizeof(sensor));
    openDevice();
    while (true) {
        readPacket();
        setDataFromPacket();
        printf("\033[7A");
        delay_millisecond(100);
    }

    pthread_exit((void*)0);
}

void openDevice()
{
    if (access(USB_SERIAL, R_OK & W_OK) == 0) {
        printf("> %s is accessable\n", USB_SERIAL);

        fd = user_uart_open(USB_SERIAL);
        if (fd != -1) {
            user_uart_config(fd, 115200, 8, 0, 1);

            printf("> %s is opened\n", USB_SERIAL);
            printf("> Configure UART: baud rate %d, data bit %d, stop bit %d, parity bit %d\n", BAUD_RATE, DATA_BIT, STOP_BIT, PARITY_BIT);
        }
    } else {
        printf("> %s is not accessable.\nPlease, check device!\n", USB_SERIAL);
        exit(-1);
    }
}

void readPacket()
{
    int readSize;
    int readTotalSize;
    unsigned char buff[MAX_BUFF_SIZE] = { 0 };

    // TCIFLUSH	 수신했지만 읽어들이지 않은 데이터를 버립니다.
    // TCOFLUSH	 쓰기응이지만 송신하고 있지 않는 데이터를 버립니다.
    // TCIOFLUSH 수신했지만 읽어들이지 않은 데이터, 및 쓰기응이지만 송신하고 있지 않는 데이터의 양쪽 모두를 버립니다.
    tcflush(fd, TCIFLUSH);
    printf("> Read packet data of sensor.\n");

    // Read data until buff[MAX_BUFF_SIZE] full
    for (readTotalSize = 0; readTotalSize < MAX_BUFF_SIZE; readTotalSize += readSize) {
        if ((readSize = user_uart_read(fd, buff, MAX_BUFF_SIZE)) == -1) {
            readSize = 0;
            continue;
        }

        strncat_s(data, buff, readTotalSize, readSize);
    }

    printf("  ");
    for (int i = 0; i < MAX_BUFF_SIZE; i++) {
        printf("%02X ", data[i]);
    }
    printfln();
}

void setDataFromPacket()
{
    printf("> Set sensing data from packet.\n");
    if (data[START_COL1] == START_BIT1 && data[START_COL2] == START_BIT2 && data[ULTRASONIC_COL] == SENSOR_BIT_USD && data[IR_COL] == SENSOR_BIT_IR && data[HT_COL] == SENSOR_BIT_DHT && data[LIGHT_COL] == SENSOR_BIT_PTR && data[GAS_COL] == SENSOR_BIT_GAS && data[END_COL1] == END_BIT1 && data[END_COL2] == END_BIT2) {

        sensor->ultrasonic = data[ULTRASONIC_COL + 1] * 100 + data[ULTRASONIC_COL + 2];
        sensor->ir = data[IR_COL + 1];
        sensor->humidity = data[HT_COL + 1];
        sensor->temperature = data[HT_COL + 2];
        sensor->heatindex = data[HT_COL + 3] + data[HT_COL + 4] * 0.01;
        sensor->light = data[LIGHT_COL + 1] * 100 + data[LIGHT_COL + 2];
        sensor->gas = data[GAS_COL + 1] * 100 + data[GAS_COL + 2];
    }

    printf("  Ultrasonic\t: %03d\t\t IR\t\t: %d\n", sensor->ultrasonic, sensor->ir);
    printf("  Humidity\t: %02d\t\t Temperature\t: %02d\n", sensor->humidity, sensor->temperature);
    printf("  Heatindex\t: %02.2f\t\t Light\t\t: %03d\n", sensor->heatindex, sensor->light);
    printf("  Gas\t\t: %04d\n", sensor->gas);
}

void strncat_s(unsigned char* target, unsigned char* buff, int target_size, int buff_size)
{
    int i, j;

    for (i = 0, j = target_size; j < MAX_BUFF_SIZE && i < buff_size; i++, j++) {
        target[j] = buff[i];
        // printf("%02X ", buff[i]);
    }
}
