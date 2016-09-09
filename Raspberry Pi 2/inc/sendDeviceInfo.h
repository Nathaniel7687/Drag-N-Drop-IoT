#include <arpa/inet.h>
#include <stdbool.h> // bool, true, false
#include <netinet/in.h>
#include <string.h> // memset()
#include <sys/socket.h>
#include <termios.h>

#define USB_SERIAL      "/dev/ttyACM0"
#define BAUD_RATE       115200
#define DATA_BIT        8
#define STOP_BIT        1
#define PARITY_BIT      0

#define SEIRAL_MAX_BUFF 60
#define SENSOR_PACKET_SIZE 20
#define ACTUATOR_PACKET_SIZE 6

#define START_BIT1      0x77
#define START_BIT2      0x00
#define END_BIT1        0xF0
#define END_BIT2        0x0F

#define SENSOR_BIT_USD  0xD2
#define SENSOR_BIT_IR   0xD3
#define SENSOR_BIT_DHT  0xD4
#define SENSOR_BIT_PTR  0xA0
#define SENSOR_BIT_GAS  0xA8

#define ACTUATOR_BIT_FAN    0xD8
#define ACTUATOR_BIT_SERVO  0xD0
#define ACTUATOR_BIT_BUZZER 0xD1

enum SENSOR_COL{
    S_START_COL1      = 0,
    S_START_COL2      = 1,
    S_ULTRASONIC_COL  = 2,
    S_IR_COL          = 5,
    S_HT_COL          = 7,
    S_LIGHT_COL       = 12,
    S_GAS_COL         = 15,
    S_END_COL1        = 18,
    S_END_COL2        = 19
};

enum ACTUATOR_COL {
    A_START_COL1      = 0,
    A_START_COL2      = 1,
    A_ACTUATOR_COL    = 2,
    A_END_COL1        = 4,
    A_END_COL2        = 5
};

enum {
    SENSOR = 1,
    ACTUATOR = 2  
};

typedef struct Sensor {
    int     ultrasonic;
    int     ir;
    int     humidity;
    int     temperature;
    float   heatindex;
    int     light;
    int     gas;
} Sensor;

typedef struct Actuator {
    int     buzzer;
    int     fan;
    int     servo;
} Actuator;

void* thread_sendDeviceInfoToServer(void* data);

void openDevice();
void readPacket();
void setDataFromPacket();
void sendDeviceInfoToServer();

void strncat_s(unsigned char*, unsigned char*, int, int);
void processPacket(unsigned char*, unsigned char*, int);
void showData(int);

void TEST_setSensorStruct();
void TEST_setActuatorStruct();
