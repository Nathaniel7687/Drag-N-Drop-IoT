#include <arpa/inet.h>
#include <errno.h>
#include <math.h>
#include <mysql/mysql.h>
#include <netinet/in.h>
#include <pthread.h>
#include <stdbool.h> // bool, true, false
#include <stdio.h>
#include <stdlib.h>
#include <string.h> // memset()
#include <sys/socket.h>
#include <termios.h>
#include <time.h>
#include <unistd.h> // read(), write(), access(), R_OK, W_OK

#define MILLISECOND 100000
#define DB_HOST "165.132.121.125"
#define DB_PORT 3306
#define DB_USER "root"
#define DB_PASS "0000"
#define DB_NAME "master"

enum {
    SENSOR = 1,
    ACTUATOR = 2
};

typedef struct socketInfo {
    int client_fd;
    int server_fd;
    struct sockaddr_in client_addr;
    struct sockaddr_in server_addr;
} SocketInfo;

typedef struct Sensor {
    int ultrasonic;
    int ir;
    int humidity;
    int temperature;
    float heatindex;
    int light;
    int gas;
} Sensor;

typedef struct Actuator {
    int buzzer;
    int fan;
    int servo;
} Actuator;

void delay(float);
void printfln();

void* thread_recvDeviceInfoFromClient(void*);
void* thread_recvData(void*);

void openDevice();
void readPacket();
void setDataFromDevice();
void recvDeviceInfoToServer();
