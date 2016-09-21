#include <arpa/inet.h>
#include <stdbool.h> // bool, true, false
#include <netinet/in.h>
#include <string.h> // memset()
#include <sys/socket.h>
#include <termios.h>
#include <stdlib.h>
#include <mysql/mysql.h>

// #define DB_HOST "127.0.0.1"
#define DB_HOST "165.132.121.124"
#define DB_PORT 3306
#define DB_USER "root"
#define DB_PASS "0000"
#define DB_NAME "master"

enum
{
    SENSOR = 1,
    ACTUATOR = 2
};

typedef struct Sensor
{
    int ultrasonic;
    int ir;
    int humidity;
    int temperature;
    float heatindex;
    int light;
    int gas;
} Sensor;

typedef struct Actuator
{
    int buzzer;
    int fan;
    int servo;
} Actuator;

void *thread_recvDeviceInfoFromClient(void *);
void *thread_recvData(void *);

void openDevice();
void readPacket();
void setDataFromDevice();
void recvDeviceInfoToServer();
