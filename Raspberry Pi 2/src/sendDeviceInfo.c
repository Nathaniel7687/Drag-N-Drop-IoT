#include "sendDeviceInfo.h"
#include "main.h"
#include "uart_api.h"

void* thread_sendDeviceInfoToServer(void* data)
{
    printf("> Create sendDeviceInfoToServer thread\n");

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("> Fail work to create socket fd!\n");
        exit(1);
    }
    printf("> Create server socket fd: %d\n", server_fd);

    memset((void*)&server_addr, 0x00, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    // TODO: necessary to change ip in inet_addr("127.0.0.1").
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    server_addr.sin_port = htons(12121);

    // while(connect(server_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1) {
    //     perror("> Connect to server error");
    //     delay(1);
    // }

    sensor = (Sensor*)malloc(sizeof(Sensor));
    actuator = (Actuator*)malloc(sizeof(Actuator));
    openDevice();
    while (true) {
        readPacket();
        setDataFromPacket();
        // sendSensorInfoToServer();
        delay(0.1);
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
        exit(1);
    }
}

void readPacket()
{
    int readSize;
    int readTotalSize;
    unsigned char buff[SEIRAL_MIN_BUFF] = { 0 };

    // TCIFLUSH	 수신했지만 읽어들이지 않은 데이터를 버립니다.
    // TCOFLUSH	 쓰기응이지만 송신하고 있지 않는 데이터를 버립니다.
    // TCIOFLUSH 수신했지만 읽어들이지 않은 데이터, 및 쓰기응이지만 송신하고 있지 않는 데이터의 양쪽 모두를 버립니다.
    tcflush(fd, TCIFLUSH);
    printf("> Read packet data of sensor.\n");

    for (readTotalSize = 0; buff[0] != END_BIT1 && buff[1] != END_BIT2; readTotalSize += readSize) {
        if ((readSize = user_uart_read(fd, buff, SEIRAL_MIN_BUFF)) == -1) {
            readSize = 0;
            continue;
        }

        strncat_s(data, buff, readTotalSize, readSize);
    }

    printf("  ");
    for (int i = 0; i < SEIRAL_MAX_BUFF; i++) {
        printf("%02X ", data[i]);
    }
    printfln();
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
        data[S_END_COL2] == END_BIT2) {

        sensor->ultrasonic = data[S_ULTRASONIC_COL + 1] * 100 + data[S_ULTRASONIC_COL + 2];
        sensor->ir = data[S_IR_COL + 1];
        sensor->humidity = data[S_HT_COL + 1];
        sensor->temperature = data[S_HT_COL + 2];
        sensor->heatindex = data[S_HT_COL + 3] + data[S_HT_COL + 4] * 0.01;
        sensor->light = data[S_LIGHT_COL + 1] * 100 + data[S_LIGHT_COL + 2];
        sensor->gas = data[S_GAS_COL + 1] * 100 + data[S_GAS_COL + 2];

        printf("  Ultrasonic\t: %03d\t\t IR\t\t: %d\n", sensor->ultrasonic, sensor->ir);
        printf("  Humidity\t: %02d\t\t Temperature\t: %02d\n", sensor->humidity, sensor->temperature);
        printf("  Heatindex\t: %02.2f\t\t Light\t\t: %03d\n", sensor->heatindex, sensor->light);
        printf("  Gas\t\t: %04d\n", sensor->gas);
        // printf("\033[7A");
    }
    else if (data[A_START_COL1] == START_BIT1 &&
        data[A_START_COL2] == START_BIT2 &&
        data[A_END_COL1] == END_BIT1 &&
        data[A_END_COL2] == END_BIT2) {

        switch (data[A_ACTUATOR_COL]) {
        case ACTUATOR_BIT_BUZZER:
            actuator->buzzer = data[A_ACTUATOR_COL + 1];
            printf("  Buzzer\t: %d\n", actuator->buzzer);
        
            break;
        case ACTUATOR_BIT_FAN:
            actuator->fan = data[A_ACTUATOR_COL + 1];
            printf("  Fan\t: %d\n", actuator->fan);
        
            break;
        case ACTUATOR_BIT_SERVO:
            actuator->servo = data[A_ACTUATOR_COL + 1];
            printf("  Servo\t: %d\n", actuator->servo);
        
            break;
        }
    }
}

void sendSensorInfoToServer()
{
    if (write(server_fd, sensor, sizeof(Sensor)) <= 0) {
        perror("> Write to server error");
        exit(1);
    }
}

void strncat_s(unsigned char* target, unsigned char* buff, int target_size, int buff_size)
{
    int i, j;

    for (i = 0, j = target_size; j < SEIRAL_MAX_BUFF && i < buff_size; i++, j++) {
        target[j] = buff[i];
        // printf("%02X ", buff[i]);
    }
}

void TEST_setSensorStruct()
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

void TEST_setActuatorStruct()
{
    printf("> Set Actuator data from packet.\n");

    actuator->buzzer = rand() % 4;
    actuator->fan = rand() % 4;
    actuator->servo = rand() % 4;

    printf("  Buzzer\t: %d\n", actuator->buzzer);
    printf("  Fan\t: %d\n", actuator->fan);
    printf("  Servo\t: %d\n", actuator->servo);
}
