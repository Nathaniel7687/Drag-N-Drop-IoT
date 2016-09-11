#include "sendDeviceInfo.h"
#include "piClient.h"
#include "uart_api.h"

int fd;
int distinction;
unsigned char data[SEIRAL_MAX_BUFF] = {0};

Sensor *sensor;
Actuator *actuator;

bool initStatus;
int server_fd;
struct sockaddr_in server_addr;

void *thread_sendDeviceInfoToServer(void *data)
{
    printf("> Create sendDeviceInfoToServer thread\n");

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("> Fail work to create socket fd!\n");
        exit(1);
    }
    printf("> Create server socket fd: %d\n", server_fd);

    memset((void *)&server_addr, 0x00, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    // TODO: necessary to change ip in inet_addr("127.0.0.1").
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    server_addr.sin_port = htons(12121);

    while (connect(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1)
    {
        perror("> Connect to server error");
        delay(1);
    }

    sensor = calloc(1, sizeof(Sensor));
    actuator = calloc(1, sizeof(Actuator));

    // openDevice();
    while (true)
    {
        // readPacket();
        TEST_setSensorStruct();
        // TEST_setActuatorStruct();
        setDataFromPacket();
        sendDeviceInfoToServer();

        delay(1);
    }

    pthread_exit((void *)0);
}

void openDevice()
{
    if (access(USB_SERIAL, R_OK & W_OK) == 0)
    {
        printf("> %s is accessable\n", USB_SERIAL);

        fd = user_uart_open(USB_SERIAL);
        if (fd != -1)
        {
            user_uart_config(fd, 115200, 8, 0, 1);

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

void readPacket()
{
    int readSize;
    int readTotalSize;
    unsigned char buff[SEIRAL_MAX_BUFF] = {0};
    unsigned char temp_buff[SEIRAL_MAX_BUFF] = {0};
    bzero(data, sizeof(data));

    // TCIFLUSH	 수신했지만 읽어들이지 않은 데이터를 버립니다.
    // TCOFLUSH	 쓰기응이지만 송신하고 있지 않는 데이터를 버립니다.
    // TCIOFLUSH 수신했지만 읽어들이지 않은 데이터, 및 쓰기응이지만 송신하고 있지 않는 데이터의 양쪽 모두를 버립니다.
    tcflush(fd, TCIFLUSH);
    printf("> Read packet data of sensor.\n");

    for (readTotalSize = 0; readTotalSize < SEIRAL_MAX_BUFF; readTotalSize += readSize)
    {
        if ((readSize = user_uart_read(fd, temp_buff, SEIRAL_MAX_BUFF)) == -1)
        {
            readSize = 0;
            continue;
        }

        strncat_s(buff, temp_buff, readTotalSize, readSize);
    }

    processPacket(data, buff, readTotalSize);
}

void processPacket(unsigned char *target, unsigned char *buff, int buff_size)
{
    int index_start = 0;
    int index_end = 0;
    bool start = false;

    // printf("  ");
    // for (int i = 0; i < buff_size; i++)
    // {
    //     printf("%02X ", buff[i]);
    // }
    // printfln();

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

void setDataFromPacket()
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

        distinction = SENSOR;
        sensor->ultrasonic = data[S_ULTRASONIC_COL + 1] * 100 + data[S_ULTRASONIC_COL + 2];
        sensor->ir = data[S_IR_COL + 1];
        sensor->humidity = data[S_HT_COL + 1];
        sensor->temperature = data[S_HT_COL + 2];
        sensor->heatindex = data[S_HT_COL + 3] + data[S_HT_COL + 4] * 0.01;
        sensor->light = data[S_LIGHT_COL + 1] * 100 + data[S_LIGHT_COL + 2];
        sensor->gas = data[S_GAS_COL + 1] * 100 + data[S_GAS_COL + 2];

        showData(SENSOR_PACKET_SIZE);
        printf("  Ultrasonic\t: %03d\t\t IR\t\t: %d\n", sensor->ultrasonic, sensor->ir);
        printf("  Humidity\t: %02d\t\t Temperature\t: %02d\n", sensor->humidity, sensor->temperature);
        printf("  Heatindex\t: %02.2f\t\t Light\t\t: %03d\n", sensor->heatindex, sensor->light);
        printf("  Gas\t\t: %04d\n", sensor->gas);

        // printf("\033[7A");
    }
    else if (data[A_START_COL1] == START_BIT1 &&
             data[A_START_COL2] == START_BIT2 &&
             data[A_END_COL1] == END_BIT1 &&
             data[A_END_COL2] == END_BIT2)
    {

        distinction = ACTUATOR;

        switch (data[A_ACTUATOR_COL])
        {
        case ACTUATOR_BIT_BUZZER:
            actuator->buzzer = data[A_ACTUATOR_COL + 1];

            showData(ACTUATOR_PACKET_SIZE);
            printf("  Buzzer\t: %d\n", actuator->buzzer);

            break;
        case ACTUATOR_BIT_FAN:
            actuator->fan = data[A_ACTUATOR_COL + 1];

            showData(ACTUATOR_PACKET_SIZE);
            printf("  Fan\t: %d\n", actuator->fan);

            break;
        case ACTUATOR_BIT_SERVO:
            actuator->servo = data[A_ACTUATOR_COL + 1];

            showData(ACTUATOR_PACKET_SIZE);
            printf("  Servo\t: %d\n", actuator->servo);

            break;
        }

        // printf("\033[4A");
    }
}

void sendDeviceInfoToServer()
{
    if (!initStatus)
    {
        if (write(server_fd, &distinction, sizeof(distinction)) <= 0)
        {
            perror("> Write distinction to server error");
            return;
        }
        else
        {
            initStatus = true;
            printf("> Write distinction to server: %d\n", distinction);
        }
    }

    switch (distinction)
    {
    case SENSOR:
        write(server_fd, sensor, sizeof(Sensor));
        break;
    case ACTUATOR:
        write(server_fd, actuator, sizeof(actuator));
        break;
    }
}

void strncat_s(unsigned char *target, unsigned char *buff, int target_size, int buff_size)
{
    int i, j;

    for (i = 0, j = target_size; j < SEIRAL_MAX_BUFF && i < buff_size; i++, j++)
    {
        target[j] = buff[i];
        // printf("%02X ", buff[i]);
    }
}

void showData(int size)
{
    printf("  ");
    for (int i = 0; i < size; i++)
    {
        printf("%02X ", data[i]);
    }
    printfln();
}

void TEST_setSensorStruct()
{
    printf("> Set sensor data from packet.\n");

    distinction = 1;
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

void TEST_setActuatorStruct()
{
    printf("> Set Actuator data from packet.\n");

    distinction = 2;
    actuator->buzzer = rand() % 4;
    actuator->fan = rand() % 4;
    actuator->servo = rand() % 4;

    printf("  Buzzer\t: %d\n", actuator->buzzer);
    printf("  Fan\t: %d\n", actuator->fan);
    printf("  Servo\t: %d\n", actuator->servo);
}
